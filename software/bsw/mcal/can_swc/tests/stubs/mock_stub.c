/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_stub.h"

static const char* CMockString_CanIf_ControllerBusOff = "CanIf_ControllerBusOff";
static const char* CMockString_CanIf_ControllerModeIndication = "CanIf_ControllerModeIndication";
static const char* CMockString_CanIf_RxIndication = "CanIf_RxIndication";
static const char* CMockString_CanIf_TxConfirmation = "CanIf_TxConfirmation";
static const char* CMockString_CanTxPduId = "CanTxPduId";
static const char* CMockString_ControllerId = "ControllerId";
static const char* CMockString_ControllerMode = "ControllerMode";
static const char* CMockString_Mailbox = "Mailbox";
static const char* CMockString_PduInfoPtr = "PduInfoPtr";

typedef struct _CMOCK_CanIf_TxConfirmation_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  char ExpectAnyArgsBool;
  PduIdType Expected_CanTxPduId;
  char IgnoreArg_CanTxPduId;

} CMOCK_CanIf_TxConfirmation_CALL_INSTANCE;

typedef struct _CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  char ExpectAnyArgsBool;
  uint8 Expected_ControllerId;
  Can_ControllerStateType Expected_ControllerMode;
  char IgnoreArg_ControllerId;
  char IgnoreArg_ControllerMode;

} CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE;

typedef struct _CMOCK_CanIf_RxIndication_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  char ExpectAnyArgsBool;
  const Can_HwType* Expected_Mailbox;
  const PduInfoType* Expected_PduInfoPtr;
  int Expected_Mailbox_Depth;
  int Expected_PduInfoPtr_Depth;
  char IgnoreArg_Mailbox;
  char IgnoreArg_PduInfoPtr;

} CMOCK_CanIf_RxIndication_CALL_INSTANCE;

typedef struct _CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  char ExpectAnyArgsBool;
  uint8 Expected_ControllerId;
  char IgnoreArg_ControllerId;

} CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE;

static struct mock_stubInstance
{
  char CanIf_TxConfirmation_IgnoreBool;
  char CanIf_TxConfirmation_CallbackBool;
  CMOCK_CanIf_TxConfirmation_CALLBACK CanIf_TxConfirmation_CallbackFunctionPointer;
  int CanIf_TxConfirmation_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE CanIf_TxConfirmation_CallInstance;
  char CanIf_ControllerModeIndication_IgnoreBool;
  char CanIf_ControllerModeIndication_CallbackBool;
  CMOCK_CanIf_ControllerModeIndication_CALLBACK CanIf_ControllerModeIndication_CallbackFunctionPointer;
  int CanIf_ControllerModeIndication_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE CanIf_ControllerModeIndication_CallInstance;
  char CanIf_RxIndication_IgnoreBool;
  char CanIf_RxIndication_CallbackBool;
  CMOCK_CanIf_RxIndication_CALLBACK CanIf_RxIndication_CallbackFunctionPointer;
  int CanIf_RxIndication_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE CanIf_RxIndication_CallInstance;
  char CanIf_ControllerBusOff_IgnoreBool;
  char CanIf_ControllerBusOff_CallbackBool;
  CMOCK_CanIf_ControllerBusOff_CALLBACK CanIf_ControllerBusOff_CallbackFunctionPointer;
  int CanIf_ControllerBusOff_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE CanIf_ControllerBusOff_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void mock_stub_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.CanIf_TxConfirmation_CallInstance;
  if (Mock.CanIf_TxConfirmation_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_CanIf_TxConfirmation);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.CanIf_TxConfirmation_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.CanIf_ControllerModeIndication_CallInstance;
  if (Mock.CanIf_ControllerModeIndication_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_CanIf_ControllerModeIndication);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.CanIf_RxIndication_CallInstance;
  if (Mock.CanIf_RxIndication_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_CanIf_RxIndication);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.CanIf_RxIndication_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.CanIf_ControllerBusOff_CallInstance;
  if (Mock.CanIf_ControllerBusOff_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_CanIf_ControllerBusOff);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.CanIf_ControllerBusOff_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
}

void mock_stub_Init(void)
{
  mock_stub_Destroy();
}

