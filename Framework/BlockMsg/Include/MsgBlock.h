#ifndef _MSG_BLOCK_H_
#define _MSG_BLOCK_H_
#include "MessageImpl.h"
#include "MsgDef.h"
#include "BlockMsg.h"

/*
 * MsgBlock ָ��״���ݽṹ����Ϣ����
 * ��Ϣ��һ�������ֶ�������ɣ���һ���������ֶ�ָ������Ϣ�ı�ʶ����ͬ��ʶ����
 * Ϣ���ܾ��в�ͬ�ֶ���ϡ�
 */
class CMessageImpl;
class BLOCKMSG_CLASS CMsgBlock
{
public:
	virtual ~CMsgBlock(void);
	CMsgBlock(CMessage& msg,size_t nDefaultWriteBufSize = 1024, size_t nMsgLengthBytes = 4);
	CMsgBlock(size_t nDefaultWriteBufSize = 1024, size_t nMsgLengthBytes = 4);
	CMsgBlock(const CMsgBlock& msgBlk);
	CMsgBlock& operator=(const CMsgBlock& msgBlk);

	const char * GetData(void);
	size_t DataLength(void);

	CMessage& GetMsg(){return m_Msg;}
protected:
	bool ReadInt8(int nFieldID);
	bool ReadInt16(int nFieldID);
	bool ReadInt32(int nFieldID);
	bool ReadOctStr(int nFieldID, size_t nSize);
	bool ReadBinary(int nFieldID, size_t nSize);
	bool ReadVLD8(int nFieldID);
	bool ReadVLD16(int nFieldID);
	bool ReadVLD32(int nFieldID);
	bool ReadMFS8(int nFieldID, size_t nFieldSize);
	bool ReadREC8(int nFieldID, size_t nRecSize);
	bool ReadREC16(int nFieldID, size_t nRecSize);
	bool ReadVLS(int nFieldID);

	bool WriteInt8(int nFieldID);
	bool WriteInt16(int nFieldID);
	bool WriteInt32(int nFieldID);
	bool WriteOctStr(int nFieldID, size_t nSize, char cBlank = '\0');
	bool WriteBinary(int nFieldID, size_t nSize, char cBlank = '\0');
	bool WriteVLD8(int nFieldID);
	bool WriteVLD16(int nFieldID);
	bool WriteVLD32(int nFieldID);
	bool WriteMFS8(int nFieldID, size_t nFieldSize);
	bool WriteREC8(int nFieldID, size_t nRecSize);
	bool WriteREC16(int nFieldID, size_t nRecSize);
	bool WriteVLS(int nFieldID);

	CMessageImpl  m_Msg;	
	
	const char * m_pReadBuf; // ���ڽ����Ļ�������ַ
	char * m_pWriteBuf; // ��������Ļ�������ַ

	size_t m_nOffset;
	size_t m_nBufLen;
	size_t m_nDefaultWriteBufSize; // �����������Ĭ�ϴ�С
	size_t m_nMsgLengthBytes; // ��Ϣ�����ֶγߴ�

	bool WriteBuf(const void * pData, size_t nSize, bool bPadding = false);
};

/*
 * �Ը������͵���Ϣ�����ж���ĺ�
 * Offset: ��Ϣ����ʶ�ֶ��ڰ��е�ƫ����
 * Length: ��Ϣ����ʶ�ֶεĳ��ȣ��ٶ�������int�ĳ���
 */
#define BEGIN_PKG_DECODE(Offset, Length) \
public: \
	void Decode(const char * pBuf, size_t nSize) \
	{ \
		m_nOffset = 0; \
		m_pReadBuf = pBuf; \
		m_nBufLen = nSize; \
		unsigned int uiCmdID = 0; \
		if (Length > sizeof(uiCmdID)) \
			return ; \
		memcpy(&uiCmdID, m_pReadBuf + Offset, Length); \
		uiCmdID = ntohl(uiCmdID);

// CmdID: ��Ϣ����ʶ , pFunc: ��Ӧ��ͨ�Ű�������
#define PKG_DECODE_HANDLE(CmdID, Func) \
		if (uiCmdID == CmdID) \
			Proc##Func(); 

#define END_PKG_DECODE() \
		return; \
	}

#define BEGIN_PKG_ENCODE \
public: \
	const char* Encode(size_t & nSize) \
	{ \
	    unsigned int uiCmdID = 0; \
	    m_Msg.GetField(MSG_CMD_ID, uiCmdID);

// CmdID: ��Ϣ����ʶ  Func: ��Ӧ��ͨ�Ű�������
#define PKG_ENCODE_HANDLE(CmdID,Func) \
        if (CmdID == uiCmdID) \
		    return Encode##Func(nSize);

#define END_PKG_ENCODE() \
		return 0; \
	}

/*
 * ��ÿ��ͨ�Ű����ж���ĺ�
 * Func : ͨ��ԭ�ﴦ����������
 */
#define BEGIN_PKG_FIELD(Func) \
private: \
	const char* Encode##Func(size_t & nSize) \
	{ \
	    nSize = 0; \
		if (m_pWriteBuf != NULL) \
		{ \
			nSize = m_nOffset; \
			return m_pWriteBuf; \
		} \
		m_nOffset = 0; \
		m_nBufLen = m_nDefaultWriteBufSize; \
		m_pWriteBuf = (char *)malloc(m_nBufLen); \
		bool bRet = Proc##Func(false); \
		if (!bRet) \
		{ \
			m_nOffset = 0; \
			nSize = 0; \
			if (0 != m_pWriteBuf) \
			{ \
				free(m_pWriteBuf); \
				m_pWriteBuf = 0; \
			} \
			return 0; \
		} \
		if (m_nMsgLengthBytes == 1) \
			*m_pWriteBuf = static_cast<unsigned char>(DataLength()); \
		else if (m_nMsgLengthBytes == 2) \
			*(unsigned short *)m_pWriteBuf = ntohs(static_cast<unsigned short>(DataLength())); \
		else if (m_nMsgLengthBytes == 4) \
			*(unsigned int *)m_pWriteBuf = ntohl(static_cast<unsigned int>(DataLength())); \
		nSize = m_nOffset; \
		return m_pWriteBuf; \
	} \
