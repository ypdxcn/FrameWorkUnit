#pragma once

const int HEAD_TYPE_LEN  = 8;
const int HEAD_LEN_LEN   = 8;
const int USER_NAME_LEN  = 16;
const int PASSWOD_LEN    = 16;

struct head
{
	char  type[HEAD_TYPE_LEN];
	char  len[HEAD_LEN_LEN];
};

struct login
{
	char  user[USER_NAME_LEN];
	char  pswd[PASSWOD_LEN];
};



template<typename T>
class  package
{
public:
	package() {}
	~package() {}

	void Decode(const char *data, int len)
	{
		if (len > 12)
		{
			memcpy(m_head.type, data, HEAD_TYPE_LEN);
			memcpy(m_head.len, data+ HEAD_TYPE_LEN, HEAD_LEN_LEN);

			//memcpy(&m_content,data+ HEAD_TYPE_LEN+ HEAD_LEN_LEN,len-12);
		}
	}

public:
	head  m_head;
	T     m_content;
};

typedef package<login> Slogin;