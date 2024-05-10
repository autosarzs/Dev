#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(port_swc)
{
  RUN_TEST_CASE(port_swc, test_PORT_GetVersionInfo_Function);
  RUN_TEST_CASE(port_swc, test_PORT_GetVersionInfo_WithNull);
}