#include "Dio.h"
#include "unity.h"
#include "unity_fixture.h"
#include "mock_Det.h"
#include "stub_structure.h"
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

TEST(dio_swc, test_Dio_GetVersionInfo_ValidVersionInfo)
{
    // Define a Std_VersionInfoType structure to hold version information
    Std_VersionInfoType versionInfo;

    // Call the function with a valid pointer to versionInfo
    Dio_GetVersionInfo(&versionInfo);

    // Check if the versionInfo structure is correctly filled
    TEST_ASSERT_EQUAL(0, versionInfo.vendorID);
    TEST_ASSERT_EQUAL(DIO_MODULE_ID, versionInfo.moduleID);
    TEST_ASSERT_EQUAL(DIO_INSTANCE_ID, versionInfo.instanceID);
    TEST_ASSERT_EQUAL(DIO_CFG_SW_MAJOR_VERSION, versionInfo.sw_major_version);
    TEST_ASSERT_EQUAL(DIO_CFG_SW_MINOR_VERSION, versionInfo.sw_minor_version);
    TEST_ASSERT_EQUAL(DIO_CFG_SW_PATCH_VERSION, versionInfo.sw_patch_version);
    TEST_ASSERT_EQUAL(DIO_CFG_AR_RELEASE_MAJOR_VERSION, versionInfo.ar_major_version);
    TEST_ASSERT_EQUAL(DIO_CFG_AR_RELEASE_MINOR_VERSION, versionInfo.ar_minor_version);
    TEST_ASSERT_EQUAL(DIO_CFG_AR_RELEASE_PATCH_VERSION, versionInfo.ar_patch_version);

}
TEST(dio_swc, test_Dio_GetVersionInfo_VersionInfo_Null)
{
    // Expect a call to Det_ReportError with specific parameters and return E_OK
    Det_ReportError_ExpectAndReturn(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER,E_OK);

    // Call the function with a null pointer
    Dio_GetVersionInfo(NULL);

}
