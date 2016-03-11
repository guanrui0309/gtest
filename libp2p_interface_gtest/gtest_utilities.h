///////////////////////////////////////////////////////////////////////////////
// gtest_utilities.h
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "stdafx.h"
#include <string>

#ifndef DWORD
#define DWORD unsigned long
#endif

namespace gtest_utils
{
	//////////////////////////////////////////////
	
	bool check_folder_exist(const std::string &strPath);

	bool string_to_wstring(const std::string &str,std::wstring &wstr);

	bool sleep(DWORD millisecond);


} //namespace gtest_utils
