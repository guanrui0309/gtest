#include "stdafx.h"
#include "media_center.h"
#include "gtest/gtest.h"
#include "libp2p.h"
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include "gtest_utility.h"

#define STREAM_SERVICE_PORT 18080

class media_center_test : public testing::Test{

protected:
	//方法在第一个TestCase之前执行
	static void SetUpTestCase(){
		path = "c:\\wahaha";
		url = "servicetype=1&uid=4995606&fid=A70A09721538A3C9273E2AE8C2461141";
		token = "";
		STREAM_INFO_COUNT = 2;
	}

	//方法在最后一个TestCase之后执行
	static void TearDownTestCase(){
		path = NULL;
		url = NULL;
		token = NULL;
		STREAM_INFO_COUNT = 0;
	}

	//方法在每个TestCase之前执行
	virtual void SetUp(){

	}

	//方法在每个TestCase之后执行
	virtual void TearDown(){
	}

	static char* path;
	static char* url;
	static char* token;
	static unsigned int STREAM_INFO_COUNT;
};

char* media_center_test::path = NULL;
char* media_center_test::url = NULL;
char* media_center_test::token = NULL;
unsigned int media_center_test::STREAM_INFO_COUNT = 0;

void MEDIA_API media_handle_callback(media_handle_t handle, 
	media_handle_state_t state, int32_t error){

}

//自定义输出格式 - 检查create_media_handle
testing::AssertionResult assert_handle(const char* m_expr, const char* n_expr, const char* url, const char* token)
{
	media_handle_t handle = media_center_create_media_handle(url, token, media_handle_callback);
	if (handle > 0 && handle != 10000)
		return testing::AssertionSuccess();
	testing::Message msg;
	msg << "use url :"<< m_expr <<" and token: " << n_expr << " but create media handle failed, handle value: " << handle;
	return testing::AssertionFailure(msg);
}

TEST_F(media_center_test, test_interface_init_media_center){
	//return MEDIA_NO_ERROR
	EXPECT_EQ(MEDIA_NO_ERROR, media_center_init(path, NET_WIFI_REACHABLE));
	//return MEDIA_INVALID_PARAM
	char* path = NULL;
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_init(path, NET_WWAN_REACHABLE));
}

TEST_F(media_center_test, test_interface_set_net_state){
	EXPECT_EQ(MEDIA_NO_ERROR, media_center_set_net_state(NET_NOT_REACHABLE));
}

TEST_F(media_center_test, test_create_media_handle){
	//return handle
	EXPECT_PRED_FORMAT2(assert_handle, url, token);
	//return MEDIA_INVALID_PARAM
	char* url = NULL;
	EXPECT_EQ(INVALID_MEDIA_HANDLE, media_center_create_media_handle(url, token, media_handle_callback));
}

TEST_F(media_center_test, test_interface_get_media_info){

	//return MEDIA_INVALID_PARAM
	media_info_t media;
	media_handle_t handle = 0;
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_get_media_info(handle, &media));
	//init_media_center(path, NET_WIFI_REACHABLE);
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_get_media_info(handle, NULL));

	//return invalid movie info
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	EXPECT_EQ(MOVIE_INFO_INVALID, media_center_get_media_info(handle, &media));

	handle = media_center_create_media_handle(url, token, media_handle_callback);
	//return 0
	if(gtest_utility::is_media_info(handle, &media))
	{
		ASSERT_EQ(0, media_center_get_media_info(handle, &media));
	}
	else
	{
		GTEST_LOG_(ERROR)<<"TestFixture: " << test_info_->test_case_name() << "TestName: "<< test_info_->name() << "---> get media info error";
	}
	media_center_destroy_media_handle(handle);
}

TEST_F(media_center_test, test_interface_get_stream_info){

	media_handle_t media_handle = 0;
	stream_info_t* stream = new stream_info_t[STREAM_INFO_COUNT];
	//return MEDIA_INVALID_PARAM ---> media_handle 0
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_get_stream_info(media_handle, stream, STREAM_INFO_COUNT));

	//return MEDIA_INVALID_PARAM ---> stream为空
	stream = NULL;
	media_handle = media_center_create_media_handle(url, token, media_handle_callback);
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_get_stream_info(media_handle, stream, STREAM_INFO_COUNT));

	//return MEDIA_INVALID_PARAM ---> stream_info_count 0
	uint32_t stream_info_count = 0;
	stream = new stream_info_t[STREAM_INFO_COUNT];
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_get_stream_info(media_handle, stream, stream_info_count));

	//return MEDIA_NO_ERROR
	EXPECT_EQ(MEDIA_NO_ERROR, media_center_get_stream_info(media_handle, stream, STREAM_INFO_COUNT));

	//verify stream_info_t
	/*typedef struct stream_info
	{
	int32_t  stream_id;							///< 媒体流id
	char	 stream_name[STREAM_NAME_SIZE];		///< 媒体流名称
	bool	 default_stream;					///< 默认媒体流

	uint64_t file_size;							///< 文件长度
	uint64_t duration;							///< 播放时长
	}stream_info_t; */
	//bitrate id: 0 ===> filesize":224593577,"duration":6128160
	//bitrate id: 1 ===> filesize":420672080,"duration":6128160

	//verify bitrate_id 0
	int32_t expect_stream_id0 = 0;
	uint64_t expect_duration0 = 6128160;
	uint64_t expect_file_size0 = 224593577;
	wchar_t* expect_stream_name0 = L"标清";
	EXPECT_EQ(expect_stream_id0, stream[0].stream_id);
	EXPECT_EQ(expect_duration0, stream[0].duration);
	EXPECT_EQ(expect_file_size0, stream[0].file_size);
	EXPECT_STREQ(gtest_utility::wc2utf8(expect_stream_name0).c_str(), stream[0].stream_name);
	//verify default_stream : 0 
	EXPECT_FALSE(stream[0].default_stream);
	int32_t expect_stream_id1 = 1;
	uint64_t expect_duration1 = 6128160;
	uint64_t expect_file_size1 = 420672080;
	wchar_t* expect_stream_name1 = L"高清";
	//verify bitrate_id 1
	EXPECT_EQ(expect_stream_id1, stream[1].stream_id);
	EXPECT_EQ(expect_duration1, stream[1].duration);
	EXPECT_EQ(expect_file_size1, stream[1].file_size);
	EXPECT_STREQ(gtest_utility::wc2utf8(expect_stream_name1).c_str(), stream[1].stream_name);
	//verify default_stream : 0 
	EXPECT_TRUE(stream[1].default_stream);
	media_center_destroy_media_handle(media_handle);
}

