#ifndef _VIQLOG_
#define _VIQLOG_


//#include "atlstr.h"
//#include "afx.h"
#include <map>
#include <stack>
#include <shlobj.h>
#include <iostream>
#include <fstream>
using namespace std;

#include<atlstr.h>
#include<afx.h>
typedef enum {
				LOG_DEBUG = 1,
				LOG_WARNING,
				LOG_CRITICAL
			}LOGLEVEL;


class CVLog
{
public:
	CVLog(CString strPath, LOGLEVEL level)
	{
		m_csLogFile = strPath;
		m_level = level;
		InitializeCriticalSection(&m_cs);
	}

	
	~CVLog(void)
	{
		DeleteCriticalSection(&m_cs);
	}


	void Log( CString csFunction, CString csMessage, LOGLEVEL level)
	{
		if(level<m_level)
			return;
		EnterCriticalSection(&m_cs);
		try
		{
			if( m_csLogFile != "" )
			{
				CFile cfLogfile;
				CFileException cfe;
				if (!cfLogfile.Open(m_csLogFile, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate, &cfe))
				{
					LeaveCriticalSection(&m_cs);
					return;
				}
				cfLogfile.SeekToEnd();
				CTime ctDateTime = CTime::GetCurrentTime();
				CString csDateTime = ctDateTime.Format("%Y-%m-%d %H:%M:%S");
				DWORD ThreadID = GetCurrentThreadId();
				CString strThreadID;
				strThreadID.Format("%d", ThreadID);
				CString csLogText = csDateTime + CString(" : (") + strThreadID + CString(")") + csFunction + " : " + csMessage + CString("\r\n");
				cfLogfile.Write(csLogText, csLogText.GetLength());
				cfLogfile.Close();
			}
			else
			{

			}
		}
		catch(...)
		{
			
		}
		LeaveCriticalSection(&m_cs);
		return;

	}

	static CVLog *GetInstance()
	{
		static CVLog *pLog = NULL;

		if(pLog)
			return pLog;
		else
		{
			char szPath[255];
			SHGetFolderPath(NULL, 
                             CSIDL_APPDATA, 
                             NULL, 
                             0, 
                             szPath);
			//string logpath(szPath);
			string logpath("");
			logpath.append("C:\\tmp\\VIQ\\");
			CreateDir(logpath);
			//CreateDir(logpath);
			logpath.append(CVLog::GetApplicationName(3));
			logpath.append(".log");
			CString strpath(logpath.c_str());
			pLog = new CVLog(strpath, LOG_DEBUG);
			return pLog;
		}
	}

	static void OutputLog(CString csFunction, CString csMessage, LOGLEVEL level=LOG_DEBUG)
	{
		CVLog *pLog = GetInstance();
		pLog->BackupLog();
		pLog->Log(csFunction, csMessage, level);
	}

	static void OutputLog(CString csFunction, int n, LOGLEVEL level=LOG_DEBUG)
	{
		CVLog *pLog = GetInstance();
		CString csMessage;
		csMessage.Format("%d", n);
		pLog->BackupLog();
		pLog->Log(csFunction, csMessage, level);
	}

	static void OutputLog(CString csFunction, double db, LOGLEVEL level=LOG_DEBUG)
	{
		CVLog *pLog = GetInstance();
		CString csMessage;
		csMessage.Format("%lf", db);
		pLog->BackupLog();
		pLog->Log(csFunction, csMessage, level);
	}

	static void OutputLog(double db1, double db2, LOGLEVEL level=LOG_DEBUG)
	{
		CVLog *pLog = GetInstance();
		CString csMessage;
		csMessage.Format("db1: %lf, db2: %lf", db1, db2);
		pLog->BackupLog();
		pLog->Log("", csMessage, level);
	}

	static void OutputLog(int n1, int n2, LOGLEVEL level=LOG_DEBUG)
	{
		CVLog *pLog = GetInstance();
		CString csMessage;
		csMessage.Format("int1: %d, int2: %d", n1, n2);
		pLog->BackupLog();
		pLog->Log("", csMessage, level);
	}

protected:
	////////////////////////////////////////////////////////////
	//Get application name
	//@param[in] type
	//1: return like C:\WINDOWS\explorer.exe
	//2: return like explorer.exe
	//3: return like explorer
	//@return
	static string GetApplicationName(DWORD type)
	{
		char strPathName[_MAX_PATH];
		::GetModuleFileName(NULL, strPathName, _MAX_PATH);
		string str(strPathName);
		size_t found = str.rfind("\\");
		string appname = str.substr(found+1);
		found = appname.find(".");
		appname = appname.substr(0, found);
		return appname;
	}

	static void CreateDir(string path)
	{
		string strDir;
	
		//remove file name if it has
		size_t found = path.find(".");
		if(found!=-1)
		{
			found = path.rfind("\\");
			if(found!=-1)
			{
				path = path.substr(0, found);
			}
		}

		found = path.find("\\");
		if(found==-1)
			return;
		strDir = path.substr(0, found);
		path = path.substr(found+1);
		found = path.find("\\");
		while(found!=-1)
		{
			strDir.append("\\");
			strDir.append(path.substr(0, found));
			path = path.substr(found+1);
			CreateDirectory(strDir.c_str(),NULL);
			found = path.find("\\");
		}
		strDir.append("\\");
		strDir.append(path);
		CreateDirectory(strDir.c_str(),NULL);

		return;
	}

	void BackupLog()
	{
		static int count = 0;
		if(count++>500)
		{
			count = 0;
			//check current log size
			DWORD dwLogSize;
			std::fstream f;
			f.open(m_csLogFile.GetString(),ios_base::in|ios_base::binary);
			if(!f) return;
			f.seekg(0, ios_base::end);
			dwLogSize = f.tellg();
			f.close();
			
			//2.if the log file is less than 10MB
			if(dwLogSize < 5*1024*1024)
				return;

			//remove old back up log
			string strBKLogPath = m_csLogFile.GetString();
			size_t found = strBKLogPath.find(".");
			if(found==-1)
				return;
			strBKLogPath.insert(found, "1");
			DeleteFile(strBKLogPath.c_str());

			//rename current log file to back up log file
			rename(m_csLogFile.GetString(), strBKLogPath.c_str());

		}
	}


private:
	LOGLEVEL m_level;
	CRITICAL_SECTION	m_cs;
	CString m_csLogFile;	
};


#endif