void mock_stub_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_CanIf_TxConfirmation_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_CanIf_TxConfirmation);
  cmock_call_instance = (CMOCK_CanIf_TxConfirmation_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.CanIf_TxConfirmation_CallInstance);
  Mock.CanIf_TxConfirmation_CallInstance = CMock_Guts_MemNext(Mock.CanIf_TxConfirmation_CallInstance);
  if (Mock.CanIf_TxConfirmation_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.CanIf_TxConfirmation_CallbackBool &&
      Mock.CanIf_TxConfirmation_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_TxConfirmation_CallbackFunctionPointer(CanTxPduId, Mock.CanIf_TxConfirmation_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->ExpectAnyArgsBool)
  {
  if (!cmock_call_instance->IgnoreArg_CanTxPduId)
  {
    UNITY_SET_DETAILS(CMockString_CanIf_TxConfirmation,CMockString_CanTxPduId);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_CanTxPduId), (void*)(&CanTxPduId), sizeof(PduIdType), cmock_line, CMockStringMismatch);
  }
  }
  if (Mock.CanIf_TxConfirmation_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_TxConfirmation_CallbackFunctionPointer(CanTxPduId, Mock.CanIf_TxConfirmation_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_CanIf_TxConfirmation(CMOCK_CanIf_TxConfirmation_CALL_INSTANCE* cmock_call_instance, PduIdType CanTxPduId);
void CMockExpectParameters_CanIf_TxConfirmation(CMOCK_CanIf_TxConfirmation_CALL_INSTANCE* cmock_call_instance, PduIdType CanTxPduId)
{
  memcpy((void*)(&cmock_call_instance->Expected_CanTxPduId), (void*)(&CanTxPduId),
         sizeof(PduIdType[sizeof(CanTxPduId) == sizeof(PduIdType) ? 1 : -1])); /* add PduIdType to :treat_as_array if this causes an error */
  cmock_call_instance->IgnoreArg_CanTxPduId = 0;
}

void CanIf_TxConfirmation_CMockIgnore(void)
{
  Mock.CanIf_TxConfirmation_IgnoreBool = (char)1;
}

void CanIf_TxConfirmation_CMockStopIgnore(void)
{
  Mock.CanIf_TxConfirmation_IgnoreBool = (char)0;
}

void CanIf_TxConfirmation_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_TxConfirmation_CALL_INSTANCE));
  CMOCK_CanIf_TxConfirmation_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_TxConfirmation_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_TxConfirmation_CallInstance = CMock_Guts_MemChain(Mock.CanIf_TxConfirmation_CallInstance, cmock_guts_index);
  Mock.CanIf_TxConfirmation_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  cmock_call_instance->ExpectAnyArgsBool = (char)1;
}

void CanIf_TxConfirmation_CMockExpect(UNITY_LINE_TYPE cmock_line, PduIdType CanTxPduId)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_TxConfirmation_CALL_INSTANCE));
  CMOCK_CanIf_TxConfirmation_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_TxConfirmation_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_TxConfirmation_CallInstance = CMock_Guts_MemChain(Mock.CanIf_TxConfirmation_CallInstance, cmock_guts_index);
  Mock.CanIf_TxConfirmation_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  CMockExpectParameters_CanIf_TxConfirmation(cmock_call_instance, CanTxPduId);
}

void CanIf_TxConfirmation_AddCallback(CMOCK_CanIf_TxConfirmation_CALLBACK Callback)
{
  Mock.CanIf_TxConfirmation_IgnoreBool = (char)0;
  Mock.CanIf_TxConfirmation_CallbackBool = (char)1;
  Mock.CanIf_TxConfirmation_CallbackFunctionPointer = Callback;
}

void CanIf_TxConfirmation_Stub(CMOCK_CanIf_TxConfirmation_CALLBACK Callback)
{
  Mock.CanIf_TxConfirmation_IgnoreBool = (char)0;
  Mock.CanIf_TxConfirmation_CallbackBool = (char)0;
  Mock.CanIf_TxConfirmation_CallbackFunctionPointer = Callback;
}

void CanIf_TxConfirmation_CMockIgnoreArg_CanTxPduId(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_CanIf_TxConfirmation_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_TxConfirmation_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.CanIf_TxConfirmation_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_CanTxPduId = 1;
}

