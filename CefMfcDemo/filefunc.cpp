#include"filefunc.h"

int strsplinum(char *str, const char*del)
{
	char *first = NULL;
	char *second = NULL;
	int num = 0;
	first = strstr(str, del);
	while (first != NULL)
	{
		second = first + 1;
		num++;
		first = strstr(second, del);
	}
	return num;
}

void split_del(char **arr, char *str, const char *del)
{
	char *s = NULL;
	char *next_token = NULL;
	s = strtok_s(str, del, &next_token);
	while (s != NULL)
	{
		*arr++ = s;
		s = strtok_s(NULL, del, &next_token);
	}
}

bool ReadData(CString sfile_x, CString sfile_y, CString &sbuff_x, CString &sbuff_y)
{
	if (!PathFileExists(sfile_x))
		return FALSE;
	if (!PathFileExists(sfile_y))
		return FALSE;

	CStdioFile file, file_Y;
	if (!file.Open(sfile_x, CFile::modeRead))
		return FALSE;
	if (!file_Y.Open(sfile_y, CFile::modeRead))
		return FALSE;

	file.ReadString(sbuff_x);
	file_Y.ReadString(sbuff_y);

	file.Close();
	file_Y.Close();
	return TRUE;
}

bool WriteData(CString sfilex_name, CString sfiley_name,CString sbuf_x,CString sbuf_y)  //��׷���ļ�����ɾ��
{
	// �ļ�����ɾ���ļ�
	/*CFile TempFile;
	if (PathFileExists(sfilex_name))
		TempFile.Remove(sfilex_name);

	if (PathFileExists(sfiley_name))
		TempFile.Remove(sfiley_name);*/

	CStdioFile file, file_Y;
	if (!file.Open(sfilex_name, CFile::modeCreate | CFile::modeWrite ))
		return FALSE;
	if (!file_Y.Open(sfiley_name, CFile::modeCreate | CFile::modeWrite ))
		return FALSE;

	file.WriteString(sbuf_x);
	file_Y.WriteString(sbuf_y);

	file.Close();
	file_Y.Close();
	return TRUE;
}

bool WriteData(CString sfilex_name,CString sbuf_x)
{
	CStdioFile file;
	if (!file.Open(sfilex_name, CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	file.WriteString(sbuf_x);
	file.Close();
	return TRUE;
}

char* CStringToChar(CString& s)			//����ʹ�� ʹ�ú�*p��NULL
{
	USES_CONVERSION;
	return T2A(s.GetBuffer(0));
}

int CStringToNum(CString s)
{
	return _ttoi(s);
}

CString stringToCString(std::string str)
{
	return str.c_str();
}

CString CharToCString(char *p)
{
	CString str = p;
	return str;
}

int CstringToList(CString s, std::list<CString> &ls)
{
	CString ssub, temp;
	temp = ssub = s;
	int Pos, ItemCount = 0;
	while ((Pos = ssub.Find(',')) != -1)
	{
		temp = ssub.Left(Pos);
		ssub = ssub.Right(ssub.GetLength() - Pos - 1);
		ls.push_back(temp);
		ItemCount++;
	}
	ls.push_back(ssub);
	ItemCount++;
	return ItemCount;
}

DWORD GetProcessIdFromName(LPCTSTR name)
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	//��ο�msdn����Ҫ�ǻ��windows��ǰ�������һ��snap�����գ��� 
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	//������һ����õ�windows�Ŀ��յ�ÿ�����̡�First ,next ���� 
	if (!Process32First(hSnapshot, &pe))
		return 0;
	CString name1, name2;
	int flag = 0, firstid;
	do
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		name1 = pe.szExeFile;
		name2 = name;
		name1.MakeUpper();
		name2.MakeUpper();
		//���в���pe�����н�����Ϣ��name������������������濴�������֣���qq.exe 

		USES_CONVERSION;
		if (strcmp(T2A(name1.GetBuffer(0)), T2A(name2.GetBuffer(0))) == 0)
		{
			//�������ID��Ҳ��ʱ����Ҫ�õ��Ľ��̵�ID 
			id = pe.th32ProcessID;
			if (flag != 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, id);
				if (hProcess != NULL)
					TerminateProcess(hProcess, 0);
			}
			else if (flag == 0)
				firstid = id;
			if (flag == 2)
			{
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, firstid);
				if (hProcess != NULL)
					TerminateProcess(hProcess, 0);
				break;
			}
			flag++;
		}

		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;
	} while (1);
	CloseHandle(hSnapshot);
	return id;
}

void split_usb(char *name, int numchar, CString &sbuff, char* cWord, int numTest)
{
	//char p[] = "{valuex:Ũ��,�¶�1,�¶�2,ʪ��1,ʪ��2}\n";
	char dest_x[128] = { "" };
	char* pTemp_x = name;
	char* pTemp_x1 = NULL;
	char* pTemp_x2 = NULL;
	int len_x;

	for (int i = 0; i < numTest; ++i)
	{
		pTemp_x1 = strchr(pTemp_x + 1, *cWord);
		len_x = pTemp_x1 - pTemp_x;
		if (i == numchar)
		{
			memset(dest_x, 0, sizeof(dest_x));
			strncpy_s(dest_x, pTemp_x, len_x);
			sbuff = dest_x;
			break;
		}
		pTemp_x = pTemp_x1 + 1;
	}
}
void del_split(char **arr, char *str, const char *del)
{
	char *s = NULL;
	char *next_token = NULL;
	s = strtok_s(str, del, &next_token);
	while (s != NULL)
	{
		*arr++ = s;
		s = strtok_s(NULL, del, &next_token);
	}
}