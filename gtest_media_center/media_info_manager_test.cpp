///=============================================================================
/// @file :		media_info_manager_test.cpp
///	@brief :	测试 ---> 媒体信息管理类
/// @version :	1.0
/// @author :	guanrui
/// @date :		2015-04-16
///=============================================================================
#include "StdAfx.h"
#include <string>
#include "media_info_manager.h"
#include "gtest/gtest.h"

using namespace std;
using namespace baofengcloud;

//重载bitrate_info结构体中的==
bool operator==(const bitrate_info_t& lhs_binfo, const bitrate_info_t& rhs_binfo){
	return (lhs_binfo.bitrate_id == rhs_binfo.bitrate_id
		&& (!strcmp(lhs_binfo.bitrate_name, rhs_binfo.bitrate_name)) 
		&& (!strcmp(lhs_binfo.gcid, rhs_binfo.gcid))
		&& (!strcmp(lhs_binfo.file_type, rhs_binfo.file_type))
		&& lhs_binfo.file_size == rhs_binfo.file_size 
		&& lhs_binfo.duration == rhs_binfo.duration
		&& lhs_binfo.bfhd_offset == rhs_binfo.bfhd_offset
		&& lhs_binfo.moov_offset == rhs_binfo.moov_offset);
}

//重载bitrate_info结构体中的!=
bool operator!=(const bitrate_info_t& lhs_binfo, const bitrate_info_t& rhs_binfo){
	return (!(lhs_binfo == rhs_binfo));
}

//重载movie_info结构体中的==
bool operator==(const movie_info_t& lhs_info, const movie_info_t& rhs_info){
	bool res = (lhs_info.user_id == rhs_info.user_id && (!strcmp(lhs_info.file_id, rhs_info.file_id))
		&& lhs_info.servicet_type == rhs_info.servicet_type
		&& (!strcmp(lhs_info.file_name, rhs_info.file_name))
		&& (!strcmp(lhs_info.file_key, rhs_info.file_key))
		&& lhs_info.file_size == rhs_info.file_size 
		&& lhs_info.duration == rhs_info.duration && lhs_info.ifpublic == rhs_info.ifpublic
		&& (!strcmp(lhs_info.movie_name, rhs_info.movie_name)));
	if (!res)
	{
		return res;
	}
	//vector的size不相等，直接返回false
	if (lhs_info.streams.size() != rhs_info.streams.size())
	{
		return false;
	}
	for (std::vector<bitrate_info_t>::size_type i = 0; i != lhs_info.streams.size(); ++i)
	{
		if ((lhs_info.streams[i] != rhs_info.streams[i]))
		{
			return false;
		}
	}
	return res;
}
//=====================================================================================

class media_info_manager_test : public testing::Test{

protected:
	static void SetUpTestCase(){

		url = "servicetype=1&uid=4995606&fid=A70A09721538A3C9273E2AE8C2461141";

		//构造一个movie_info测试数据
		memset(&movie_info, 0 , sizeof(movie_info));
		movie_info.user_id = 1;
		strncpy(movie_info.file_id, "A70A09721538A3C9273E2AE8C2461141", FILE_ID_SIZE);
		movie_info.file_id[FILE_ID_SIZE-1]='\0';
		movie_info.servicet_type = 0; 
		strncpy(movie_info.file_name, "test.mp4", FILE_NAME_SIZE);
		movie_info.file_name[FILE_NAME_SIZE-1]='\0';
		strncpy(movie_info.file_key, "", FILE_KEY_SIZE);
		movie_info.file_key[FILE_KEY_SIZE-1]='\0';
		movie_info.file_size = 420672080;
		movie_info.duration = 6128160;
		movie_info.ifpublic = 1; ///< 是否为公有视频（1：公有，0：私有）
		strncpy(movie_info.movie_name, "test.mp4", FILE_NAME_SIZE);
		movie_info.movie_name[FILE_NAME_SIZE-1]='\0';

		//构造一个bitrate_info测试数据
		memset(&bitrate_info, 0, sizeof(bitrate_info));
		bitrate_info.bitrate_id = 1;
		strncpy(bitrate_info.bitrate_name, "test.mp4", BITRATE_SIZE);
		bitrate_info.bitrate_name[BITRATE_SIZE-1] = '\0';
		strncpy(bitrate_info.gcid, "32F65FA55E9F481EAAFED1A79CE7D6CE574A9112", GCID_SIZE);
		bitrate_info.gcid[GCID_SIZE-1]='\0';
		strncpy(bitrate_info.file_type, "mp4", FILE_TYPE_SIZE);
		bitrate_info.file_type[FILE_TYPE_SIZE-1] = '\0';
		bitrate_info.file_size = 420672080;
		bitrate_info.duration = 6128160;
		bitrate_info.bfhd_offset = 40224;
		bitrate_info.moov_offset = 3358026;

		//构造一个bitrate_info测试数据
		memset(&bitrate_info_2, 0, sizeof(bitrate_info_2));
		bitrate_info_2.bitrate_id = 2;
		strncpy(bitrate_info_2.bitrate_name, "test_2.mp4", BITRATE_SIZE);
		bitrate_info_2.bitrate_name[BITRATE_SIZE-1] = '\0';
		strncpy(bitrate_info_2.gcid, "32F65FA55E9F481EAAFED1A79CE7D6CE574A9112", GCID_SIZE);
		bitrate_info_2.gcid[GCID_SIZE-1]='\0';
		strncpy(bitrate_info_2.file_type, "mp4", FILE_TYPE_SIZE);
		bitrate_info_2.file_type[FILE_TYPE_SIZE-1] = '\0';
		bitrate_info_2.file_size = 222222222;
		bitrate_info_2.duration = 6128160;
		bitrate_info_2.bfhd_offset = 40224;
		bitrate_info_2.moov_offset = 3358026;

		movie_info.streams.push_back(bitrate_info);
		movie_info.streams.push_back(bitrate_info_2);
	};

