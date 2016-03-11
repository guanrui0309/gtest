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
	/// @brief: �ж�media_info�Ƿ����
	/// @param: media_handle_t handle media���
	/// @param[out]: stream_info_t* info ý��������ָ��
	/// @return:media_info��ȡ�ɹ�����true,��ȡʧ�ܷ���false
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
	/// @brief: ��wchar_tת����utf-8
	/// @param: Ҫת����wchar_t�ַ���
	/// @return:utf-8�ַ���
	///=============================================================================
	static std::string wc2utf8(const wchar_t* buf);

	//==============================================================================
	/// @brief: ���һ���򵥵Ķ�ʱ��
	/// @param: ��ʱ����ʱ�䣬��λΪms
	/// @return:��ʱ����ʱ����true
	///=============================================================================
	static bool add_timer(DWORD millisecond);
};

#endif // _UTILITY_H