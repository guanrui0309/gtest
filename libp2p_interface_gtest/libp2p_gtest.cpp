// libp2p_interface_gtest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	//testing::GTEST_FLAG(filter)="libp2p_test.*";
	//testing::GTEST_FLAG(filter)="libp2p_task_test.*";
	//testing::GTEST_FLAG(filter) = "libp2p_vod_task_test.test_libp2p_vod_stream_seek_to_position";
	//testing::GTEST_FLAG(filter) = "libp2p_download_task_test.*";
	testing::GTEST_FLAG(filter) = "libp2p_error_test.*";
	testing::GTEST_FLAG(output) = "xml:gtest_result.xml";
	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	system("Pause");
	return result;
}

