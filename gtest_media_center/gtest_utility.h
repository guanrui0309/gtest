// Utility.h: interface for the Utility class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _UTILITY_H
#define _UTILITY_H

#include "stdafx.h"
#include "media_center.h"
#include <string>

#ifndef DWORD
#define DWORD unsigned long
#endif 

#define MOVIE_INFO_INVALID 2004
#define MOVIE_NO_ERROR 0

class gtest_utility{

public:
	//==============================================================================
	/// @brief: 判断media_info是否存在
	/// @param: media_handle_t handle media句柄
	/// @param[out]: stream_info_t* info 媒体流数组指针
	/// @return:media_info获取成功返回true,获取失败返回false
	///=============================================================================
	static bool is_media_info(media_handle_t handle, media_info_t* info);

	//==============================================================================
	/// @brief: 
	/// @param: 
	/// @param: 
	/// @return:
	///=============================================================================
	static uint32_t get_listening_port(const char* status, const char* path);

	//==============================================================================
	/// @brief: 将wchar_t转换成utf-8
	/// @param: 要转换的wchar_t字符串
	/// @return:utf-8字符串
	///=============================================================================
	static std::string wc2utf8(const wchar_t* buf);

	//==============================================================================
	/// @brief: 添加一个简单的定时器
	/// @param: 定时器的时间，单位为ms
	/// @return:定时器到时返回true
	///=============================================================================
	static bool add_timer(DWORD millisecond);
};

#endif // _UTILITY_H