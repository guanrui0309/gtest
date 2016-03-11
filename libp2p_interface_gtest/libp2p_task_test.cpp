#include "stdafx.h"
#include "gtest/gtest.h"
#include "libp2p_task.h"
#include "libp2p.h"
#include "gtest_utilities.h"

class libp2p_task_test : public testing::Test
{
protected:
	static void SetUpTestCase()
	{
		app_name = "wl";
		app_version = "2.2.2";
		qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;lh=DGFBFXDA&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
		
		libp2p_set_app_name(app_name);
		libp2p_set_app_version(app_version);
	}

	static void TearDownTestCase()
	{
		app_name = NULL;
		app_version = NULL;
		qstp = NULL;
	}

	virtual void SetUp()
	{
		libp2p_startup("c:\\test", libp2p_net_wifi_reachable);
	}

	virtual void TearDown()
	{
		libp2p_shutdown();
	}

	static char* qstp;
	static char* app_name;
	static char* app_version;
};

char* libp2p_task_test::qstp = NULL;
char* libp2p_task_test::app_name= NULL;
char* libp2p_task_test::app_version = NULL;

const uint32_t MEMORY_CACHE_SIZE = 20 * 1024 * 1024;            ///< memory cache size 20M

void libp2p_task_test_task_state_cb(libp2p_task_t t, libp2p_task_state old_status, libp2p_task_state new_status, int error)
{

}

TEST_F(libp2p_task_test, test_libp2p_task_start)
{
	libp2p_task_t m_task = UINT_MAX;
	int32_t m_result = UINT_MAX;

	m_result = libp2p_task_start(m_task);
	EXPECT_EQ(-1, m_result);

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, 20*1024*1024, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		m_result = libp2p_task_start(m_task);
		EXPECT_EQ(0, m_result);
		libp2p_task_stop(m_task);
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_stop)
{
	libp2p_task_t m_task = UINT_MAX;
	int32_t m_result = UINT_MAX;

	m_result = libp2p_task_stop(m_task);
	EXPECT_EQ(-1, m_result);

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, 20*1024*1024, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		m_result = libp2p_task_stop(m_task);
		EXPECT_EQ(0, m_result);
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_destroy)
{
	libp2p_task_t m_task = UINT_MAX;

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, 20*1024*1024, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_get_type)
{
	libp2p_task_t m_task = UINT_MAX;

	EXPECT_EQ(libp2p_task_type_vod, libp2p_task_get_type(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, 20*1024*1024, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(libp2p_task_type_vod, libp2p_task_get_type(m_task));
		libp2p_task_destroy(m_task);
	}
	
	m_task = libp2p_download_task_create(qstp, libp2p_task_cache_file_single, 1, libp2p_task_test_task_state_cb);
	if (2 == m_task)
	{
		EXPECT_EQ(libp2p_task_type_download, libp2p_task_get_type(m_task));
		libp2p_task_destroy(m_task);
	}

	//todo:live_task, predownload_task
}

TEST_F(libp2p_task_test, test_libp2p_task_get_state)
{
	libp2p_task_t m_task = UINT_MAX;

	EXPECT_EQ(libp2p_task_idle, libp2p_task_get_state(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(libp2p_task_idle, libp2p_task_get_state(m_task));
		libp2p_task_start(m_task);
		EXPECT_EQ(libp2p_task_downloading, libp2p_task_get_state(m_task));
		libp2p_task_stop(m_task);
		libp2p_task_destroy(m_task);
	}

	//todo: libp2p_task_download_completed, libp2p_task_failed
}

TEST_F(libp2p_task_test, test_libp2p_task_get_gcid)
{
	libp2p_task_t m_task = UINT_MAX;
	char gcid_buf[41] = {0};

	EXPECT_FALSE(libp2p_task_get_gcid(m_task));

	if (!libp2p_get_url_gcid(qstp, gcid_buf, sizeof(gcid_buf)))
	{
		m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);

		if (1 == m_task)
		{
			EXPECT_STREQ(gcid_buf, libp2p_task_get_gcid(m_task));
			libp2p_task_destroy(m_task);
		}
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_get_cache_type)
{
	libp2p_task_t m_task = UINT_MAX;
	EXPECT_EQ(libp2p_task_cache_file_segment, libp2p_task_get_cache_type(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);

	if (1 == m_task)
	{
		EXPECT_EQ(libp2p_task_cache_memory, libp2p_task_get_cache_type(m_task));
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);

	if (2 == m_task)
	{
		EXPECT_EQ(libp2p_task_cache_file_single, libp2p_task_get_cache_type(m_task));
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_segment, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);

	if (3 == m_task)
	{
		EXPECT_EQ(libp2p_task_cache_file_segment, libp2p_task_get_cache_type(m_task));
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_get_cache_size)
{
	libp2p_task_t m_task = UINT_MAX;

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(libp2p_get_url_file_size(qstp), libp2p_task_get_cache_size(m_task));
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_segment, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (2 == m_task)
	{
		EXPECT_EQ(libp2p_get_url_file_size(qstp), libp2p_task_get_cache_size(m_task));
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (3 == m_task)
	{
		EXPECT_EQ(libp2p_get_url_file_size(qstp), libp2p_task_get_cache_size(m_task));
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_get_head_size)
{
	libp2p_task_t m_task = UINT_MAX;
	uint64_t m_head_size = 24735;

	EXPECT_EQ(0, libp2p_task_get_head_size(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(m_head_size, libp2p_task_get_head_size(m_task));
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_get_download_speed)
{
	libp2p_task_t m_task = UINT_MAX;

	EXPECT_EQ(0, libp2p_task_get_download_speed(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		if (!libp2p_task_start(m_task))
		{
			gtest_utils::sleep(20*1000);
			EXPECT_LT(0, libp2p_task_get_download_speed(m_task));
			EXPECT_GT(4194304, libp2p_task_get_download_speed(m_task));
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_get_downloaded_size)
{
	libp2p_task_t m_task = UINT_MAX;
	
	EXPECT_EQ(0, libp2p_task_get_downloaded_size(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		if (!libp2p_task_start(m_task))
		{
			gtest_utils::sleep(20*1000);
			EXPECT_LT(0, libp2p_task_get_downloaded_size(m_task));
			EXPECT_GT(libp2p_get_url_file_size(qstp), libp2p_task_get_downloaded_size(m_task));
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_task_test, test_libp2p_task_set_download_speed_limit)
{
	libp2p_task_t m_task = UINT_MAX;
	uint32_t m_max_speed = 50*1024*1024;

	//no task, return directly
	libp2p_task_set_download_speed_limit(m_task, m_max_speed);

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_task_test_task_state_cb);
	if (1 == m_task)
	{
		libp2p_task_set_download_speed_limit(m_task, m_max_speed);
		libp2p_task_destroy(m_task);
	}
}