///////////////////////////////////////////////////////////////////////////////
// utilities.cpp
///////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "gtest_utilities.h"

#ifdef WIN32
#include <windows.h>
#endif

#ifdef WIN32
#pragma warning(disable: 4996)
#endif

using namespace std;

namespace gtest_utils
{
	//////////////////////////////////
bool string_to_wstring(const std::string &str,std::wstring &wstr)
{
	int nLen = (int)str.length();
	wstr.resize(nLen,L' ');
	int nResult = MultiByteToWideChar(CP_ACP,0,(LPCSTR)str.c_str(),nLen,(LPWSTR)wstr.c_str(),nLen);
	if (nResult == 0)
	{
		return false;
	}
	return true;
}

bool check_folder_exist(const std::string &strPath)
{
	WIN32_FIND_DATA  wfd;
	bool rValue = false;
	HANDLE hFind = NULL;

#ifdef UNICODE
	wstring w_strPath;
	if (string_to_wstring(strPath, w_strPath))
	{
		hFind = FindFirstFile(w_strPath.c_str(), &wfd);
	}
#else
	 hFind = FindFirstFile(strPath.c_str(), &wfd);
#endif

	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = true;   
	}

	FindClose(hFind);
	return rValue;
}

bool sleep(DWORD millisecond)
{
	DWORD dw_old_time = GetTickCount();
	while(true){
		DWORD dw_new_time = GetTickCount();
		if((dw_new_time - dw_old_time) > millisecond){
			return true;
		}
	}
}

} //namespace gtest_utils