//#include"Mysql.h"
//
//bool ConnectDB()
//{
//	mysql_init(&m_mysql);
//	//设置数据库编码格式
//	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");
//	//连接数据库
//	if (!mysql_real_connect(&m_mysql, HOST, USER, PASSW, DBNAME, PORT, NULL, 0))
//		return false;
//	return false;
//}
//void CoseDB()
//{
//	mysql_close(&m_mysql);
//}