#include "stdafx.h"
#include "gtest/gtest.h"
#include "libp2p.h"
#include "gtest_utilities.h"

class libp2p_test : public testing::Test
{
protected:
	static void SetUpTestCase()
	{
		path = "c:\\test";
		app_name = "tv";
		app_version = "1.1.1";
		qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";

		libp2p_set_app_name(app_name);
		libp2p_set_app_version(app_version);
	}

	static void TearDownTestCase()
	{
		path = NULL;
		app_name = NULL;
		app_version = NULL;
		qstp = NULL;
	}

	virtual void SetUp()
	{

	}

	virtual void TearDown()
	{

	}

	static char* path;
	static char* app_name;
	static char* app_version;
	static char* qstp;
};

char* libp2p_test::path = NULL;
char* libp2p_test::app_name = NULL;
char* libp2p_test::app_version = NULL;
char* libp2p_test::qstp = NULL;

void log_fuction(libp2p_log_level level, const char* msg)
{

}

void libp2p_test_task_state_cb(libp2p_task_t t, libp2p_task_state old_status, libp2p_task_state new_status, int error)
{

}

TEST_F(libp2p_test, test_libp2p_get_version)
{
	uint32_t act_libp2p_version = 0;
	uint32_t exp_libp2p_version = 65792;

	act_libp2p_version = libp2p_get_version();
	EXPECT_EQ(exp_libp2p_version, act_libp2p_version);
}

TEST_F(libp2p_test, test_libp2p_get_version_string)
{
	const char *exp_libp2p_version = "1.1.0";
	const char *act_libp2p_version = NULL;

	act_libp2p_version = libp2p_get_version_string();
	EXPECT_STREQ(exp_libp2p_version, act_libp2p_version);
}

TEST_F(libp2p_test, test_libp2p_enable_log)
{
	libp2p_enable_log(LIBP2P_LOG_TRACE);
	EXPECT_TRUE(true);
}

TEST_F(libp2p_test, test_libp2p_set_log_function)
{
	libp2p_set_log_function(log_fuction);
	EXPECT_TRUE(true);
}

TEST_F(libp2p_test, test_libp2p_startup)
{
	const char* m_path = NULL;
	EXPECT_EQ(-1, libp2p_startup(m_path, libp2p_net_wifi_reachable));
	
	m_path = "c:\\test";
	if (gtest_utils::check_folder_exist(m_path))
	{
		int32_t m_result = libp2p_startup(m_path, libp2p_net_wwan_reachable);
		EXPECT_EQ(0, m_result);
		libp2p_shutdown();
	}
	else
	{
		EXPECT_TRUE(false);
	}	
}

TEST_F(libp2p_test, test_libp2p_set_app_name)
{
	std::string m_app_name = "wl";
	int32_t m_result = libp2p_set_app_name(m_app_name.c_str());
	EXPECT_EQ(0, m_result);	
}

TEST_F(libp2p_test, test_libp2p_set_app_version)
{
	const char* m_app_ver = "3.6.7";
	int32_t m_result = libp2p_set_app_version(m_app_ver);;
	EXPECT_EQ(0, m_result);
}

TEST_F(libp2p_test, test_libp2p_get_url_gcid)
{
	const char* m_qstp = NULL;
	char buf[41] = {0}; 
	int32_t m_result = libp2p_get_url_gcid(m_qstp, buf, sizeof(buf));
	EXPECT_EQ(-1, m_result);

	m_result = 0;
	m_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	char* buf_null = NULL;
	uint32_t buf_size = 41;
	m_result = libp2p_get_url_gcid(m_qstp, buf_null, buf_size);
	EXPECT_EQ(-1, m_result);

	m_result = 0;
	buf_size = 40;
	m_result = libp2p_get_url_gcid(qstp, buf, buf_size);
	EXPECT_EQ(-1, m_result);

	m_result = 0;
	buf_size = 39;
	m_result = libp2p_get_url_gcid(qstp, buf, buf_size);
	EXPECT_EQ(-1, m_result);

	m_result = 0;
	const char* wrong_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	m_result = libp2p_get_url_gcid(wrong_qstp, buf, sizeof(buf));
	EXPECT_EQ(-1, m_result);

	const char* m_expect_gcid = "DA0FA7A2910BF1E146E60E5CBBB864433D141E45";
	m_result = libp2p_get_url_gcid(qstp, buf, sizeof(buf));
	EXPECT_EQ(0, m_result);
	EXPECT_STREQ(m_expect_gcid, buf);
}