void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_CanIf_ControllerModeIndication);
  cmock_call_instance = (CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.CanIf_ControllerModeIndication_CallInstance);
  Mock.CanIf_ControllerModeIndication_CallInstance = CMock_Guts_MemNext(Mock.CanIf_ControllerModeIndication_CallInstance);
  if (Mock.CanIf_ControllerModeIndication_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.CanIf_ControllerModeIndication_CallbackBool &&
      Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer(ControllerId, ControllerMode, Mock.CanIf_ControllerModeIndication_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->ExpectAnyArgsBool)
  {
  if (!cmock_call_instance->IgnoreArg_ControllerId)
  {
    UNITY_SET_DETAILS(CMockString_CanIf_ControllerModeIndication,CMockString_ControllerId);
    UNITY_TEST_ASSERT_EQUAL_HEX8(cmock_call_instance->Expected_ControllerId, ControllerId, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_ControllerMode)
  {
    UNITY_SET_DETAILS(CMockString_CanIf_ControllerModeIndication,CMockString_ControllerMode);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_ControllerMode), (void*)(&ControllerMode), sizeof(Can_ControllerStateType), cmock_line, CMockStringMismatch);
  }
  }
  if (Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer(ControllerId, ControllerMode, Mock.CanIf_ControllerModeIndication_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_CanIf_ControllerModeIndication(CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance, uint8 ControllerId, Can_ControllerStateType ControllerMode);
void CMockExpectParameters_CanIf_ControllerModeIndication(CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance, uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
  cmock_call_instance->Expected_ControllerId = ControllerId;
  cmock_call_instance->IgnoreArg_ControllerId = 0;
  memcpy((void*)(&cmock_call_instance->Expected_ControllerMode), (void*)(&ControllerMode),
         sizeof(Can_ControllerStateType[sizeof(ControllerMode) == sizeof(Can_ControllerStateType) ? 1 : -1])); /* add Can_ControllerStateType to :treat_as_array if this causes an error */
  cmock_call_instance->IgnoreArg_ControllerMode = 0;
}

void CanIf_ControllerModeIndication_CMockIgnore(void)
{
  Mock.CanIf_ControllerModeIndication_IgnoreBool = (char)1;
}

void CanIf_ControllerModeIndication_CMockStopIgnore(void)
{
  Mock.CanIf_ControllerModeIndication_IgnoreBool = (char)0;
}

void CanIf_ControllerModeIndication_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE));
  CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_ControllerModeIndication_CallInstance = CMock_Guts_MemChain(Mock.CanIf_ControllerModeIndication_CallInstance, cmock_guts_index);
  Mock.CanIf_ControllerModeIndication_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  cmock_call_instance->ExpectAnyArgsBool = (char)1;
}

void CanIf_ControllerModeIndication_CMockExpect(UNITY_LINE_TYPE cmock_line, uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE));
  CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_ControllerModeIndication_CallInstance = CMock_Guts_MemChain(Mock.CanIf_ControllerModeIndication_CallInstance, cmock_guts_index);
  Mock.CanIf_ControllerModeIndication_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  CMockExpectParameters_CanIf_ControllerModeIndication(cmock_call_instance, ControllerId, ControllerMode);
}

void CanIf_ControllerModeIndication_AddCallback(CMOCK_CanIf_ControllerModeIndication_CALLBACK Callback)
{
  Mock.CanIf_ControllerModeIndication_IgnoreBool = (char)0;
  Mock.CanIf_ControllerModeIndication_CallbackBool = (char)1;
  Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer = Callback;
}

void CanIf_ControllerModeIndication_Stub(CMOCK_CanIf_ControllerModeIndication_CALLBACK Callback)
{
  Mock.CanIf_ControllerModeIndication_IgnoreBool = (char)0;
  Mock.CanIf_ControllerModeIndication_CallbackBool = (char)0;
  Mock.CanIf_ControllerModeIndication_CallbackFunctionPointer = Callback;
}

void CanIf_ControllerModeIndication_CMockIgnoreArg_ControllerId(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.CanIf_ControllerModeIndication_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_ControllerId = 1;
}

