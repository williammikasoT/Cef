#pragma once
#include "mysql/mysql.h"
#include "stddef.h"
#define HOST	"localhost"
#define USER	"root"
#define PASSW	"secret"
#define DBNAME  "cefdata"		
#define PORT     3306

#pragma comment(lib, "mysql/libmysql.lib")

MYSQL m_mysql;
//bool ConnectDB();
//void CoseDB();