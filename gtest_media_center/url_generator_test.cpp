///=============================================================================
/// @file :		url_generater_test.cpp
///	@brief :	����qstp��������
/// @version :	1.0
/// @author :	guanrui
/// @date :		2015-04-10
///=============================================================================
#include "StdAfx.h"
#include "gtest/gtest.h"
#include <string>
#include "media_center.h"
#include "media_handle.h"
#include "media_info_manager.h"
#include "url_generater.h"

using namespace std;
using namespace baofengcloud;

class url_generator_test :  public testing::Test{

protected:
	static void SetUpTestCase(){
		generater = new url_generater();
	}

	static void TearDownTestCase(){
		delete generater;
		generater = NULL;
	}

	static url_generater* generater;
};

///// ӰƬ��Ϣ
//typedef struct movie_info
//{
//	uint64_t user_id;					///< �û�ID
//	char     file_id[FILE_ID_SIZE];		///< �ļ�ID
//	uint32_t servicet_type;				///< �������ͣ�0��ƽ̨���㲥��1��������㲥��2��ֱ����3������ʱֱ����
//	char     file_name[FILE_NAME_SIZE];	///< �ļ�����ԭʼ�ļ�����
//	char	 file_key[FILE_KEY_SIZE];	///< �ļ�key���ļ���ȥ�أ�
//	uint64_t file_size;					///< ԭʼ�ļ�����
//	uint32_t duration;					///< ����ʱ��
//	uint32_t ifpublic;					///< �Ƿ�Ϊ������Ƶ��1�����У�0��˽�У�
//	char     movie_name[FILE_NAME_SIZE];///< ӰƬ����
//
//	std::vector<bitrate_info_t> streams;///< ����Ϣ
//
//public:
//	movie_info(void);
//
//}movie_info_t;
//================================================
//typedef struct bitrate_info
//{
//	uint32_t bitrate_id;				///< ����ID  ��0,1��2��
//	char     bitrate_name[BITRATE_SIZE];///< �������ƣ����壬����,���壩
//	char	 gcid[GCID_SIZE];			///< Ψһ��ʶ
//	char	 file_type[FILE_TYPE_SIZE];	///< �ļ�����
//	uint64_t file_size;					///< �ļ�����
//	uint32_t duration;					///< ����ʱ��
//	uint32_t bfhd_offset;				///< ����˽��ͷƫ��
//	uint32_t moov_offset;				///< mp4��׼ͷƫ��
//}bitrate_info_t;

url_generater* url_generator_test::generater = NULL;