void CanIf_ControllerModeIndication_CMockIgnoreArg_ControllerMode(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerModeIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.CanIf_ControllerModeIndication_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_ControllerMode = 1;
}

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_CanIf_RxIndication);
  cmock_call_instance = (CMOCK_CanIf_RxIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.CanIf_RxIndication_CallInstance);
  Mock.CanIf_RxIndication_CallInstance = CMock_Guts_MemNext(Mock.CanIf_RxIndication_CallInstance);
  if (Mock.CanIf_RxIndication_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.CanIf_RxIndication_CallbackBool &&
      Mock.CanIf_RxIndication_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_RxIndication_CallbackFunctionPointer(Mailbox, PduInfoPtr, Mock.CanIf_RxIndication_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->ExpectAnyArgsBool)
  {
  if (!cmock_call_instance->IgnoreArg_Mailbox)
  {
    UNITY_SET_DETAILS(CMockString_CanIf_RxIndication,CMockString_Mailbox);
    if (cmock_call_instance->Expected_Mailbox == NULL)
      { UNITY_TEST_ASSERT_NULL(Mailbox, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY((void*)(cmock_call_instance->Expected_Mailbox), (void*)(Mailbox), sizeof(const Can_HwType), cmock_call_instance->Expected_Mailbox_Depth, cmock_line, CMockStringMismatch); }
  }
  if (!cmock_call_instance->IgnoreArg_PduInfoPtr)
  {
    UNITY_SET_DETAILS(CMockString_CanIf_RxIndication,CMockString_PduInfoPtr);
    if (cmock_call_instance->Expected_PduInfoPtr == NULL)
      { UNITY_TEST_ASSERT_NULL(PduInfoPtr, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY((void*)(cmock_call_instance->Expected_PduInfoPtr), (void*)(PduInfoPtr), sizeof(const PduInfoType), cmock_call_instance->Expected_PduInfoPtr_Depth, cmock_line, CMockStringMismatch); }
  }
  }
  if (Mock.CanIf_RxIndication_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_RxIndication_CallbackFunctionPointer(Mailbox, PduInfoPtr, Mock.CanIf_RxIndication_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_CanIf_RxIndication(CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance, const Can_HwType* Mailbox, int Mailbox_Depth, const PduInfoType* PduInfoPtr, int PduInfoPtr_Depth);
void CMockExpectParameters_CanIf_RxIndication(CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance, const Can_HwType* Mailbox, int Mailbox_Depth, const PduInfoType* PduInfoPtr, int PduInfoPtr_Depth)
{
  cmock_call_instance->Expected_Mailbox = Mailbox;
  cmock_call_instance->Expected_Mailbox_Depth = Mailbox_Depth;
  cmock_call_instance->IgnoreArg_Mailbox = 0;
  cmock_call_instance->Expected_PduInfoPtr = PduInfoPtr;
  cmock_call_instance->Expected_PduInfoPtr_Depth = PduInfoPtr_Depth;
  cmock_call_instance->IgnoreArg_PduInfoPtr = 0;
}

void CanIf_RxIndication_CMockIgnore(void)
{
  Mock.CanIf_RxIndication_IgnoreBool = (char)1;
}

void CanIf_RxIndication_CMockStopIgnore(void)
{
  Mock.CanIf_RxIndication_IgnoreBool = (char)0;
}

void CanIf_RxIndication_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_RxIndication_CALL_INSTANCE));
  CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_RxIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_RxIndication_CallInstance = CMock_Guts_MemChain(Mock.CanIf_RxIndication_CallInstance, cmock_guts_index);
  Mock.CanIf_RxIndication_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  cmock_call_instance->ExpectAnyArgsBool = (char)1;
}

void CanIf_RxIndication_CMockExpect(UNITY_LINE_TYPE cmock_line, const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_RxIndication_CALL_INSTANCE));
  CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_RxIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_RxIndication_CallInstance = CMock_Guts_MemChain(Mock.CanIf_RxIndication_CallInstance, cmock_guts_index);
  Mock.CanIf_RxIndication_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  CMockExpectParameters_CanIf_RxIndication(cmock_call_instance, Mailbox, 1, PduInfoPtr, 1);
}

void CanIf_RxIndication_AddCallback(CMOCK_CanIf_RxIndication_CALLBACK Callback)
{
  Mock.CanIf_RxIndication_IgnoreBool = (char)0;
  Mock.CanIf_RxIndication_CallbackBool = (char)1;
  Mock.CanIf_RxIndication_CallbackFunctionPointer = Callback;
}

void CanIf_RxIndication_Stub(CMOCK_CanIf_RxIndication_CALLBACK Callback)
{
  Mock.CanIf_RxIndication_IgnoreBool = (char)0;
  Mock.CanIf_RxIndication_CallbackBool = (char)0;
  Mock.CanIf_RxIndication_CallbackFunctionPointer = Callback;
}

void CanIf_RxIndication_CMockExpectWithArray(UNITY_LINE_TYPE cmock_line, const Can_HwType* Mailbox, int Mailbox_Depth, const PduInfoType* PduInfoPtr, int PduInfoPtr_Depth)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_RxIndication_CALL_INSTANCE));
  CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_RxIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_RxIndication_CallInstance = CMock_Guts_MemChain(Mock.CanIf_RxIndication_CallInstance, cmock_guts_index);
  Mock.CanIf_RxIndication_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  CMockExpectParameters_CanIf_RxIndication(cmock_call_instance, Mailbox, Mailbox_Depth, PduInfoPtr, PduInfoPtr_Depth);
}

