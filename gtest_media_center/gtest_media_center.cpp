// gtest_media_center.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "media_center.h"
#include "gtest/gtest.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	//testing::GTEST_FLAG(filter)="url_generator_test.*";
	//testing::GTEST_FLAG(filter)="media_info_manager_test.*";
	testing::GTEST_FLAG(filter)="media_center_test.*";
	testing::GTEST_FLAG(output) = "xml:gtest_result.xml";
	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	system("Pause");
	return result;
}