TEST_F(media_center_test, test_interface_start_stream_service){
	//return MEDIA_INVALID_PARAM handle 0
	media_handle_t handle = 0;
	media_info_t media_info;
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_start_stream_service(handle, 0, STREAM_HLS_MODE, STREAM_SERVICE_PORT));

	//return MEDIA_NO_ERROR
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	if (gtest_utility::is_media_info(handle, &media_info))
	{
		EXPECT_EQ(MEDIA_NO_ERROR, media_center_start_stream_service(handle, 0, STREAM_HLS_MODE, STREAM_SERVICE_PORT));
	}
	media_center_stop_stream_service(handle);
	media_center_destroy_media_handle(handle);
}

TEST_F(media_center_test, test_interface_stop_stream_service){
	//return MEDIA_INVALID_PARAM handle 0
	media_handle_t handle = 0;
	EXPECT_EQ(MEDIA_INVALID_PARAM, media_center_stop_stream_service(handle));

	//return MEDIA_NO_ERROR
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	EXPECT_EQ(MEDIA_NO_ERROR, media_center_stop_stream_service(handle));
	media_center_destroy_media_handle(handle);
}

TEST_F(media_center_test, test_interface_get_handle_state){
	media_info_t media;

	//return MEDIA_HANDLE_ERROR handle 0
	media_handle_t handle = 0;
	EXPECT_EQ(MEDIA_HANDLE_ERROR, media_center_get_handle_state(handle));

	//return MEDIA_HANDLE_RUNNABLE
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	EXPECT_EQ(MEDIA_HANDLE_RUNNABLE, media_center_get_handle_state(handle));

	//return MEDIA_HANDLE_ERROR
	char* url = "servicetype=1&fid=A70A09721538A3C9273E2AE8C2461141";
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	if(gtest_utility::is_media_info(handle, &media))
	{
		EXPECT_EQ(MEDIA_HANDLE_ERROR, media_center_get_handle_state(handle));
	}
	media_center_destroy_media_handle(handle);
}

TEST_F(media_center_test, test_get_download_speed){
	media_info_t media;
	media_handle_t handle = 0;
	int count = 0;
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	if(gtest_utility::is_media_info(handle, &media))
	{
		EXPECT_EQ(MEDIA_HANDLE_RUNNABLE, media_center_get_handle_state(handle));
	}
	EXPECT_EQ(MEDIA_NO_ERROR, media_center_start_stream_service(handle, 0, STREAM_HLS_MODE, STREAM_SERVICE_PORT));
	while(true)
	{
		if(gtest_utility::add_timer(3*1000))
		{
			uint32_t speed = media_center_get_download_speed(handle);
			EXPECT_TRUE(speed > 0 && speed < 5*1024*1024);
			count++;
			GTEST_LOG_(INFO)<<"TestFixture: " << test_info_->test_case_name() << "TestName: "<< test_info_->name() << "---> task download speed:"<<speed;
			if(count > 3)
				break;
		}
	}
	media_center_stop_stream_service(handle);
	media_center_destroy_media_handle(handle);
}

TEST_F(media_center_test, test_get_download_percent){
	media_info_t media;
	media_handle_t handle = 0;
	int count = 0;
	handle = media_center_create_media_handle(url, token, media_handle_callback);
	if(gtest_utility::is_media_info(handle, &media))
	{
		EXPECT_EQ(MEDIA_HANDLE_RUNNABLE, media_center_get_handle_state(handle));
	}
	EXPECT_EQ(MEDIA_NO_ERROR, media_center_start_stream_service(handle, 0, STREAM_HLS_MODE, STREAM_SERVICE_PORT));
	while(true)
	{
		if(gtest_utility::add_timer(3*1000))
		{
			uint32_t percent = media_center_get_download_percent(handle);
			EXPECT_TRUE(percent >= 0 && percent < 10);
			count++;
			GTEST_LOG_(INFO)<<"TestFixture: " << test_info_->test_case_name() << "TestName: "<< test_info_->name() << "---> task download percent:"<<percent;
			if(count > 3)
				break;
		}
	}
	media_center_stop_stream_service(handle);
	media_center_destroy_media_handle(handle);
}

TEST_F(media_center_test, test_interface_media_center_cleanup){
	media_info_t media;
	//init_media_center(path, NET_WIFI_REACHABLE);
	media_handle_t handle = media_center_create_media_handle(url, token, media_handle_callback);
	if(gtest_utility::is_media_info(handle, &media))
	{
		EXPECT_EQ(MEDIA_NO_ERROR, media_center_destroy_media_handle(handle));
		//test media_center_cleanup
		EXPECT_EQ(0, media_center_cleanup());
	}
	else
	{
		GTEST_LOG_(ERROR)<<"TestFixture: " << test_info_->test_case_name() << "TestName: "<< test_info_->name() << "---> get media info error";
	}
}

