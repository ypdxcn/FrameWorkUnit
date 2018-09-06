#pragma once


#undef socklen_t
#include "mongoose.h"

/*
static const char *s_http_port = "8003";

static void ev_handler(struct mg_connection *c, int ev, void *p) 
{
	if (ev == MG_EV_HTTP_REQUEST) 
	{
		struct http_message *hm = (struct http_message *) p;

		// We have received an HTTP request. Parsed request is contained in `hm`.
		// Send HTTP reply to the client which shows full original request.
		mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
		mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
	}
}
*/

static sig_atomic_t     s_signal_received = 0;
static const char       *s_http_port = "8000";
static struct mg_serve_http_opts    s_http_server_opts;

static void signal_handler(int sig_num) {
	signal(sig_num, signal_handler);  // Reinstantiate signal handler
	s_signal_received = sig_num;
}

static int is_websocket(const struct mg_connection *nc) {
	return nc->flags & MG_F_IS_WEBSOCKET;
}

//RESTful API demo
//界面数据发生变化时，下面函数响应
static void handle_sum_call(struct mg_connection *nc, struct http_message *hm) 
{
	char n1[100], n2[100];
	double result;

	/* Get form variables */
	mg_get_http_var(&hm->body, "n1", n1, sizeof(n1));
	mg_get_http_var(&hm->body, "n2", n2, sizeof(n2));

	/* Send headers */
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

	/* Compute the result and send it back as a JSON object */
	result = strtod(n1, NULL) + strtod(n2, NULL);
	mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);
	mg_send_http_chunk(nc, "", 0); /* Send empty chunk, the end of response */
}

static void broadcast(struct mg_connection *nc, const struct mg_str msg) {
	struct mg_connection *c;
	char buf[500];
	char addr[32];
	mg_sock_addr_to_str(&nc->sa, addr, sizeof(addr),MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);

	snprintf(buf, sizeof(buf), "%s %.*s", addr, (int)msg.len, msg.p);
	printf("%s\n", buf); /* Local echo. */
	for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) 
	{
		if (c == nc) continue; /* Don't send to the sender. */
		mg_send_websocket_frame(c, WEBSOCKET_OP_TEXT, buf, strlen(buf));
	}
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) 
{
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
		/* New websocket connection. Tell everybody. */
		broadcast(nc, mg_mk_str("++ joined"));
		break;
	}
	case MG_EV_WEBSOCKET_FRAME: {
		struct websocket_message *wm = (struct websocket_message *) ev_data;
		/* New websocket message. Tell everybody. */
		struct mg_str d = { (char *)wm->data, wm->size };
		broadcast(nc, d);
		break;
	}
	case MG_EV_HTTP_REQUEST: {
		//mg_serve_http(nc, (struct http_message *) ev_data, s_http_server_opts);
		//break;

		if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) 
		{
			handle_sum_call(nc, hm); /* Handle RESTful call */
		}
		else if (mg_vcmp(&hm->uri, "/printcontent") == 0) 
		{
			char buf[100] = { 0 };
			memcpy(buf, hm->body.p,
				sizeof(buf) - 1 < hm->body.len ? sizeof(buf) - 1 : hm->body.len);
			printf("%s\n", buf);
		}
		else {
			mg_serve_http(nc, hm, s_http_server_opts); /* Serve static content */
		}
		break;
	}
	case MG_EV_CLOSE: {
		/* Disconnect. Tell everybody. */
		if (is_websocket(nc)) {
			broadcast(nc, mg_mk_str("-- left"));
		}
		break;
	}
	}
}
