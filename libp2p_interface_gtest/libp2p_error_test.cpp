#include "stdafx.h"
#include "gtest/gtest.h"
#include "libp2p.h"
#include "gtest_utilities.h"

class libp2p_error_test : public testing::Test
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

char* libp2p_error_test::qstp = NULL;
char* libp2p_error_test::app_name= NULL;
char* libp2p_error_test::app_version = NULL;

TEST_F(libp2p_error_test, test_libp2p_error_interfaces)
{
	int32_t m_error = 1002;
	int32_t m_act_error = INT32_MAX;
	const char* m_error_string = "file io error";

	libp2p_set_last_error(m_error);
	m_act_error = libp2p_get_last_error();
	EXPECT_EQ(m_error, m_act_error);
	EXPECT_STRCASEEQ(m_error_string, libp2p_get_error_info(m_act_error));

	m_error = 10005;
	m_error_string = "Unknown error";
	libp2p_set_last_error(m_error);
	m_act_error = libp2p_get_last_error();
	EXPECT_EQ(m_error, m_act_error);
	EXPECT_STRCASEEQ(m_error_string, libp2p_get_error_info(m_act_error));
}
