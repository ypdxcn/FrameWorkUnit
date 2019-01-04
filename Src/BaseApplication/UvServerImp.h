#pragma once
#include <string>
#include <vector>

#include <functional>

using namespace std;

#include "uv.h"
#include "uvPacketStruct.h"
#include "WorkThread.h"

class CPacket;//内部K-V格式数据


//本网络层对上层的回调服务
using  connectCallBack		= std::function<void(int error)>;
using  disconnectCallBack	= std::function<void(int error)>;
using  sendCallBack			= std::function<void(int error)>;
using  receviveCallBack		= std::function<void(CPacket &pkt)>;

//底层对本网络层回调
using  tcpCloseCallBack		= std::function<void (int clientId, void* userdata)>;//当clientid为-1时，表现服务器的关闭事件
using  newConnectCallBack   = std::function<void (int clientId, void* userdata)>;//接收到新客户
using  serverRecvCallBack   = std::function<void (int clientid, const NetPacket& packethead, const unsigned char* buf, void* userdata)>;//收数据

using  getPacketCallback = std::function<void(const NetPacket& packethead, const unsigned char* buf, void* userdata)>;


inline std::string GetUVError(int errcode)
{
	if (0 == errcode) {
		return "";
	}
	std::string err;
	auto tmpChar = uv_err_name(errcode);
	if (tmpChar) {
		err = tmpChar;
		err += ":";
	}
	else {
		err = "unknown system errcode " + std::to_string((long long)errcode);
		err += ":";
	}
	tmpChar = uv_strerror(errcode);
	if (tmpChar) {
		err += tmpChar;
	}
	return std::move(err);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//定义关联上下文
class AcceptClient;
typedef struct _tcpclient_ctx 
{
	uv_tcp_t	tcphandle;//data filed store this
	//PacketSync* packet_;//userdata filed storethis
	uv_buf_t	read_buf_;
	int			clientid;
	void*		parent_server;//tcpserver
	void*		parent_acceptclient;//accept client
} TcpClientCtx;
TcpClientCtx* AllocTcpClientCtx(void* parentserver);
void FreeTcpClientCtx(TcpClientCtx* ctx);

//
typedef struct _write_param 
{ //the param of uv_write
	uv_write_t	write_req_;
	uv_buf_t	buf_;
	int			buf_truelen_;
} write_param;

write_param* AllocWriteParam(void);
void FreeWriteParam(write_param* param);
/////////////////////////////////////////////////////////////////////////////////////////////////////


class CUvServerImp
{
public:
	class  CMyServer /*: public  CWorkThread*/
	{
		//子类嵌套
		class AcceptClient
		{
		public:
			//control: accept client data. handle by server
			//loop:    the loop of server
			AcceptClient(TcpClientCtx* control, int clientid, char packhead, char packtail, uv_loop_t* loop);
			virtual ~AcceptClient();

			void SetRecvCB(serverRecvCallBack pfun, void* userdata)//set recv cb
			{

			}
			void SetClosedCB(tcpCloseCallBack pfun, void* userdata);//set close cb.
			TcpClientCtx* GetTcpHandle(void) const;

			void Close();

			const char* GetLastErrMsg() const {
				return errmsg_.c_str();
			};

		private:
			bool init(char packhead, char packtail);

			uv_loop_t* loop_;
			int client_id_;

			TcpClientCtx* client_handle_;//accept client data
			bool isclosed_;
			std::string errmsg_;

			serverRecvCallBack recvcb_;
			void* recvcb_userdata_;

			tcpCloseCallBack closedcb_;
			void* closedcb_userdata_;
		private:
			static void AfterClientClose(uv_handle_t* handle);
		public:
			friend static void AllocBufferForRecv(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
			friend static void AfterRecv(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
		
			friend static void GetPacket(const NetPacket& packethead, const unsigned char* packetdata, void* userdata);
		};


	public:
		enum {
			START_TIMEOUT,
			START_FINISH,
			START_ERROR,
			START_DIS,
		};

		CMyServer()
		{
			int iret = uv_loop_init(&loop_);
			if (iret) 
			{
				errmsg_ = uv_errno_t(iret);
				fprintf(stdout, "init loop error: %s\n", errmsg_.c_str());
			}

			iret = uv_mutex_init(&mutex_clients_);
			if (iret) {
				errmsg_ = uv_errno_t(iret);
				
				fprintf(stdout, "uv_mutex_init error: %s\n", errmsg_.c_str());
			}
		}
		~CMyServer()
		{
			Close();
			uv_thread_join(&start_threadhandle_);
			uv_mutex_destroy(&mutex_clients_);
			uv_loop_close(&loop_);
			for (auto it = available_tcpHandle_.begin(); it != available_tcpHandle_.end(); ++it) {
				FreeTcpClientCtx(*it);
			}
			available_tcpHandle_.clear();

			for (auto it = writeparam_list_.begin(); it != writeparam_list_.end(); ++it) {
				FreeWriteParam(*it);
			}
			writeparam_list_.clear();
		}
		void Bind(CUvServerImp *parent) { m_parent = parent; }
		
		bool init() 
		{
			if (!isclosed_) {
				return true;
			}
			int iret = uv_async_init(&loop_, &async_handle_close_, AsyncCloseCB);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			async_handle_close_.data = this;

			iret = uv_tcp_init(&loop_, &tcp_handle_);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			tcp_handle_.data = this;
			iret = uv_tcp_nodelay(&tcp_handle_, 1);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			isclosed_ = false;
			return true;
		}

		bool Start(const char* ip, int port)//Start the server, ipv4
		{
			serverip_   = ip;
			serverport_ = port;
			closeinl();
			if (!init()) 
			{
				return false;
			}
			if (!bind(serverip_.c_str(), serverport_)) {
				return false;
			}
			if (!listen(SOMAXCONN)) {
				return false;
			}
			int iret = uv_thread_create(&start_threadhandle_, StartThread, this);//use thread to wait for start succeed.
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			int wait_count = 0;
			while (startstatus_ == START_DIS) {
				Sleep(100);
				if (++wait_count > 100) {
					startstatus_ = START_TIMEOUT;
					break;
				}
			}
			return startstatus_ == START_FINISH;
		}

		bool Start6(const char* ip, int port)//Start the server, ipv6
		{
			serverip_ = ip;
			serverport_ = port;
			closeinl();
			if (!init()) {
				return false;
			}
			if (!bind6(serverip_.c_str(), serverport_)) {
				return false;
			}
			if (!listen(SOMAXCONN)) {
				return false;
			}
			int iret = uv_thread_create(&start_threadhandle_, StartThread, this);//use thread to wait for start succeed.
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			int wait_count = 0;
			while (startstatus_ == START_DIS) {
				Sleep(100);
				if (++wait_count > 100) {
					startstatus_ = START_TIMEOUT;
					break;
				}
			}
			return startstatus_ == START_FINISH;
		}

		void closeinl()
		{
			if (isclosed_) {
				return;
			}

			uv_mutex_lock(&mutex_clients_);
			for (auto it = clients_list_.begin(); it != clients_list_.end(); ++it) {
				auto data = it->second;
				data->Close();
			}
			uv_walk(&loop_, CloseWalkCB, this);//close all handle in loop
			//LOGI("close server");
		}


		void Close()//send close command. verify IsClosed for real closed
		{
			if (isclosed_) {return;	}

			isUseraskforclosed_ = true;
			uv_async_send(&async_handle_close_);
		}

		

		bool IsClosed() {//verify if real closed
			return isclosed_;
		};
		bool bind(const char* ip, int port)
		{
			struct sockaddr_in bind_addr;
			int iret = uv_ip4_addr(ip, port, &bind_addr);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			iret = uv_tcp_bind(&tcp_handle_, (const struct sockaddr*)&bind_addr, 0);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			//LOGI("server bind ip=" << ip << ", port=" << port);
			return true;
		}
		bool bind6(const char* ip, int port)
		{
			struct sockaddr_in6 bind_addr;
			int iret = uv_ip6_addr(ip, port, &bind_addr);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			iret = uv_tcp_bind(&tcp_handle_, (const struct sockaddr*)&bind_addr, 0);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}

			//LOGI("server bind ip=" << ip << ", port=" << port);
			return true;
		}

		bool listen(int backlog = SOMAXCONN)
		{
			int iret = uv_listen((uv_stream_t*)&tcp_handle_, backlog, AcceptConnection);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			//LOGI("server Start listen. Runing.......");
			fprintf(stdout, "Server Runing.......\n");
			return true;
		}

		bool run(int status = UV_RUN_DEFAULT)
		{
			int iret = uv_run(&loop_, (uv_run_mode)status);
			if (iret) {
				errmsg_ = GetUVError(iret);
				//LOGE(errmsg_);
				return false;
			}
			return true;
		}


		static void StartThread(void* arg)
		{

			CMyServer* theclass    = (CMyServer*)arg;
			theclass->startstatus_ = START_FINISH;
			theclass->run();
			//the server is close when come here
			theclass->isclosed_ = true;
			theclass->isUseraskforclosed_ = false;
			//LOGI("server  had closed.");
			if (theclass->closedcb_) {//trigger the close cb
				theclass->closedcb_(-1, theclass->closedcb_userdata_);
			}
		}

		static void AcceptConnection(uv_stream_t* server, int status)
		{
			CMyServer* tcpsock = (CMyServer*)server->data;
			//assert(tcpsock);
			if (status) {
				tcpsock->errmsg_ = GetUVError(status);
				//LOGE(tcpsock->errmsg_);
				return;
			}
			TcpClientCtx* tmptcp = nullptr;//定义上下文指针
			if (tcpsock->available_tcpHandle_.empty()) {
				tmptcp = AllocTcpClientCtx(tcpsock);
			}
			else {
				tmptcp = tcpsock->available_tcpHandle_.front();
				tcpsock->available_tcpHandle_.pop_front();
				tmptcp->parent_acceptclient = NULL;
			}
			int iret = uv_tcp_init(&tcpsock->loop_, &tmptcp->tcphandle);
			if (iret) {
				tcpsock->available_tcpHandle_.push_back(tmptcp);//Recycle
				tcpsock->errmsg_ = GetUVError(iret);
				///LOGE(tcpsock->errmsg_);
				return;
			}
			tmptcp->tcphandle.data = tmptcp;

			auto clientid = tcpsock->GetAvailaClientID();
			tmptcp->clientid = clientid;
			iret = uv_accept((uv_stream_t*)server, (uv_stream_t*)&tmptcp->tcphandle);
			if (iret) {
				tcpsock->available_tcpHandle_.push_back(tmptcp);//Recycle
				tcpsock->errmsg_ = GetUVError(iret);
				//LOGE(tcpsock->errmsg_);
				return;
			}

			tcpsock->SetPacketCB(GetPacket, tmptcp);
			//tcpsock->Start(tcpsock->packet_head, tcpsock->packet_tail);
			iret = uv_read_start((uv_stream_t*)&tmptcp->tcphandle, AllocBufferForRecv, AfterRecv);
			if (iret) {
				uv_close((uv_handle_t*)&tmptcp->tcphandle, CMyServer::RecycleTcpHandle);
				tcpsock->errmsg_ = GetUVError(iret);
				//LOGE(tcpsock->errmsg_);
				return;
			}
			AcceptClient* cdata = new AcceptClient(tmptcp, clientid, tcpsock->packet_head, tcpsock->packet_tail, &tcpsock->loop_); //delete on SubClientClosed
			cdata->SetClosedCB(CMyServer::SubClientClosed, tcpsock);
			uv_mutex_lock(&tcpsock->mutex_clients_);
			tcpsock->clients_list_.insert(std::make_pair(clientid, cdata)); //add accept client
			uv_mutex_unlock(&tcpsock->mutex_clients_);

			if (tcpsock->newconcb_) {
				tcpsock->newconcb_(clientid, tcpsock->newconcb_userdata_);
			}
			//LOGI("new client id=" << clientid);
			return;
		}
		static void AsyncCloseCB(uv_async_t* handle)//async close
		{
			CMyServer* theclass = (CMyServer*)handle->data;
			if (theclass->isUseraskforclosed_) {
				theclass->closeinl();
			}
			return;
		}

		/* Fully close a loop */
		static void CloseWalkCB(uv_handle_t* handle, void* arg)
		{
			CMyServer* theclass = (CMyServer*)arg;
			if (!uv_is_closing(handle)) {
				uv_close(handle, AfterServerClose);
			}
		}
		static void AfterServerClose(uv_handle_t* handle)
		{
			CMyServer* theclass = (CMyServer*)handle->data;
			fprintf(stdout, "Close CB handle %p\n", handle);
		}

		static void GetPacket(const NetPacket& packethead, const unsigned char* packetdata, void* userdata)
		{
			fprintf(stdout, "Get control packet type %d\n", packethead.type);
			//assert(userdata);
			TcpClientCtx* theclass = (TcpClientCtx*)userdata;
			CMyServer* parent = (CMyServer*)theclass->parent_server;
			const std::string& senddata = parent->ParsePacket(packethead, packetdata);
			parent->sendinl(senddata, theclass);
			return;
		}

		int GetAvailaClientID() const
		{
			static int s_id = 0;
			return ++s_id;
		}

		//client的数据解析回调
		void SetPacketCB(getPacketCallback pfun, void* userdata) {
			getPacketcb_		 = pfun;
			packetcb_userdata_   = userdata;
		}

		bool sendinl(const std::string& senddata, TcpClientCtx* client)
		{
			if (senddata.empty()) {
				//LOGA("send data is empty.");
				return true;
			}
			write_param* writep = nullptr;
			if (writeparam_list_.empty()) {
				writep = AllocWriteParam();
			}
			else {
				writep = writeparam_list_.front();
				writeparam_list_.pop_front();
			}
			if (writep->buf_truelen_ < senddata.length()) {
				writep->buf_.base = (char*)realloc(writep->buf_.base, senddata.length());
				writep->buf_truelen_ = senddata.length();
			}
			memcpy(writep->buf_.base, senddata.data(), senddata.length());
			writep->buf_.len = senddata.length();
			writep->write_req_.data = client;
			int iret = uv_write((uv_write_t*)&writep->write_req_, (uv_stream_t*)&client->tcphandle, &writep->buf_, 1, AfterSend);//发送
			if (iret) {
				writeparam_list_.push_back(writep);
				errmsg_ = "send data error.";
				//LOGE("client(" << client << ") send error:" << GetUVError(iret));
				fprintf(stdout, "send error. %s-%s\n", uv_err_name(iret), uv_strerror(iret));
				return false;
			}
			return true;
			
		}

		static  const int  MAXLISTSIZE = 50;

		static void RecycleTcpHandle(uv_handle_t* handle)//recycle handle after close client
		{
			TcpClientCtx* theclass = (TcpClientCtx*)handle->data;
			//assert(theclass);
			CMyServer* parent = (CMyServer*)theclass->parent_server;
			if (parent->available_tcpHandle_.size() > MAXLISTSIZE) {
				FreeTcpClientCtx(theclass);
			}
			else {
				parent->available_tcpHandle_.push_back(theclass);
			}
		}

		static void SubClientClosed(int clientid, void* userdata) //AcceptClient close cb
		{
			CMyServer* theclass = (CMyServer*)userdata;
			uv_mutex_lock(&theclass->mutex_clients_);
			auto itfind = theclass->clients_list_.find(clientid);
			if (itfind != theclass->clients_list_.end()) {
				if (theclass->closedcb_) {
					theclass->closedcb_(clientid, theclass->closedcb_userdata_);
				}
				if (theclass->available_tcpHandle_.size() > MAXLISTSIZE) {
					FreeTcpClientCtx(itfind->second->GetTcpHandle());
				}
				else {
					theclass->available_tcpHandle_.push_back(itfind->second->GetTcpHandle());
				}
				delete itfind->second;
				//LOGI("delete client:" << itfind->first);
				fprintf(stdout, "delete client：%d\n", itfind->first);
				theclass->clients_list_.erase(itfind);
			}
			uv_mutex_unlock(&theclass->mutex_clients_);
		}

		//回调解析数据
		const std::string& ParsePacket(const NetPacket& packet, const unsigned char* buf)
		{
			return  "";
		}

		static void AfterSend(uv_write_t* req, int status)
		{
			TcpClientCtx* theclass = (TcpClientCtx*)req->data;
			CMyServer* parent = (CMyServer*)theclass->parent_server;
			if (parent->writeparam_list_.size() > MAXLISTSIZE) {
				FreeWriteParam((write_param*)req);
			}
			else {
				parent->writeparam_list_.push_back((write_param*)req);
			}
			if (status < 0) {
				//LOGE("send data error:" << GetUVError(status));
				fprintf(stderr, "send error %s.%s\n", uv_err_name(status), uv_strerror(status));
			}
		}

		static void AfterRecv(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
		{
			/*
			TcpClientCtx* theclass = (TcpClientCtx*)handle->data;
			//assert(theclass);
			if (nread < 0) {
				if (nread == UV_EOF) {
					fprintf(stdout, "client(%d)eof\n", theclass->clientid);
					//LOGW("client(" << theclass->clientid << ")eof");
				}
				else if (nread == UV_ECONNRESET) {
					fprintf(stdout, "client(%d)conn reset\n", theclass->clientid);
					//LOGW("client(" << theclass->clientid << ")conn reset");
				}
				else {
					fprintf(stdout, "%s\n", GetUVError(nread));
					//LOGW("client(" << theclass->clientid << ")：" << GetUVError(nread));
				}
				AcceptClient* acceptclient = (AcceptClient*)theclass->parent_acceptclient;
				acceptclient->Close();
				return;
			}
			else if (0 == nread) {

			}
			else {
				theclass->recvdata((const unsigned char*)buf->base, nread);
			}
			*/
		}

		static  void AllocBufferForRecv(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
		{
			TcpClientCtx* theclass = (TcpClientCtx*)handle->data;
			//assert(theclass);
			*buf = theclass->read_buf_;
		}


	
public:

		char packet_head;//protocol head
		char packet_tail;//protocol tail


private:
		int             startstatus_;
		bool			isclosed_;//是否关闭
		bool			isUseraskforclosed_;//用户要求关闭

		std::string		errmsg_;
		uv_mutex_t		mutex_clients_;

		uv_loop_t		loop_;//底层事件模型，主循环
		uv_tcp_t		tcp_handle_;
		uv_async_t		async_handle_close_;

		std::string		serverip_;//服务IP
		int				serverport_;//服务端口
		uv_thread_t		start_threadhandle_;//启动的线程句柄


		

		//accept管理
		std::map<int, AcceptClient*> clients_list_;//clients

		//accept管理
		std::list<TcpClientCtx*> available_tcpHandle_;//Available accept client data
		std::list<write_param*>  writeparam_list_;//Available write_t


		//与OS IO交互的回调
		tcpCloseCallBack      closedcb_;
		void*				  closedcb_userdata_;

		newConnectCallBack    newconcb_;
		void*				  newconcb_userdata_;

	    serverRecvCallBack    recvcb_;

		//客户socket的回调
		getPacketCallback     getPacketcb_;
		void*				  packetcb_userdata_;//回调函数所带的自定义数据


		CUvServerImp  *m_parent;

	};

public:
	CUvServerImp();
	~CUvServerImp();

	static CUvServerImp *Instance()
	{
		static CUvServerImp  imp;
		return &imp;
	}

	////////////////给上层注册回调///////////////////////////////////////////////////////////////////
	//用来处理接收到数据的
	void  registerReceiveCallBack(receviveCallBack& receviveCallBack);
	void  unregisterReceiveCallBack(const receviveCallBack& receviveCallBack);

	//用来处理网络状态通知
	void  registerConnectCallBack(const connectCallBack& connectCallBack);
	void  registerdisConnectCallBack(const disconnectCallBack & disconnectCallBack);
	void  registerSendCallBack(const sendCallBack & sendCallBack);
	////////////////////////////////////////////////////////////////////////////////////////////
	int  InitServerUrl(const char *url);
	//int  InitClientUrl(const char *url);
	void closeAll();
	int  send(const  char *data ,int length);
	int  recv(const  char *data);
	

private:
	//////////////////////////////////////////////上层/////////////////////////////////////////////////////////////////
	//搜集订阅,消息通道
	std::vector<connectCallBack>      net_connectCb_;
	std::vector<disconnectCallBack>   net_disconnectCb_;
	std::vector<sendCallBack>         sendCb_;
	//用于给上层订阅,数据通道
	using VPKTRECEIVER = std::vector<receviveCallBack *>;
	VPKTRECEIVER            m_vPketReceiver;


	int			m_port;
	string		strUrl;


	///////////////////////////////////////////////下层//////////////////////////////////////////////////////////////////////
	//std::map<int, AcceptClient*> clients_list_; //clients map
	

};


