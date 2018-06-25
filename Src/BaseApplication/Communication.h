#pragma once


struct head
{
	char  type[6];
	char  len[6];
};

struct login
{
	char  user[36];
	char  pswd[36];
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
			memcpy(&m_head, data, 12);
			memcpy(&m_content,data+12,len-12);
		}
	}

public:
	head  m_head;
	T     m_content;
};

typedef package<login> Slogin;