TEST_F(libp2p_test, test_libp2p_get_url_file_size)
{
	const char* wrong_qstp = NULL;
	int32_t m_result = libp2p_get_url_file_size(wrong_qstp);
	EXPECT_EQ(0, m_result);

	wrong_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	m_result = libp2p_get_url_file_size(wrong_qstp);
	EXPECT_EQ(0, m_result);

	const char* m_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	uint64_t m_expect_file_size = 318502928;
	uint64_t m_actual_file_size = libp2p_get_url_file_size(m_qstp);
	EXPECT_EQ(m_expect_file_size, m_actual_file_size);
}

TEST_F(libp2p_test, test_libp2p_set_net_state)
{
	int32_t m_result = INT32_MAX;
	if (!libp2p_startup(path, libp2p_net_wwan_reachable))
	{
		m_result = libp2p_set_net_state(libp2p_net_wifi_reachable);
		EXPECT_EQ(0, m_result);
		libp2p_shutdown();
	}
}

TEST_F(libp2p_test, test_libp2p_get_free_disk_space)
{
	uint64_t m_result = ULONG_MAX;
	m_result = libp2p_get_free_disk_space();
	EXPECT_LT(0, m_result);
}

TEST_F(libp2p_test, test_libp2p_remove_cache_data)
{
	int32_t m_result = 0;
	const char* wrong_gcid = "DA0FA7A2910BF1E146E60E5CBBB864433D141E4";
	m_result = libp2p_remove_cache_data(wrong_gcid);
	EXPECT_EQ(-1, m_result);

	wrong_gcid = "";
	m_result = libp2p_remove_cache_data(wrong_gcid);
	EXPECT_EQ(-1, m_result);

	if (!libp2p_startup(path, libp2p_net_wifi_reachable))
	{
		libp2p_task_t task = 0;
		task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, 20*1024*1024, libp2p_play_hls, 1, libp2p_test_task_state_cb);
		if (0 < task)
		{
			const char* gcid = "DA0FA7A2910BF1E146E60E5CBBB864433D141E45";
			m_result = libp2p_remove_cache_data(gcid);
			EXPECT_EQ(-1, m_result);
		}
		libp2p_task_destroy(task);
		libp2p_shutdown();
	}
	
	const char* m_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	char buf[41] = {0};
	if (!libp2p_startup(path, libp2p_net_wwan_reachable))
	{
		if (!libp2p_get_url_gcid(m_qstp, buf, sizeof(buf)))
		{
			m_result = libp2p_remove_cache_data(buf);
			EXPECT_EQ(0, m_result);
		}
		libp2p_shutdown();
	}	
}

TEST_F(libp2p_test, test_libp2p_get_downloaded_size)
{
	char* gcid = "DA0FA7A2910BF1E146E60E5CBBB864433D141E45";
	uint64_t m_result = ULONG_MAX;
	const char* m_wrong_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	m_result = libp2p_get_downloaded_size(m_wrong_qstp);
	//cast -1 to ULONG_MAX
	EXPECT_EQ(-1, m_result);

	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		m_result = libp2p_get_downloaded_size(qstp);
		EXPECT_EQ(0, m_result);
		libp2p_shutdown();
	}
	
	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		libp2p_task_t task = 0;
		task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, 1, libp2p_test_task_state_cb);
		if (0 < task)
		{
			if(0 == libp2p_task_start(task))
			{
				gtest_utils::sleep(30*1000);
				libp2p_task_stop(task);
			}
			libp2p_task_destroy(task);
		}
		libp2p_shutdown();
	}

	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		m_result = libp2p_get_downloaded_size(qstp);
		EXPECT_LT(0, m_result);
		EXPECT_GT(libp2p_get_url_file_size(qstp), m_result);
		libp2p_shutdown();
	}
	
	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		libp2p_remove_cache_data(gcid);
		libp2p_task_t task = 0;
		task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_segment, 0, libp2p_play_hls, 1, libp2p_test_task_state_cb);
		if (0 < task)
		{
			if(0 == libp2p_task_start(task))
			{
				gtest_utils::sleep(30*1000);
				libp2p_task_stop(task);
			}
			libp2p_task_destroy(task);
		}
		libp2p_shutdown();
	}

	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		m_result = libp2p_get_downloaded_size(qstp);
		EXPECT_LT(0, m_result);
		EXPECT_GT(libp2p_get_url_file_size(qstp), m_result);
		libp2p_shutdown();
	}
}

TEST_F(libp2p_test, test_libp2p_set_download_speed_limit)
{
	uint32_t m_max_speed = 30*1024;
	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		libp2p_set_download_speed_limit(m_max_speed);
		libp2p_shutdown();
	}
}

TEST_F(libp2p_test, test_libp2p_set_upload_speed_limit)
{
	uint32_t m_max_speed = 30*1024;
	if (!libp2p_startup(path, libp2p_net_ethernet_reachable))
	{
		libp2p_set_upload_speed_limit(m_max_speed);
		libp2p_shutdown();
	}
}

