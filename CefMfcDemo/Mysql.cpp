//#include"Mysql.h"
//
//bool ConnectDB()
//{
//	mysql_init(&m_mysql);
//	//�������ݿ�����ʽ
//	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");
//	//�������ݿ�
//	if (!mysql_real_connect(&m_mysql, HOST, USER, PASSW, DBNAME, PORT, NULL, 0))
//		return false;
//	return false;
//}
//void CoseDB()
//{
//	mysql_close(&m_mysql);
//}