void CanIf_RxIndication_CMockIgnoreArg_Mailbox(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_RxIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.CanIf_RxIndication_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_Mailbox = 1;
}

void CanIf_RxIndication_CMockIgnoreArg_PduInfoPtr(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_CanIf_RxIndication_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_RxIndication_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.CanIf_RxIndication_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_PduInfoPtr = 1;
}

void CanIf_ControllerBusOff(uint8 ControllerId)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_CanIf_ControllerBusOff);
  cmock_call_instance = (CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.CanIf_ControllerBusOff_CallInstance);
  Mock.CanIf_ControllerBusOff_CallInstance = CMock_Guts_MemNext(Mock.CanIf_ControllerBusOff_CallInstance);
  if (Mock.CanIf_ControllerBusOff_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.CanIf_ControllerBusOff_CallbackBool &&
      Mock.CanIf_ControllerBusOff_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_ControllerBusOff_CallbackFunctionPointer(ControllerId, Mock.CanIf_ControllerBusOff_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->ExpectAnyArgsBool)
  {
  if (!cmock_call_instance->IgnoreArg_ControllerId)
  {
    UNITY_SET_DETAILS(CMockString_CanIf_ControllerBusOff,CMockString_ControllerId);
    UNITY_TEST_ASSERT_EQUAL_HEX8(cmock_call_instance->Expected_ControllerId, ControllerId, cmock_line, CMockStringMismatch);
  }
  }
  if (Mock.CanIf_ControllerBusOff_CallbackFunctionPointer != NULL)
  {
    Mock.CanIf_ControllerBusOff_CallbackFunctionPointer(ControllerId, Mock.CanIf_ControllerBusOff_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_CanIf_ControllerBusOff(CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE* cmock_call_instance, uint8 ControllerId);
void CMockExpectParameters_CanIf_ControllerBusOff(CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE* cmock_call_instance, uint8 ControllerId)
{
  cmock_call_instance->Expected_ControllerId = ControllerId;
  cmock_call_instance->IgnoreArg_ControllerId = 0;
}

void CanIf_ControllerBusOff_CMockIgnore(void)
{
  Mock.CanIf_ControllerBusOff_IgnoreBool = (char)1;
}

void CanIf_ControllerBusOff_CMockStopIgnore(void)
{
  Mock.CanIf_ControllerBusOff_IgnoreBool = (char)0;
}

void CanIf_ControllerBusOff_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE));
  CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_ControllerBusOff_CallInstance = CMock_Guts_MemChain(Mock.CanIf_ControllerBusOff_CallInstance, cmock_guts_index);
  Mock.CanIf_ControllerBusOff_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  cmock_call_instance->ExpectAnyArgsBool = (char)1;
}

void CanIf_ControllerBusOff_CMockExpect(UNITY_LINE_TYPE cmock_line, uint8 ControllerId)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE));
  CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.CanIf_ControllerBusOff_CallInstance = CMock_Guts_MemChain(Mock.CanIf_ControllerBusOff_CallInstance, cmock_guts_index);
  Mock.CanIf_ControllerBusOff_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ExpectAnyArgsBool = (char)0;
  CMockExpectParameters_CanIf_ControllerBusOff(cmock_call_instance, ControllerId);
}

void CanIf_ControllerBusOff_AddCallback(CMOCK_CanIf_ControllerBusOff_CALLBACK Callback)
{
  Mock.CanIf_ControllerBusOff_IgnoreBool = (char)0;
  Mock.CanIf_ControllerBusOff_CallbackBool = (char)1;
  Mock.CanIf_ControllerBusOff_CallbackFunctionPointer = Callback;
}

void CanIf_ControllerBusOff_Stub(CMOCK_CanIf_ControllerBusOff_CALLBACK Callback)
{
  Mock.CanIf_ControllerBusOff_IgnoreBool = (char)0;
  Mock.CanIf_ControllerBusOff_CallbackBool = (char)0;
  Mock.CanIf_ControllerBusOff_CallbackFunctionPointer = Callback;
}

void CanIf_ControllerBusOff_CMockIgnoreArg_ControllerId(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE* cmock_call_instance = (CMOCK_CanIf_ControllerBusOff_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.CanIf_ControllerBusOff_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_ControllerId = 1;
}

