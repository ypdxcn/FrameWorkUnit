1  Ŀ¼�ṹ 
1.1 ��Ŀ¼�ṹ��
  ...CPlusFramwork
  |- Utility ����ģ��(.dll/.a)
  |  |- Include ͷ�ļ�Ŀ¼
  |  |- Src Դ�ļ�Ŀ¼
  |- NetMgr ���ܿ��(.dll/.a)
  |  |- Include ͷ�ļ�Ŀ¼
  |  |- Src Դ�ļ�Ŀ¼
  |- CommFramwork ͨѶ���(.dll/.a)
  |  |- Include ͷ�ļ�Ŀ¼
  |  |- Src Դ�ļ�Ŀ¼
  |- FramworkAp	ͨѶ��ܽ����(�ӿ�Э��,���в���.dll/.a) 
  |  |- Include ͷ�ļ�Ŀ¼
  |  |- Src Դ�ļ�Ŀ¼
  |- NetMgrAgent ���ܴ���ʵ�ֵ�H1/H2�ӿ�Э��(.dll/.a) 
  |  |- Include
  |  |- Src Դ�ļ�Ŀ¼
  |- Include windowsƽ̨�ⲿ������ļ�
  |  |- pthread windowsƽ̨posix�߳̿�ͷ�ļ�
  |  |- oci windowsƽ̨ORACLE OCIͷ�ļ�
  |- lib windowsƽ̨�ⲿ���ļ�
  |  |- pthread windowsƽ̨posix�߳̿���ļ�
  


1.2 ��Ŀ¼���ļ�˵��
Root_2005.sln  vs2005��������ļ�(��������windowsƽ̨��Ӧ��)
Root_2008.sln  vs2008��������ļ�(��������windowsƽ̨��Ӧ��)
Risk_src.bat  unixƽ̨����Ŀ¼Դ�ļ������������ļ�
Risk_aix.bat  aixƽ̨make�ļ������������ļ�
Risk_hpunix.bat hpunixƽ̨make�ļ������������ļ�
Risk_linux.bat linuxƽ̨make�ļ������������ļ�


2 ����˵��
2.1 windowsƽ̨
   1 ��VS2005
   2 ����Root_2005.sln�������
   3 ������Ҫ�������Ӧ�ù���

2.1.1 ���߻�����(Utility)����˵��
    ���߻����⹤����Utility��
    ����ɹ�������ļ�:Utility.dll,Utility.lib
    ����ɹ������Ŀ¼:binĿ¼ 
    ע�⣺winodwsƽ̨posix�߳̿�dll/lib��Ŀ¼λ��
    
2.1.2 ϵͳ��ؽӿڿ�(NetMgr)����˵��
    ϵͳ��ؽӿڿ⹤����NetMgr���������̣�Utility�������ú�������ϵ��
���뱾���̻��Զ������������̡�
    ����ɹ�������ļ�:NetMgr.dll,NetMgr.lib
    ����ɹ������Ŀ¼:binĿ¼ 
    ע�⣺winodwsƽ̨posix�߳̿�dll/lib��Ŀ¼λ��
    
2.1.3 ͨѶ��ܿ�(CommFramwork)����˵��
    ͨѶ��ܿ⹤����CommFramwork���������̣�Utility��NetMgr�������ú�������ϵ��
���뱾���̻��Զ������������̡�
    ����ɹ�������ļ�:CommFramwork.dll,CommFramwork.lib
    ����ɹ������Ŀ¼:binĿ¼ 
    ע�⣺winodwsƽ̨posix�߳̿�dll/lib��Ŀ¼λ��
         
2.1.4 ���������Ľӿڿ�(FramworkAp)����˵��
    ͨѶ��ܿ⹤����FramworkAp���������̣�Utility��NetMgr��CommFramwork��
�����ú�������ϵ�����뱾���̻��Զ������������̡�
    ����ɹ�������ļ�:FramworkAp.dll,FramworkAp.lib
    ����ɹ������Ŀ¼:binĿ¼ 
    ע�⣺winodwsƽ̨posix�߳̿�dll/lib��Ŀ¼λ��
             
2.1.5 ϵͳ���ʵ�ֿ�(NetMgrAgent)����˵��
    ͨѶ��ܿ⹤����NetMgrAgent���������̣�Utility��NetMgr��CommFramwork��FramworkAp��
�����ú�������ϵ�����뱾���̻��Զ������������̡�
    ����ɹ�������ļ�:NetMgrAgent.dll,NetMgrAgent.lib
    ����ɹ������Ŀ¼:binĿ¼ 
    ע�⣺winodwsƽ̨posix�߳̿�dll/lib��Ŀ¼λ��
     
2.2 Linuxƽ̨
1 ִ��Risk_src.bat(�������D�̣��������޸��������ļ�)
2 ִ��Risk_linux.bat(�������D�̣��������޸��������ļ�)
3 ʹ��FTP��D:\Unix_Linux_verĿ¼�µ������ļ��ϴ���Linux���뻷��������ΪRootĿ¼
4 ����RootĿ¼
5 ִ��make�������Զ������ؼ���ؿ�
    ע�⣺���߻�����(Utility)��ͨѶ��ܿ�(CommFramwork)��ϵͳ��ؿ�(NetMgr��NetMgrAgent)��
�������Ľӿڿ�(FramworkAp)��������ļ�Ϊ��̬��.a�����Ŀ¼Ϊ�û�Ŀ¼ ~/lib��

2.3 HP_Unixƽ̨(����g++ 4.2ƽ̨�ϳɹ����룬��ȷ���Ѿ���ȷ��װgcc)
1 ִ��Risk_src.bat(�������D�̣��������޸��������ļ�)
2 ִ��Risk_hpunix.bat(�������D�̣��������޸��������ļ�)
3 ʹ��FTP��D:\Unix_Linux_verĿ¼�µ������ļ��ϴ���HP_Unix���뻷��������ΪRootĿ¼
4  ����RootĿ¼
5 ִ��gmake -f mkhp.gcc�������Զ������ؼ���ؿ�
    ע�⣺���߻�����(Utility)��ͨѶ��ܿ�(CommFramwork)��ϵͳ��ؿ�(NetMgr��NetMgrAgent)��
�������Ľӿڿ�(FramworkAp)��������ļ�Ϊ��̬��.a�����Ŀ¼Ϊ�û�Ŀ¼ ~/lib��

2.4 AIXƽ̨(��ʹ��xlC_r 6.0�ɹ����룬��ȷ���Ѿ���ȷ��װIBM��Ӧ�汾�ı��뻷��)
1 ִ��Risk_src.bat(�������D�̣��������޸��������ļ�)
2 ִ��Risk_aix.bat(�������D�̣��������޸��������ļ�)
3 ʹ��FTP��D:\Unix_Linux_verĿ¼�µ������ļ��ϴ���AIX���뻷��������ΪRootĿ¼
4 ����RootĿ¼
5 ִ��make -f mk.vac�������Զ������ؼ���ؿ�
    ע�⣺���߻�����(Utility)��ͨѶ��ܿ�(CommFramwork)��ϵͳ��ؿ�(NetMgr��NetMgrAgent)��
�������Ľӿڿ�(FramworkAp)��������ļ�Ϊ��̬��.a�����Ŀ¼
Ϊ�û�Ŀ¼ ~/lib��

3 �������ļ�����˵��        
    Utility.dll
    NetMgr.dll
    CommFramwork.dll
    FramworkAp.dll
    NetMgrAgent.dll
    