TEST_F(url_generator_test, test_generate_url){
	movie_info_t movie_info;
	bitrate_info_t bitrate_info;

	//����һ��bitrate_info��������
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

	//����һ��movie_info��������
	memset(&movie_info, 0, sizeof(movie_info));
	movie_info.user_id = 1;
	strncpy(movie_info.file_id, "A70A09721538A3C9273E2AE8C2461141", FILE_ID_SIZE);
	movie_info.file_id[FILE_ID_SIZE-1]='\0';
	movie_info.servicet_type = 4; 
	strncpy(movie_info.file_name, "test.mp4", FILE_NAME_SIZE);
	movie_info.file_name[FILE_NAME_SIZE-1]='\0';
	strncpy(movie_info.file_key, "", FILE_KEY_SIZE);
	movie_info.file_key[FILE_KEY_SIZE-1]='\0';
	movie_info.file_size = 420672080;
	movie_info.duration = 6128160;
	movie_info.ifpublic = 1; ///< �Ƿ�Ϊ������Ƶ��1�����У�0��˽�У�
	strncpy(movie_info.movie_name, "test.mp4", FILE_NAME_SIZE);
	movie_info.movie_name[FILE_NAME_SIZE-1]='\0';
	movie_info.streams.push_back(bitrate_info);

	//bool url_generater::generate_url(const movie_info_t& info, uint32_t index, const char* token, std::string& qstp)
	int index = 1;
	string qstp;
	string token;

	url_ext_info m_url_ext_info;
	//service_type 4, return false
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	movie_info.servicet_type = 1;
	//index > info.streams.size() return false
	index = 3;
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//index = info.streams.size() return false
	index = movie_info.streams.size();
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//strlen(bitrate.gcid) != GCID_SIZE-1 retun false
	index = 0;
	strncpy(bitrate_info.gcid, "32F65FA55E9F481EAAFED1A79CE7D6CE574", GCID_SIZE);
	bitrate_info.gcid[GCID_SIZE-1]='\0';
	movie_info.streams.pop_back();
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//0 == bitrate.duration return false
	movie_info.streams.pop_back();
	strncpy(bitrate_info.gcid, "32F65FA55E9F481EAAFED1A79CE7D6CE574A9112", GCID_SIZE);
	bitrate_info.gcid[GCID_SIZE-1]='\0';
	bitrate_info.duration = 0;
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//0 == bitrate.bfhd_offset return false;
	movie_info.streams.pop_back();
	bitrate_info.duration = 6128160;
	bitrate_info.bfhd_offset = 0;
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//0 == bitrate.moov_offset return false
	movie_info.streams.pop_back();
	bitrate_info.bfhd_offset = 40224;
	bitrate_info.moov_offset = 0;
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//0 == bitrate.file_size return false
	movie_info.streams.pop_back();
	bitrate_info.moov_offset = 3358026;
	bitrate_info.file_size = 0;
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//bitrate.bfhd_offset > bitrate.file_size return false
	movie_info.streams.pop_back();
	bitrate_info.file_size = 420672080;
	bitrate_info.bfhd_offset = bitrate_info.file_size + 1;
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//bitrate.moov_offset > bitrate.file_size return false
	movie_info.streams.pop_back();
	bitrate_info.bfhd_offset = 40224;
	bitrate_info.moov_offset = bitrate_info.file_size + 1;
	movie_info.streams.push_back(bitrate_info);
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//!info.ifpublic
	movie_info.streams.pop_back();
	bitrate_info.moov_offset = 3358026; 
	movie_info.streams.push_back(bitrate_info);
	movie_info.ifpublic = 0;
	EXPECT_FALSE(generater->generate_url(movie_info, index, NULL, m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//���ifpublic = 1 & token = NULL -----> ������ȷ����qstp���ޱ���
	movie_info.ifpublic = 1;
	EXPECT_TRUE(generater->generate_url(movie_info, index, NULL, m_url_ext_info, qstp));
	const char* exp_vod_qstp_ntoken = "vod://32F65FA55E9F481EAAFED1A79CE7D6CE574A9112?public=1&bitrate_id=1&file_type=mp4&file_size=420672080&duration=6128160&bfhd_offset=40224&moov_offset=3358026";
	EXPECT_STREQ(exp_vod_qstp_ntoken, qstp.c_str());
	//info.servicet_type = 0 return false
	movie_info.servicet_type = 0;
	qstp.clear();
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//info.servicet_type = 1 & ifpublic = 1  ----> return true
	string vod_token = "";
	movie_info.servicet_type = 1;
	EXPECT_TRUE(generater->generate_url(movie_info, index, vod_token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ(exp_vod_qstp_ntoken, qstp.c_str());
	//info.servicet_type = 1 & ifpublic = 0  ----> return true
	vod_token = "vod";
	movie_info.ifpublic = 0;
	const char* exp_vod_qstp_token = "vod://32F65FA55E9F481EAAFED1A79CE7D6CE574A9112?public=0&bitrate_id=1&file_type=mp4&file_size=420672080&duration=6128160&bfhd_offset=40224&moov_offset=3358026&token=vod";
	EXPECT_TRUE(generater->generate_url(movie_info, index, vod_token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ(exp_vod_qstp_token, qstp.c_str());
	//info.servicet_type = 2 & ifpublic = 1  ----> return true
	qstp.clear();
	movie_info.servicet_type = 2;
	movie_info.ifpublic = 1;
	string live_token = "";
	const char* exp_live_qstp_ntoken = "live://32F65FA55E9F481EAAFED1A79CE7D6CE574A9112?public=1";
	EXPECT_TRUE(generater->generate_url(movie_info, index, live_token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ(exp_live_qstp_ntoken, qstp.c_str());
	//info.servicet_type = 2 & ifpublic = 0  ----> return true
	live_token = "live";
	movie_info.servicet_type = 2;
	movie_info.ifpublic = 0;
	const char* exp_live_qstp_token = "live://32F65FA55E9F481EAAFED1A79CE7D6CE574A9112?public=0&token=live";
	EXPECT_TRUE(generater->generate_url(movie_info, index, live_token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ(exp_live_qstp_token, qstp.c_str());
	//info.servicet_type = 3 ----> return false
	qstp.clear();
	movie_info.servicet_type = 3;
	movie_info.ifpublic = 1;
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
	//info.servicet_type = 4(�����ڵ�service_type) ----> return false
	movie_info.servicet_type = 4;
	movie_info.ifpublic = 1;
	EXPECT_FALSE(generater->generate_url(movie_info, index, token.c_str(), m_url_ext_info, qstp));
	EXPECT_STREQ("", qstp.c_str());
}