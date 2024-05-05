#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(can_swc)
{
  RUN_TEST_CASE(can_swc, CAN_TEST_PASS);
  RUN_TEST_CASE(can_swc, CAN_TEST_FAIL);
}