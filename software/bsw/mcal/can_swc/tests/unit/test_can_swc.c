#include "Can.h"
#include "unity.h"
#include "unity_fixture.h"
#include "mock_Det.h"
#include "mock_stub.h"
#include "mock_can_lib.h"
#include "mock_test_can_swc_stubs.h"

/**********CALLBACKS *****************/
Std_ReturnType Det_ReportError_CALLBACK(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
  (void)ModuleId;
  (void)InstanceId;
  (void)ApiId;
  (void)ErrorId;
  return E_OK;
}
/***********TESTS*************/
TEST_GROUP(can_swc);

TEST_SETUP(can_swc)
{
  mock_Det_Init();
  mock_stub_Init();
  mock_stub_Init();
  mock_can_lib_Init();
  mock_test_can_swc_stubs_Init();
}

TEST_TEAR_DOWN(can_swc)
{
  mock_Det_Verify();
  mock_Det_Destroy();
  mock_stub_Verify();
  mock_stub_Destroy();
  mock_can_lib_Verify();
  mock_can_lib_Destroy();
  mock_test_can_swc_stubs_Verify();
  mock_test_can_swc_stubs_Destroy();
}

TEST(can_swc, CAN_TEST_PASS)
{
  TEST_MESSAGE("\n ------- FORCE PASS SCENARIO ----------\n");
  TEST_ASSERT_EQUAL(1,1);
}
TEST(can_swc, CAN_TEST_FAIL)
{
  TEST_MESSAGE("\n ------- FORCE FAIL SCENARIO ----------\n");
  TEST_ASSERT_EQUAL(1,-1);
}