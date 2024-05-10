#include "Dio.h"
#include "unity.h"
#include "unity_fixture.h"
#include "mock_Det.h"

TEST_GROUP(dio_swc);

TEST_SETUP(dio_swc)
{
}

TEST_TEAR_DOWN(dio_swc)
{
}

TEST(dio_swc, test_Dio_ReadChannel_OutOfRange)
{
    Dio_LevelType ret  ; 
    Dio_ChannelType ChannelId = DIO_CONFIGURED_CHANNLES+1; 
    Det_ReportError_ExpectAndReturn(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_CHANNEL_SID,
                    DIO_E_PARAM_INVALID_CHANNEL_ID,E_OK);   
    ret = Dio_ReadChannel(ChannelId); 
    TEST_ASSERT_EQUAL(STD_OFF,ret);
}
