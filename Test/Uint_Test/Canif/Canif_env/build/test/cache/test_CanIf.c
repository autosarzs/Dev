#include "build/temp/_test_CanIf.c"
#include "src/CanIf.h"
#include "build/test/mocks/mock_Det.h"
#include "build/test/mocks/mock_Can.h"
#include "C:/Ruby23-x64/lib/ruby/gems/2.3.0/gems/ceedling-0.29.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_CanIf_NeedToImplement(void)

{

    CanIf_ModuleState = ((CanIf_ModuleStateType)0x01);

}



void test_CanIf_NeedToImplement1(void)

{

    if ((CanIf_ModuleState==((CanIf_ModuleStateType)0x01))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(21)));};

}
