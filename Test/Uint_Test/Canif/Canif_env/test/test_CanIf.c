#include "unity.h"
#include "mock_Can.h"
#include "mock_Det.h"
#include "CanIf.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_CanIf_NeedToImplement(void)
{
    CanIf_ModuleState = CANIF_READY;
}

void test_CanIf_NeedToImplement1(void)
{
    TEST_ASSERT_TRUE(CanIf_ModuleState==CANIF_READY);
}