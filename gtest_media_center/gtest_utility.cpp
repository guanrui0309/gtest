// Utility.cpp: implementation of the Utility class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "gtest_utility.h"
#include "media_center.h"
#include <stdio.h>
#include <vector>
#ifdef WIN32
#include <windows.h>
#endif

//使用GetTickCount()制造一个定时器
//select(0, NULL, NULL, NULL, &wait)在windows中不好使，返回WSAEINVAL(10022)
//大于3秒没有返回就认为服务器出错了
bool gtest_utility::is_media_info(media_handle_t handle, media_info_t* info){
	DWORD dw_old_time = GetTickCount();
	while(true){
		DWORD dw_new_time = GetTickCount();
		if((dw_new_time - dw_old_time) >= 3*1000){
			int32_t result = media_center_get_media_info(handle, info);
			if( (MOVIE_NO_ERROR == result) || (MOVIE_INFO_INVALID == result)){
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

uint32_t gtest_utility::get_listening_port(const char* status, const char* path){
	return 0;
}

std::string gtest_utility::wc2utf8(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);
	return std::string(&utf8[0]);
}

bool gtest_utility::add_timer(DWORD millisecond){
	DWORD dw_old_time = GetTickCount();
	while(true){
		DWORD dw_new_time = GetTickCount();
		if((dw_new_time - dw_old_time) > millisecond){
			return true;
		}
	}
}