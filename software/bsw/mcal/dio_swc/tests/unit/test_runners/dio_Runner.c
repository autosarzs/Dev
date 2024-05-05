#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(dio_swc)
{
  RUN_TEST_CASE(dio_swc, test_Dio_ReadChannel_OutOfRange);
}