private: \
	bool Proc##Func(bool bDecode = true) \
	{ \
		bool bRet = true;

// ����ֶΣ�����ʱ�������Σ�����ʱ��'\0'
#define FIELD_PADDING(Length) \
		if (bDecode) \
		{ \
			if (m_nOffset + Length > m_nBufLen) \
				return false; \
			m_nOffset += Length; \
		} \
		else \
		{ \
			bRet = WriteBuf(NULL, Length, true); \
		} \
		if (!bRet) return false;

// 8λ�����ֶ�
#define FIELD_INT8(FieldID) \
		if (bDecode) \
			bRet = ReadInt8(FieldID); \
		else \
			bRet = WriteInt8(FieldID); \
		if (!bRet) return false;

// 16λ�����ֶ�
#define FIELD_INT16(FieldID) \
		if (bDecode) \
			bRet = ReadInt16(FieldID); \
		else \
			bRet = WriteInt16(FieldID); \
		if (!bRet) return false;

// 32λ�����ֶ�
#define FIELD_INT32(FieldID) \
		if (bDecode) \
			bRet = ReadInt32(FieldID); \
		else \
			bRet = WriteInt32(FieldID); \
		if (!bRet) return false;

// ���8λ�ַ����ɵ��ֶΣ�������'\0'�ַ�
#define FIELD_OCTSTR(FieldID, Length) \
		if (bDecode) \
			bRet = ReadOctStr(FieldID, Length); \
		else \
			bRet = WriteOctStr(FieldID, Length); \
		if (!bRet) return false;

// ���8λ�ַ����ɵ��ֶΣ��ɰ���'\0'�ַ�
#define FIELD_BINARY(FieldID, Length) \
		if (bDecode) \
			bRet = ReadBinary(FieldID, Length); \
		else \
			bRet = WriteBinary(FieldID, Length); \
		if (!bRet) return false;

// �ɱ䳤���ַ���(Variable Length String)�ֶΣ��ַ�����'\0'��β
#define FIELD_VLS(FieldID) \
		if (bDecode) \
		{ \
			bRet = ReadVLS(FieldID); \
		} \
		else \
		{ \
			bRet = WriteVLS(FieldID); \
		} \
		if (!bRet) return false;

// �ɱ䳤������(Variable Length Data)�ֶΣ����������ֽ�8λ���ͱ�ʾ
#define FIELD_VLD8(FieldID) \
		if (bDecode) \
		{ \
			bRet = ReadVLD8(FieldID); \
		} \
		else \
		{ \
			bRet = WriteVLD8(FieldID); \
		} \
		if (!bRet) return false;

// �ɱ䳤������(Variable Length Data)�ֶΣ����������ֽ�16λ���ͱ�ʾ
#define FIELD_VLD16(FieldID) \
		if (bDecode) \
		{ \
			bRet = ReadVLD16(FieldID); \
		} \
		else \
		{ \
			bRet = WriteVLD16(FieldID); \
		} \
		if (!bRet) return false;

// �ɱ䳤������(Variable Length Data)�ֶΣ����������ֽ�32λ���ͱ�ʾ
#define FIELD_VLD32(FieldID) \
		if (bDecode) \
		{ \
			bRet = ReadVLD32(FieldID); \
		} \
		else \
		{ \
			bRet = WriteVLD32(FieldID); \
		} \
		if (!bRet) return false;

/*
 * ���ֶ��ַ���(Multiple Fields String)�ֶΣ��ֶθ��������ֽ�8λ���ͱ�ʾ��ÿ��
 * �εĳ��ȹ̶�����,��ƴ�ӷ���FieldIDָ�����ֶ���
 */
#define FIELD_MFS8(FieldID, Length) \
		if (bDecode) \
			bRet = ReadMFS8(FieldID, Length); \
		else \
			bRet = WriteMFS8(FieldID, Length); \
		if (!bRet) return false;

/*
 * ���¼�ֶΣ���¼���������ֽ�8λ���ͱ�ʾ��ÿ��¼
 * �ĳ��ȹ̶�ΪLength��
 */
#define FIELD_REC8(FieldID, Length) \
		if (bDecode) \
			bRet = ReadREC8(FieldID, Length); \
		else \
			bRet = WriteREC8(FieldID, Length); \
		if (!bRet) return false;

/*
 * ���¼�ֶΣ���¼�����������ֽ����ͱ�ʾ��ÿ��¼
 * �ĳ��ȹ̶�ΪLength��
 */
#define FIELD_REC16(FieldID, Length) \
		if (bDecode) \
			bRet = ReadREC16(FieldID, Length); \
		else \
			bRet = WriteREC16(FieldID, Length); \
		if (!bRet) return false;

// �Զ����ֶΣ����Զ��崦�������д����������ݽ���
#define FIELD_CUSTOM(FieldID, CustomFunc) \
		bRet = CustomFunc(FieldID, bDecode); \
		if (!bRet) return false;

#define END_PKG_FIELD() \
		return bRet; \
	}

#endif // _MSG_BLOCK_H_
