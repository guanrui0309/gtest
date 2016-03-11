#include "stdafx.h"
#include "gtest/gtest.h"
#include "libp2p.h"
#include "gtest_utilities.h"

class libp2p_vod_task_test : public testing::Test
{
protected:
	static void SetUpTestCase()
	{
		app_name = "mj";
		app_version = "3.3.3";
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

char* libp2p_vod_task_test::qstp = NULL;
char* libp2p_vod_task_test::app_name= NULL;
char* libp2p_vod_task_test::app_version = NULL;

const uint32_t MEMORY_CACHE_SIZE = 20*1024*1024;
const uint32_t STREAM_PORT = 18080;

void libp2p_vod_task_state_cb(libp2p_task_t t, libp2p_task_state old_status, libp2p_task_state new_status, int error)
{

}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_task_create)
{
	libp2p_task_t m_task = UINT_MAX;
	const char* m_qstp = NULL;
	const char* m_wrong_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";
	
	EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_vod_task_create(m_qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb));
	EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_vod_task_create(m_wrong_qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb));
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);
	EXPECT_EQ(2, m_task);
	libp2p_task_destroy(m_task);
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_start)
{
	libp2p_task_t m_task = UINT_MAX;
	uint32_t m_port = 8080;
	
	EXPECT_EQ(-1, libp2p_vod_stream_start(m_task, m_port));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(-1, libp2p_vod_stream_start(m_task, m_port));
		m_port = 18080;
		EXPECT_EQ(0, libp2p_vod_stream_start(m_task, m_port));
		EXPECT_EQ(0, libp2p_vod_stream_stop(m_task));
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_stop)
{
	libp2p_task_t m_task = UINT_MAX;

	EXPECT_EQ(-1, libp2p_vod_stream_stop(m_task));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(0, libp2p_vod_stream_stop(m_task));
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_set_play_time)
{
	libp2p_task_t m_task = UINT_MAX;
	uint32_t m_pos_ms = 50*1000;

	EXPECT_EQ(-1, libp2p_vod_stream_set_play_time(m_task, m_pos_ms));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(0, libp2p_vod_stream_set_play_time(m_task, m_pos_ms));
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_can_play_time_by_time)
{
	libp2p_task_t m_task = UINT_MAX;
	uint32_t m_pos_ms = 10*1000;
	uint32_t m_play_time = UINT_MAX;

	EXPECT_EQ(0, libp2p_vod_stream_can_play_time_by_time(m_task, m_pos_ms));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(0, libp2p_vod_stream_can_play_time_by_time(m_task, m_pos_ms));
		if (!libp2p_task_start(m_task))
		{
			if (!libp2p_vod_stream_start(m_task, STREAM_PORT))
			{
				gtest_utils::sleep(30*1000);
				m_play_time = libp2p_vod_stream_can_play_time_by_time(m_task, m_pos_ms);
				EXPECT_LT(0, m_play_time);
				EXPECT_GT(100000, m_play_time);
				libp2p_vod_stream_stop(m_task);
			}
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_can_read_size_by_time)
{
	libp2p_task_t m_task = UINT_MAX;
	uint32_t m_pos_ms = 10*1000;
	uint64_t m_can_read_size = ULONG_MAX;

	EXPECT_EQ(0, libp2p_vod_stream_can_read_size_by_time(m_task, m_pos_ms));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (1 == m_task)
	{
		EXPECT_EQ(0, libp2p_vod_stream_can_read_size_by_time(m_task, m_pos_ms));
		if (!libp2p_task_start(m_task))
		{
			if (!libp2p_vod_stream_start(m_task, STREAM_PORT))
			{
				gtest_utils::sleep(30*1000);
				m_can_read_size = libp2p_vod_stream_can_read_size_by_time(m_task, m_pos_ms);
				EXPECT_LT(0, m_can_read_size);
				EXPECT_GT(10*1024*1024, m_can_read_size);
				libp2p_vod_stream_stop(m_task);
			}
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_can_read_size_by_pos)
{
	libp2p_task_t m_task = UINT_MAX;
	uint64_t m_file_pos = ULONG_MAX;
	uint64_t m_can_read_size = ULONG_MAX;

	EXPECT_EQ(0, libp2p_vod_stream_can_read_size_by_pos(m_task, m_file_pos));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (1 == m_task)
	{
		m_file_pos = 2995842; //header range pos
		EXPECT_EQ(0, libp2p_vod_stream_can_read_size_by_pos(m_task, m_file_pos));
		if (!libp2p_task_start(m_task))
		{
			if (!libp2p_vod_stream_start(m_task, STREAM_PORT))
			{
				gtest_utils::sleep(30*1000);
				//
				m_can_read_size = libp2p_vod_stream_can_read_size_by_pos(m_task, m_file_pos);
				EXPECT_LT(0, m_can_read_size);
				EXPECT_GT(10*1024*1024, m_can_read_size);
				libp2p_vod_stream_stop(m_task);
			}
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_calc_play_time_by_pos)
{
	libp2p_task_t m_task = UINT_MAX;
	uint64_t m_file_pos = ULONG_MAX;
	uint32_t m_play_time = 15800;

	EXPECT_EQ(0, libp2p_vod_stream_calc_play_time_by_pos(m_task, m_file_pos));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (1 == m_task)
	{
		m_file_pos = 4000000; 
		EXPECT_EQ(UINT_MAX, libp2p_vod_stream_calc_play_time_by_pos(m_task, m_file_pos));
		if (!libp2p_task_start(m_task))
		{
			if (!libp2p_vod_stream_start(m_task, STREAM_PORT))
			{
				gtest_utils::sleep(5*1000);
				EXPECT_EQ(m_play_time, libp2p_vod_stream_calc_play_time_by_pos(m_task, m_file_pos));
				libp2p_vod_stream_stop(m_task);
			}
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_calc_file_pos_by_time)
{
	libp2p_task_t m_task = UINT_MAX;
	uint32_t m_pos_ms = UINT_MAX;
	uint64_t m_file_pos = 3354969;

	EXPECT_EQ(0, libp2p_vod_stream_calc_file_pos_by_time(m_task, m_pos_ms));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (1 == m_task)
	{
		m_pos_ms = 10*1000;
		EXPECT_EQ(UINT_MAX, libp2p_vod_stream_calc_file_pos_by_time(m_task, m_pos_ms));
		if (!libp2p_task_start(m_task))
		{
			if (!libp2p_vod_stream_start(m_task, STREAM_PORT))
			{
				gtest_utils::sleep(30*1000);
				EXPECT_EQ(m_file_pos, libp2p_vod_stream_calc_file_pos_by_time(m_task, m_pos_ms));
				libp2p_vod_stream_stop(m_task);
			}
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_read_data)
{
	libp2p_task_t m_task = UINT_MAX;
	uint64_t m_position = ULONG_MAX;
	char buf[8192] = {0};
	char* buf_null = NULL;

	EXPECT_EQ(0, libp2p_vod_stream_read_data(m_task, m_position, buf, sizeof(buf)));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_single, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (1 == m_task)
	{
		EXPECT_EQ(0, libp2p_vod_stream_read_data(m_task, m_position, buf_null, sizeof(buf)));
		EXPECT_EQ(0, libp2p_vod_stream_read_data(m_task, m_position, buf, 0));
		EXPECT_EQ(0, libp2p_vod_stream_read_data(m_task, m_position, buf, sizeof(buf)));

		if (!libp2p_task_start(m_task))
		{
			m_position = 2995842;
			gtest_utils::sleep(30*1000);
			EXPECT_EQ(sizeof(buf), libp2p_vod_stream_read_data(m_task, m_position, buf, sizeof(buf)));
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_file_segment, 0, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (2 == m_task)
	{
		if (!libp2p_task_start(m_task))
		{
			m_position = 2995842;
			gtest_utils::sleep(30*1000);
			EXPECT_EQ(sizeof(buf), libp2p_vod_stream_read_data(m_task, m_position, buf, sizeof(buf)));
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (3 == m_task)
	{
		if (!libp2p_task_start(m_task))
		{
			m_position = 2995842;
			gtest_utils::sleep(30*1000);
			EXPECT_EQ(sizeof(buf), libp2p_vod_stream_read_data(m_task, m_position, buf, sizeof(buf)));
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}

TEST_F(libp2p_vod_task_test, test_libp2p_vod_stream_seek_to_position)
{
	libp2p_task_t m_task = UINT_MAX;
	uint64_t m_seek_position = ULONG_MAX;

	EXPECT_EQ(0, libp2p_vod_stream_seek_to_position(m_task, m_seek_position));

	m_task = libp2p_vod_task_create(qstp, libp2p_task_cache_memory, MEMORY_CACHE_SIZE, libp2p_play_hls, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_vod_task_state_cb);

	if (1 == m_task)
	{
		srand((int)time(0));
		m_seek_position = rand()%libp2p_get_url_file_size(qstp);
		
		if (!libp2p_task_start(m_task))
		{
			EXPECT_EQ(0, libp2p_vod_stream_seek_to_position(m_task, m_seek_position));
			libp2p_task_stop(m_task);
		}
		libp2p_task_destroy(m_task);
	}
}