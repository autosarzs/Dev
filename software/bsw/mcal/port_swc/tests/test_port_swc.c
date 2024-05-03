#include "unity.h"
#include "unity_fixture.h"

#include "Port.h"
#include "mock_Det.h"

TEST_GROUP(port_swc);

TEST_SETUP(port_swc)
{
}

TEST_TEAR_DOWN(port_swc)
{
}

TEST(port_swc, test_PORT_GetVersionInfo_Function)
{
  Std_VersionInfoType VersionInfo = {0} ; 
  PORT_GetVersionInfo(&VersionInfo);
  TEST_ASSERT_EQUAL(0,VersionInfo.vendorID);
  TEST_ASSERT_EQUAL(PORT_MODULE_ID,VersionInfo.moduleID);
  TEST_ASSERT_EQUAL(PORT_INSTANCE_ID,VersionInfo.instanceID);
}

TEST(port_swc, test_PORT_GetVersionInfo_WithNull)
{
  Std_VersionInfoType VersionInfo = {0} ; 
  Det_ReportError_ExpectAnyArgsAndReturn(E_NOT_OK);
  PORT_GetVersionInfo(NULL);
}