	static void TearDownTestCase(){

	};

	virtual void SetUp(){
		media_info_manager::create_instance();
	};

	virtual void TearDown(){
		media_info_manager::destroy_instance();
	};

	static movie_info_t movie_info;
	static bitrate_info_t bitrate_info;
	static bitrate_info_t bitrate_info_2;
	static string url;
};

//被测试类的public方法
//public:
//	static media_info_manager* create_instance(void);
//	static media_info_manager* get_instance(void);
//	static void destroy_instance(void);
//public:
//	/// 设置影片信息
//	bool set_movie_info(const std::string& url, const movie_info_t& info);
//	/// 获得影片信息
//	bool get_movie_info(const std::string& url, movie_info_t& info) const;
//	/// 判断是否存在影片信息
//	bool movie_info_exist(const std::string& url);
//	/// 复用影片信息
//	void reuse_movie_info(const std::string& url);
//	/// 删除影片信息
//	void remove_movie_info(const std::string& url);
//
//public:
//	/// 获得媒体信息
//	bool get_media_info(const std::string& url, media_info_t& info) const;
//	/// 获得媒体流信息
//	bool get_stream_info(const std::string& url, 
//		std::vector<stream_info_t>& info) const;
string media_info_manager_test::url;
movie_info_t media_info_manager_test::movie_info;
bitrate_info_t media_info_manager_test::bitrate_info;
bitrate_info_t media_info_manager_test::bitrate_info_2;

TEST_F(media_info_manager_test, test_create_instance){
	media_info_manager::create_instance();
	media_info_manager* man_2 = media_info_manager::get_instance();
	media_info_manager* man_1 = media_info_manager::create_instance();
	EXPECT_TRUE((man_1 == man_2));
	man_1 = media_info_manager::create_instance();
	EXPECT_TRUE(man_1 == man_2);
	media_info_manager::destroy_instance();
	man_1 = media_info_manager::get_instance();
	man_2 = media_info_manager::get_instance();
	EXPECT_TRUE(man_1 == NULL && man_2 ==NULL);
}

TEST_F(media_info_manager_test, test_reuse_movie_info){
	string url_1 = "servicetype=1&uid=4995606&fid=A70A09721538A3C9273E2AE8C2461141";
	string url_2 = "servicetype=1&uid=4995606&fid=A70A09721538A3C9273E2AE8C2461141";
	string url_3 = "servicetype=1&uid=4995607&fid=A70A09721538A3C9273E2AE8C2461141";
	media_info_manager* mana_test = media_info_manager::get_instance();
	mana_test->reuse_movie_info(url_1);
	mana_test->reuse_movie_info(url_2);
	const std::list<std::string>& test_url_list = mana_test->reuse_movie_info(url_3);
	EXPECT_STREQ(test_url_list.back().c_str(), url_3.c_str());
	EXPECT_STREQ(test_url_list.front().c_str(), url_2.c_str());
	int url_list_size = 2;
	EXPECT_EQ(url_list_size, test_url_list.size());
}

TEST_F(media_info_manager_test, test_remove_movie_info){
	string url_no_exist = "test";
	movie_info_t movie_info_actual;
	media_info_manager* mana_test = media_info_manager::get_instance();
	EXPECT_TRUE(mana_test->set_movie_info(url, movie_info));
	mana_test->remove_movie_info(url);
	EXPECT_FALSE(mana_test->get_movie_info(url, movie_info));
	EXPECT_NO_THROW(mana_test->remove_movie_info(url_no_exist));
}

