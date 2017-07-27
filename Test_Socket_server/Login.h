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
	// 用户名
	CString strUsername;
	// 登录密码
	CString strPassword;
	afx_msg void OnBnClickedLoginButton();
	BOOL login_succeed;
};
class VspdCToMySQL 
{
public:
      
       //变量
       //MYSQL mysql;
 
       /*
       构造函数和稀构函数
       */
       VspdCToMySQL();
       ~VspdCToMySQL();
 
       /*
       主要的功能：
       初始化数据库
       连接数据库
       设置字符集
 
       入口参数：
       host ：MYSQL服务器IP
       port:数据库端口
       Db：数据库名称
       user：数据库用户
       passwd：数据库用户的密码
       charset：希望使用的字符集
       Msg:返回的消息，包括错误消息
 
       出口参数：
       int ：0表示成功；1表示失败
       */
       int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,char * Msg);
 
       /*
       主要的功能：
       查询数据
 
       入口参数：
       SQL：查询的SQL语句
       Cnum:查询的列数
       Msg:返回的消息，包括错误消息
 
       出口参数：
       string 准备放置返回的数据，多条记录则用0x06隔开,多个栏位用0x05隔开
       如果 返回的长度＝ 0，责表示舞结果
       */
//        CString SelectData(char * SQL,int Cnum ,char * Msg);
// 	   string VspdCToMySQL::SelectData(char * SQL,int Cnum,char * Msg)
// 	   {
// 		   MYSQL_ROW m_row;
// 		   MYSQL_RES *m_res;
// 		   char sql[2048];
// 		   sprintf(sql,SQL);
// 		   int rnum = 0;
// 		   char rg = 0x06;//行隔开
// 		   char cg = {0x05};//字段隔开
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
       主要功能：
       插入数据
      
       入口参数
       SQL：查询的SQL语句
       Msg:返回的消息，包括错误消息
 
       出口参数：
       int ：0表示成功；1表示失败
       */
       int InsertData(char * SQL,char * Msg);
 
       /*
       主要功能：
       修改数据
      
       入口参数
       SQL：查询的SQL语句
       Msg:返回的消息，包括错误消息
 
       出口参数：
       int ：0表示成功；1表示失败
       */
       int UpdateData(char * SQL,char * Msg);
 
 
       /*
       主要功能：
       删除数据
      
       入口参数
       SQL：查询的SQL语句
       Msg:返回的消息，包括错误消息
 
       出口参数：
       int ：0表示成功；1表示失败
       */
       int DeleteData(char * SQL,char * Msg);
      
       /*
       主要功能：
       关闭数据库连接
       */
       void CloseMySQLConn();
 
};
