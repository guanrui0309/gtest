///=============================================================================
/// @file :		media_handle_manager_test.cpp
///	@brief :	测试 ---> 媒体流句柄管理类
/// @author :	guanrui
/// @date :		2015-04-20
///=============================================================================

#include "StdAfx.h"
#include <string>
#include "gtest/gtest.h"
#include "media_handle.h"
#include "media_info_manager.h"
#include "media_handle_manager.h"

using namespace std;
using namespace baofengcloud;

class media_handle_manager_test : public testing::Test{

protected:
	static void SetUpTestCase(){
		url = "servicetype=1&uid=4995606&fid=A70A09721538A3C9273E2AE8C2461141";
		token = "";
		path = "c:\\wahaha";
	};

	static void TearDownTestCase(){
		url = NULL;
		token = NULL;
	};

	virtual void SetUp(){
		media_handle_manager::create_instance();
	}

	virtual void TearDown(){
		media_handle_manager::destroy_instance();
	}

	static char* url;
	static char* token;
	static char* path;
};

//public:
//	static media_handle_manager* create_instance(void);
//	static media_handle_manager* get_instance(void);
//	static void destroy_instance(void);
//
//public:
//	/// 创建媒体句柄
//	media_handle_t create_media_handle(const char* url, const char* token, 
//		media_handle_state_cb state_cb);
//	/// 销毁媒体句柄
//	void destroy_media_handle(media_handle_t handle);
//
//	/// 获得媒体句柄
//	media_handle* get_media_handle(media_handle_t handle);
//	/// 释放媒体句柄
//	void release_media_handle(media_handle* handle);
char* media_handle_manager_test::url = NULL;
char* media_handle_manager_test::token = NULL;
char* media_handle_manager_test::path = NULL;

void MEDIA_API media_handle_state_callback(media_handle_t handle, 
	media_handle_state_t state, int32_t error){

}
TEST_F(media_handle_manager_test, test_instance){
	media_handle_manager::create_instance();
	media_handle_manager* mhm_2 = media_handle_manager::get_instance();
	media_handle_manager* mhm_1 = media_handle_manager::create_instance();
	EXPECT_TRUE((mhm_1 == mhm_2));
	mhm_1 = media_handle_manager::create_instance();
	EXPECT_TRUE(mhm_1 == mhm_2);
	media_handle_manager::destroy_instance();
	mhm_1 = media_handle_manager::get_instance();
	mhm_2 = media_handle_manager::get_instance();
	EXPECT_TRUE(mhm_1 == NULL && mhm_2 ==NULL);
}

TEST_F(media_handle_manager_test, test_create_media_handle){
	media_handle_manager* mhm_test = media_handle_manager::get_instance();
	EXPECT_EQ(0, media_center_init(path, NET_WIFI_REACHABLE));
	media_handle_t m_handle_id = mhm_test->create_media_handle(service_type(1), url, token, media_handle_state_callback);
	media_handle * m_media_handle = mhm_test->get_media_handle(m_handle_id);
	mhm_test->release_media_handle(m_media_handle);
	EXPECT_EQ(m_media_handle->get_handle_id(), m_handle_id);
	EXPECT_EQ(m_handle_id, mhm_test->create_media_handle(service_type(1), url, token, media_handle_state_callback));
	mhm_test->release_media_handle(m_media_handle);
	mhm_test->destroy_media_handle(m_handle_id);
}

TEST_F(media_handle_manager_test, test_destroy_media_handle){
	media_handle_manager* mhm_test = media_handle_manager::get_instance();
	media_handle_t m_handle_id = 1;
	mhm_test->destroy_media_handle(m_handle_id);
	EXPECT_TRUE(mhm_test->get_media_handle(m_handle_id) == NULL);
	m_handle_id = mhm_test->create_media_handle(service_type(1), url, token, media_handle_state_callback);
	mhm_test->destroy_media_handle(m_handle_id);
	EXPECT_TRUE(mhm_test->get_media_handle(m_handle_id) == NULL);
}

TEST_F(media_handle_manager_test, test_get_media_handle){

}

TEST_F(media_handle_manager_test, test_release_media_handle){

}