#pragma once


// CLogin dialog

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLogin();

// Dialog Data
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// �û���
	CString strUsername;
	// ��¼����
	CString strPassword;
	afx_msg void OnBnClickedLoginButton();
	BOOL login_succeed;
};
class VspdCToMySQL 
{
public:
      
       //����
       //MYSQL mysql;
 
       /*
       ���캯����ϡ������
       */
       VspdCToMySQL();
       ~VspdCToMySQL();
 
       /*
       ��Ҫ�Ĺ��ܣ�
       ��ʼ�����ݿ�
       �������ݿ�
       �����ַ���
 
       ��ڲ�����
       host ��MYSQL������IP
       port:���ݿ�˿�
       Db�����ݿ�����
       user�����ݿ��û�
       passwd�����ݿ��û�������
       charset��ϣ��ʹ�õ��ַ���
       Msg:���ص���Ϣ������������Ϣ
 
       ���ڲ�����
       int ��0��ʾ�ɹ���1��ʾʧ��
       */
       int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,char * Msg);
 
       /*
       ��Ҫ�Ĺ��ܣ�
       ��ѯ����
 
       ��ڲ�����
       SQL����ѯ��SQL���
       Cnum:��ѯ������
       Msg:���ص���Ϣ������������Ϣ
 
       ���ڲ�����
       string ׼�����÷��ص����ݣ�������¼����0x06����,�����λ��0x05����
       ��� ���صĳ��ȣ� 0�����ʾ����
       */
//        CString SelectData(char * SQL,int Cnum ,char * Msg);
// 	   string VspdCToMySQL::SelectData(char * SQL,int Cnum,char * Msg)
// 	   {
// 		   MYSQL_ROW m_row;
// 		   MYSQL_RES *m_res;
// 		   char sql[2048];
// 		   sprintf(sql,SQL);
// 		   int rnum = 0;
// 		   char rg = 0x06;//�и���
// 		   char cg = {0x05};//�ֶθ���
// 
// 		   if(mysql_query(&mysql,sql) != 0)
// 		   {
// 			   Msg = "select ps_info Error";
// 			   return "";
// 		   }
// 		   m_res = mysql_store_result(&mysql);
// 
// 		   if(m_res==NULL)
// 		   {
// 			   Msg = "select username Error";
// 			   return "";
// 		   }
// 		   string str("");
// 		   while(m_row = mysql_fetch_row(m_res))
// 		   {
// 			   for(int i = 0;i < Cnum;i++)
// 			   {
// 				   str += m_row[i];
// 				   str += rg;
// 			   }
// 			   str += rg;             
// 			   rnum++;
// 		   }
// 
// 		   mysql_free_result(m_res);
// 
// 		   return str;
// 	   }
       /*
       ��Ҫ���ܣ�
       ��������
      
       ��ڲ���
       SQL����ѯ��SQL���
       Msg:���ص���Ϣ������������Ϣ
 
       ���ڲ�����
       int ��0��ʾ�ɹ���1��ʾʧ��
       */
       int InsertData(char * SQL,char * Msg);
 
       /*
       ��Ҫ���ܣ�
       �޸�����
      
       ��ڲ���
       SQL����ѯ��SQL���
       Msg:���ص���Ϣ������������Ϣ
 
       ���ڲ�����
       int ��0��ʾ�ɹ���1��ʾʧ��
       */
       int UpdateData(char * SQL,char * Msg);
 
 
       /*
       ��Ҫ���ܣ�
       ɾ������
      
       ��ڲ���
       SQL����ѯ��SQL���
       Msg:���ص���Ϣ������������Ϣ
 
       ���ڲ�����
       int ��0��ʾ�ɹ���1��ʾʧ��
       */
       int DeleteData(char * SQL,char * Msg);
      
       /*
       ��Ҫ���ܣ�
       �ر����ݿ�����
       */
       void CloseMySQLConn();
 
};