TEST_F(media_info_manager_test, test_movie_info_exist){
	string url_no_exist = "test";
	media_info_manager* mana_test = media_info_manager::get_instance();
	EXPECT_TRUE(mana_test->set_movie_info(url, movie_info));
	EXPECT_TRUE(mana_test->movie_info_exist(url));
	EXPECT_FALSE(mana_test->movie_info_exist(url_no_exist));
}

TEST_F(media_info_manager_test, test_set_movie_info){
	media_info_manager* mana_test = media_info_manager::get_instance();
	for(int i = 1; i <= 16; i++){
		string url_test = "test_" + i;
		mana_test->set_movie_info(url_test, movie_info);
	}
	EXPECT_TRUE(mana_test->set_movie_info(url, movie_info));
	EXPECT_EQ(1, movie_info.streams[0].bitrate_id);
	EXPECT_EQ(2, movie_info.streams[1].bitrate_id);
	EXPECT_FALSE(mana_test->get_movie_info("test_1", movie_info));

}

TEST_F(media_info_manager_test, test_get_movie_info){
	movie_info_t movie_info_actual;
	movie_info_t movie_info_expect;
	media_info_manager* mana_test = media_info_manager::get_instance();
	EXPECT_TRUE(mana_test->set_movie_info(url, movie_info));
	EXPECT_TRUE(mana_test->get_movie_info(url, movie_info_actual));
	EXPECT_TRUE(movie_info_actual == movie_info);
	string url_no_exist = "test";
	memset(&movie_info_actual, 0 , sizeof(movie_info_actual));
	EXPECT_FALSE(mana_test->get_movie_info(url_no_exist, movie_info_actual));
	EXPECT_TRUE(movie_info_actual == movie_info_expect);
}

//typedef struct media_info
//{
//	char     media_name[MEDIA_NAME_SIZE];		///< 媒体名称
//	uint32_t media_stream_count;				///< 该媒体包含的流数量
//}media_info_t;
TEST_F(media_info_manager_test, test_get_media_info){
	media_info_t media_info;
	media_info_manager* mana_test = media_info_manager::get_instance();
	EXPECT_TRUE(mana_test->set_movie_info(url, movie_info));
	EXPECT_TRUE(mana_test->get_media_info(url, media_info));
	EXPECT_EQ(0, strcmp(media_info.media_name, movie_info.file_name));
	int media_stream_count_exp = 2;
	EXPECT_EQ(media_stream_count_exp, media_info.media_stream_count);
	string url_no_exist = "test";
	memset(&media_info, 0, sizeof(media_info));
	EXPECT_FALSE(mana_test->get_media_info(url_no_exist, media_info));
}

///// 媒体流信息定义
//#define STREAM_NAME_SIZE 64
//typedef struct stream_info
//{
//	int32_t  stream_id;							///< 媒体流id
//	char	 stream_name[STREAM_NAME_SIZE];		///< 媒体流名称
//	bool	 default_stream;					///< 默认媒体流
//
//	uint64_t file_size;							///< 文件长度
//	uint64_t duration;							///< 播放时长
//}stream_info_t;
TEST_F(media_info_manager_test, test_get_stream_info){
	media_info_manager* mana_test = media_info_manager::get_instance();
	vector<stream_info_t> streams;
	int stream_info_count_exp = 2;
	int stream_default_stream_exp = 0;
	EXPECT_TRUE(mana_test -> set_movie_info(url, movie_info));
	EXPECT_TRUE(mana_test -> get_stream_info(url, streams));
	EXPECT_TRUE(streams.size() == movie_info.streams.size());
	EXPECT_EQ(stream_info_count_exp, streams.size());
	EXPECT_EQ(stream_info_count_exp, movie_info.streams.size());
	for(vector<bitrate_info_t>::size_type i = 0; i != streams.size(); i++){

		EXPECT_EQ(streams[i].stream_id, movie_info.streams[i].bitrate_id);
		EXPECT_STREQ(streams[i].stream_name, movie_info.streams[i].bitrate_name);
		EXPECT_EQ(stream_default_stream_exp, (int)streams[i].default_stream);
		EXPECT_EQ(streams[i].file_size, movie_info.streams[i].file_size);
		EXPECT_EQ(streams[i].duration, movie_info.streams[i].duration);

	}
	streams.clear();
	string url_no_exist = "test";
	EXPECT_FALSE(mana_test->get_stream_info(url_no_exist, streams));
}