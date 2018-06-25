#ifndef _FRAMWORKNM_CONSTANT_H_
#define _FRAMWORKNM_CONSTANT_H_

#include <string>
using namespace std;

namespace FramworkNmConst
{
	//const string gc_CtrQuit		            = "0";				//�˳���������
	//const string gc_CtrRestar		        = "1";				//������������
	//const string gc_CtrStar			        = "2";				//������������
	//const string gc_CtrDetach			    = "3";				//detach��������
	//const string gc_CtrAttach			    = "4";				//attach��������

	//const int gc_nThreadRun					= 0;				//����
	//const int gc_nThreadBlock				= 1;				//����
	//const int gc_nThreadQuit				= 2;				//�˳�

	//const int gc_nTcpInit					= 0;				//��ʼ��
	//const int gc_nTcpConneted				= 1;				//��������
	//const int gc_nTcpDisConneted			= 2;				//�����ж�

	//const int gc_ProceRun				    = 0;				//����    ��������״̬
	//const int gc_ProceStop					= 1;				//δ����
	//const int gc_ProceNoHeart				= 2;				//������

	//MIB
	const std::string mibCpuRadio			= "1.1.1.1.1";		//cpuʹ����
	const std::string mibCpuTemperature		= "1.1.1.1.2";		//cpu�¶�

	const std::string mibEmsTotal			= "1.1.1.2.1.1";		//�ڴ�����
	const std::string mibEmsUse				= "1.1.1.2.1.2";		//�ڴ�ʹ����
	const std::string mibEmsRadio			= "1.1.1.2.1.3";		//�ڴ�ʹ����


	const std::string mibDiskNum			= "1.1.1.3.1";		//Ӳ�̷�����
	const std::string mibPartIndex		    = "1.1.1.3.2.1.1";	//Ӳ�̷�������
	const std::string mibDiskPhyTotal		= "1.1.1.3.2.1.2";	//Ӳ�̵�����������С
	const std::string mibDisk_Used			= "1.1.1.3.2.1.3";	//Ӳ���Ѿ�ʹ�õĴ�С
	const std::string mibDisk_Used_Ratio    = "1.1.1.3.2.1.4";	//Ӳ��ʹ����
	const std::string mibDiskTemperature    = "1.1.1.3.3";		//Ӳ���¶�

	const std::string gc_sThreadNum			= "1.1.2.1";		//�߳�����
	const std::string gc_sThreadIdx			= "1.1.2.2.1.1";	//�߳�����
	const std::string gc_sThreadState		= "1.1.2.2.1.2";	//�߳�״̬

	const std::string gc_sTcpLocalIp		= "1.1.3.2.1.2";	//����IP
	const std::string gc_sTcpLocalPort		= "1.1.3.2.1.3";	//���ض˿�
	const std::string gc_sTcpRemoteIp		= "1.1.3.2.1.4";	//�Զ�IP
	const std::string gc_sTcpRemotePort		= "1.1.3.2.1.5";	//�Զ˶˿�
	const std::string gc_sTcpState			= "1.1.3.2.1.6";	//����״̬
	const std::string gc_sTcpInBytesAve		= "1.1.3.2.1.7";	//ƽ�����ֽ���
	const std::string gc_sTcpInBytesTotal	= "1.1.3.2.1.8";	//�����ֽ���
	const std::string gc_sTcpOutBytesAve	= "1.1.3.2.1.9";	//ƽ�����ֽ���
	const std::string gc_sTcpOutBytesTotal		= "1.1.3.2.1.A";	//�ܳ��ֽ���
	const std::string gc_sTcpOutBufBytes		= "1.1.3.2.1.B";	//���ͻ����ֽ���
	const std::string gc_sTcpOutBufPkts			= "1.1.3.2.1.C";	//���ͻ��汨�ĸ���	
	const std::string gc_sTcpOutBufBytesTotal	= "1.1.3.2.1.D";	//���ͻ����ֽ����ۼ�
	const std::string gc_sTcpOutBufPktsTotal	= "1.1.3.2.1.E";	//���ͻ��汨�ĸ����ۼ�
	const std::string gc_sTcpOutBufCount		= "1.1.3.2.1.F";	//���ͻ��汨�Ĵ���

	const std::string mib_NodeId		    = "1.2.6.1.1.1";	//���ID     ���¼
	const std::string mib_NodeSta    	    = "1.2.6.1.1.2";	//���״̬
	const std::string mib_NodeCtr			= "1.2.6.1.1.3";	//������  0 1 2 ������ֹͣ����ʼ
	const std::string mibQueNum 		    = "1.1.4.1.1.2";	//�����б�������
}

#endif