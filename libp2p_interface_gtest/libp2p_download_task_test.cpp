#include "stdafx.h"
#include "gtest/gtest.h"
#include "libp2p.h"
#include "gtest_utilities.h"

class libp2p_download_task_test : public testing::Test
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

char* libp2p_download_task_test::qstp = NULL;
char* libp2p_download_task_test::app_name= NULL;
char* libp2p_download_task_test::app_version = NULL;

void libp2p_download_task_state_cb(libp2p_task_t t, libp2p_task_state old_status, libp2p_task_state new_status, int error)
{

}

TEST_F(libp2p_download_task_test, test_libp2p_download_task_create)
{
	libp2p_task_t m_task = UINT_MAX;
	const char* m_qstp = NULL;
	const char* m_wrong_qstp = "qstp://qkvp/pGp/bmxleqg/qey:XDXZ.s?jp=GGJ&amp;jd=10AF0W0GZDABFDEDMTETAEQCBBBXTMMJJ1DMDEMQ&amp;vd=XW11Z0BZE1XFGGD1QB1JFETZXZ11XTJZ1QQZZZAD&amp;fz=G1BT0C&amp;pi=DT&amp;pr=WMBTA&amp;pps=A&amp;ppk=A&amp;pyp=DGFBFWF0&amp;blzd=TAZF&amp;pah=XJ1A10WZQQXD1XZCWWBBZWJQJATEC0GF&amp;ped=pov";

	EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_download_task_create(m_qstp, libp2p_task_cache_file_single, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_download_task_state_cb));
	EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_download_task_create(qstp, libp2p_task_cache_memory, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_download_task_state_cb));
	EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_download_task_create(m_wrong_qstp, libp2p_task_cache_file_segment, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_download_task_state_cb));

	m_task = libp2p_download_task_create(qstp, libp2p_task_cache_file_single, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_download_task_state_cb);
	if (1 == m_task)
	{
		EXPECT_EQ(INVALID_TASK_HANDLE, libp2p_download_task_create(qstp, libp2p_task_cache_file_single, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_download_task_state_cb));
		libp2p_task_destroy(m_task);
	}

	m_task = libp2p_download_task_create(qstp, libp2p_task_cache_file_single, LIBP2P_VOD_TASK_SKIP_MP4_HEADER, libp2p_download_task_state_cb);
	EXPECT_EQ(2, m_task);
	libp2p_task_destroy(m_task);
}

//Todo: predownload task interface test