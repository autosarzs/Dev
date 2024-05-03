/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_CAN_LIB_H
#define _MOCK_CAN_LIB_H

#include "unity.h"
#include "can_lib.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void mock_can_lib_Init(void);
void mock_can_lib_Destroy(void);
void mock_can_lib_Verify(void);


typedef void(*cmock_can_lib_func_ptr1)(void);


#define CANBitTimingGet_Ignore() CANBitTimingGet_CMockIgnore()
void CANBitTimingGet_CMockIgnore(void);
#define CANBitTimingGet_StopIgnore() CANBitTimingGet_CMockStopIgnore()
void CANBitTimingGet_CMockStopIgnore(void);
#define CANBitTimingGet_ExpectAnyArgs() CANBitTimingGet_CMockExpectAnyArgs(__LINE__)
void CANBitTimingGet_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANBitTimingGet_Expect(ui32Base, psClkParms) CANBitTimingGet_CMockExpect(__LINE__, ui32Base, psClkParms)
void CANBitTimingGet_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, tCANBitClkParms* psClkParms);
typedef void (* CMOCK_CANBitTimingGet_CALLBACK)(uint32 ui32Base, tCANBitClkParms* psClkParms, int cmock_num_calls);
void CANBitTimingGet_AddCallback(CMOCK_CANBitTimingGet_CALLBACK Callback);
void CANBitTimingGet_Stub(CMOCK_CANBitTimingGet_CALLBACK Callback);
#define CANBitTimingGet_StubWithCallback CANBitTimingGet_Stub
#define CANBitTimingGet_ExpectWithArray(ui32Base, psClkParms, psClkParms_Depth) CANBitTimingGet_CMockExpectWithArray(__LINE__, ui32Base, psClkParms, psClkParms_Depth)
void CANBitTimingGet_CMockExpectWithArray(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, tCANBitClkParms* psClkParms, int psClkParms_Depth);
#define CANBitTimingGet_ReturnThruPtr_psClkParms(psClkParms) CANBitTimingGet_CMockReturnMemThruPtr_psClkParms(__LINE__, psClkParms, sizeof(tCANBitClkParms))
#define CANBitTimingGet_ReturnArrayThruPtr_psClkParms(psClkParms, cmock_len) CANBitTimingGet_CMockReturnMemThruPtr_psClkParms(__LINE__, psClkParms, cmock_len * sizeof(*psClkParms))
#define CANBitTimingGet_ReturnMemThruPtr_psClkParms(psClkParms, cmock_size) CANBitTimingGet_CMockReturnMemThruPtr_psClkParms(__LINE__, psClkParms, cmock_size)
void CANBitTimingGet_CMockReturnMemThruPtr_psClkParms(UNITY_LINE_TYPE cmock_line, tCANBitClkParms const* psClkParms, size_t cmock_size);
#define CANBitTimingGet_IgnoreArg_ui32Base() CANBitTimingGet_CMockIgnoreArg_ui32Base(__LINE__)
void CANBitTimingGet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANBitTimingGet_IgnoreArg_psClkParms() CANBitTimingGet_CMockIgnoreArg_psClkParms(__LINE__)
void CANBitTimingGet_CMockIgnoreArg_psClkParms(UNITY_LINE_TYPE cmock_line);
#define CANBitTimingSet_Ignore() CANBitTimingSet_CMockIgnore()
void CANBitTimingSet_CMockIgnore(void);
#define CANBitTimingSet_StopIgnore() CANBitTimingSet_CMockStopIgnore()
void CANBitTimingSet_CMockStopIgnore(void);
#define CANBitTimingSet_ExpectAnyArgs() CANBitTimingSet_CMockExpectAnyArgs(__LINE__)
void CANBitTimingSet_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANBitTimingSet_Expect(ui32Base, psClkParms) CANBitTimingSet_CMockExpect(__LINE__, ui32Base, psClkParms)
void CANBitTimingSet_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, tCANBitClkParms* psClkParms);
typedef void (* CMOCK_CANBitTimingSet_CALLBACK)(uint32 ui32Base, tCANBitClkParms* psClkParms, int cmock_num_calls);
void CANBitTimingSet_AddCallback(CMOCK_CANBitTimingSet_CALLBACK Callback);
void CANBitTimingSet_Stub(CMOCK_CANBitTimingSet_CALLBACK Callback);
#define CANBitTimingSet_StubWithCallback CANBitTimingSet_Stub
#define CANBitTimingSet_ExpectWithArray(ui32Base, psClkParms, psClkParms_Depth) CANBitTimingSet_CMockExpectWithArray(__LINE__, ui32Base, psClkParms, psClkParms_Depth)
void CANBitTimingSet_CMockExpectWithArray(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, tCANBitClkParms* psClkParms, int psClkParms_Depth);
#define CANBitTimingSet_ReturnThruPtr_psClkParms(psClkParms) CANBitTimingSet_CMockReturnMemThruPtr_psClkParms(__LINE__, psClkParms, sizeof(tCANBitClkParms))
#define CANBitTimingSet_ReturnArrayThruPtr_psClkParms(psClkParms, cmock_len) CANBitTimingSet_CMockReturnMemThruPtr_psClkParms(__LINE__, psClkParms, cmock_len * sizeof(*psClkParms))
#define CANBitTimingSet_ReturnMemThruPtr_psClkParms(psClkParms, cmock_size) CANBitTimingSet_CMockReturnMemThruPtr_psClkParms(__LINE__, psClkParms, cmock_size)
void CANBitTimingSet_CMockReturnMemThruPtr_psClkParms(UNITY_LINE_TYPE cmock_line, tCANBitClkParms const* psClkParms, size_t cmock_size);
#define CANBitTimingSet_IgnoreArg_ui32Base() CANBitTimingSet_CMockIgnoreArg_ui32Base(__LINE__)
void CANBitTimingSet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANBitTimingSet_IgnoreArg_psClkParms() CANBitTimingSet_CMockIgnoreArg_psClkParms(__LINE__)
void CANBitTimingSet_CMockIgnoreArg_psClkParms(UNITY_LINE_TYPE cmock_line);
#define CANBitRateSet_IgnoreAndReturn(cmock_retval) CANBitRateSet_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void CANBitRateSet_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, uint32 cmock_to_return);
#define CANBitRateSet_StopIgnore() CANBitRateSet_CMockStopIgnore()
void CANBitRateSet_CMockStopIgnore(void);
#define CANBitRateSet_ExpectAnyArgsAndReturn(cmock_retval) CANBitRateSet_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void CANBitRateSet_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, uint32 cmock_to_return);
#define CANBitRateSet_ExpectAndReturn(ui32Base, ui32SourceClock, ui32BitRate, cmock_retval) CANBitRateSet_CMockExpectAndReturn(__LINE__, ui32Base, ui32SourceClock, ui32BitRate, cmock_retval)
void CANBitRateSet_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32SourceClock, uint32 ui32BitRate, uint32 cmock_to_return);
typedef uint32 (* CMOCK_CANBitRateSet_CALLBACK)(uint32 ui32Base, uint32 ui32SourceClock, uint32 ui32BitRate, int cmock_num_calls);
void CANBitRateSet_AddCallback(CMOCK_CANBitRateSet_CALLBACK Callback);
void CANBitRateSet_Stub(CMOCK_CANBitRateSet_CALLBACK Callback);
#define CANBitRateSet_StubWithCallback CANBitRateSet_Stub
#define CANBitRateSet_IgnoreArg_ui32Base() CANBitRateSet_CMockIgnoreArg_ui32Base(__LINE__)
void CANBitRateSet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANBitRateSet_IgnoreArg_ui32SourceClock() CANBitRateSet_CMockIgnoreArg_ui32SourceClock(__LINE__)
void CANBitRateSet_CMockIgnoreArg_ui32SourceClock(UNITY_LINE_TYPE cmock_line);
#define CANBitRateSet_IgnoreArg_ui32BitRate() CANBitRateSet_CMockIgnoreArg_ui32BitRate(__LINE__)
void CANBitRateSet_CMockIgnoreArg_ui32BitRate(UNITY_LINE_TYPE cmock_line);
#define CANDisable_Ignore() CANDisable_CMockIgnore()
void CANDisable_CMockIgnore(void);
#define CANDisable_StopIgnore() CANDisable_CMockStopIgnore()
void CANDisable_CMockStopIgnore(void);
#define CANDisable_ExpectAnyArgs() CANDisable_CMockExpectAnyArgs(__LINE__)
void CANDisable_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANDisable_Expect(ui32Base) CANDisable_CMockExpect(__LINE__, ui32Base)
void CANDisable_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base);
typedef void (* CMOCK_CANDisable_CALLBACK)(uint32 ui32Base, int cmock_num_calls);
void CANDisable_AddCallback(CMOCK_CANDisable_CALLBACK Callback);
void CANDisable_Stub(CMOCK_CANDisable_CALLBACK Callback);
#define CANDisable_StubWithCallback CANDisable_Stub
#define CANDisable_IgnoreArg_ui32Base() CANDisable_CMockIgnoreArg_ui32Base(__LINE__)
void CANDisable_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANEnable_Ignore() CANEnable_CMockIgnore()
void CANEnable_CMockIgnore(void);
#define CANEnable_StopIgnore() CANEnable_CMockStopIgnore()
void CANEnable_CMockStopIgnore(void);
#define CANEnable_ExpectAnyArgs() CANEnable_CMockExpectAnyArgs(__LINE__)
void CANEnable_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANEnable_Expect(ui32Base) CANEnable_CMockExpect(__LINE__, ui32Base)
void CANEnable_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base);
typedef void (* CMOCK_CANEnable_CALLBACK)(uint32 ui32Base, int cmock_num_calls);
void CANEnable_AddCallback(CMOCK_CANEnable_CALLBACK Callback);
void CANEnable_Stub(CMOCK_CANEnable_CALLBACK Callback);
#define CANEnable_StubWithCallback CANEnable_Stub
#define CANEnable_IgnoreArg_ui32Base() CANEnable_CMockIgnoreArg_ui32Base(__LINE__)
void CANEnable_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANErrCntrGet_IgnoreAndReturn(cmock_retval) CANErrCntrGet_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void CANErrCntrGet_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, boolean cmock_to_return);
#define CANErrCntrGet_StopIgnore() CANErrCntrGet_CMockStopIgnore()
void CANErrCntrGet_CMockStopIgnore(void);
#define CANErrCntrGet_ExpectAnyArgsAndReturn(cmock_retval) CANErrCntrGet_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void CANErrCntrGet_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, boolean cmock_to_return);
#define CANErrCntrGet_ExpectAndReturn(ui32Base, pui32RxCount, pui32TxCount, cmock_retval) CANErrCntrGet_CMockExpectAndReturn(__LINE__, ui32Base, pui32RxCount, pui32TxCount, cmock_retval)
void CANErrCntrGet_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32* pui32RxCount, uint32* pui32TxCount, boolean cmock_to_return);
typedef boolean (* CMOCK_CANErrCntrGet_CALLBACK)(uint32 ui32Base, uint32* pui32RxCount, uint32* pui32TxCount, int cmock_num_calls);
void CANErrCntrGet_AddCallback(CMOCK_CANErrCntrGet_CALLBACK Callback);
void CANErrCntrGet_Stub(CMOCK_CANErrCntrGet_CALLBACK Callback);
#define CANErrCntrGet_StubWithCallback CANErrCntrGet_Stub
#define CANErrCntrGet_ExpectWithArrayAndReturn(ui32Base, pui32RxCount, pui32RxCount_Depth, pui32TxCount, pui32TxCount_Depth, cmock_retval) CANErrCntrGet_CMockExpectWithArrayAndReturn(__LINE__, ui32Base, pui32RxCount, pui32RxCount_Depth, pui32TxCount, pui32TxCount_Depth, cmock_retval)
void CANErrCntrGet_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32* pui32RxCount, int pui32RxCount_Depth, uint32* pui32TxCount, int pui32TxCount_Depth, boolean cmock_to_return);
#define CANErrCntrGet_ReturnThruPtr_pui32RxCount(pui32RxCount) CANErrCntrGet_CMockReturnMemThruPtr_pui32RxCount(__LINE__, pui32RxCount, sizeof(uint32))
#define CANErrCntrGet_ReturnArrayThruPtr_pui32RxCount(pui32RxCount, cmock_len) CANErrCntrGet_CMockReturnMemThruPtr_pui32RxCount(__LINE__, pui32RxCount, cmock_len * sizeof(*pui32RxCount))
#define CANErrCntrGet_ReturnMemThruPtr_pui32RxCount(pui32RxCount, cmock_size) CANErrCntrGet_CMockReturnMemThruPtr_pui32RxCount(__LINE__, pui32RxCount, cmock_size)
void CANErrCntrGet_CMockReturnMemThruPtr_pui32RxCount(UNITY_LINE_TYPE cmock_line, uint32 const* pui32RxCount, size_t cmock_size);
#define CANErrCntrGet_ReturnThruPtr_pui32TxCount(pui32TxCount) CANErrCntrGet_CMockReturnMemThruPtr_pui32TxCount(__LINE__, pui32TxCount, sizeof(uint32))
#define CANErrCntrGet_ReturnArrayThruPtr_pui32TxCount(pui32TxCount, cmock_len) CANErrCntrGet_CMockReturnMemThruPtr_pui32TxCount(__LINE__, pui32TxCount, cmock_len * sizeof(*pui32TxCount))
#define CANErrCntrGet_ReturnMemThruPtr_pui32TxCount(pui32TxCount, cmock_size) CANErrCntrGet_CMockReturnMemThruPtr_pui32TxCount(__LINE__, pui32TxCount, cmock_size)
void CANErrCntrGet_CMockReturnMemThruPtr_pui32TxCount(UNITY_LINE_TYPE cmock_line, uint32 const* pui32TxCount, size_t cmock_size);
#define CANErrCntrGet_IgnoreArg_ui32Base() CANErrCntrGet_CMockIgnoreArg_ui32Base(__LINE__)
void CANErrCntrGet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANErrCntrGet_IgnoreArg_pui32RxCount() CANErrCntrGet_CMockIgnoreArg_pui32RxCount(__LINE__)
void CANErrCntrGet_CMockIgnoreArg_pui32RxCount(UNITY_LINE_TYPE cmock_line);
#define CANErrCntrGet_IgnoreArg_pui32TxCount() CANErrCntrGet_CMockIgnoreArg_pui32TxCount(__LINE__)
void CANErrCntrGet_CMockIgnoreArg_pui32TxCount(UNITY_LINE_TYPE cmock_line);
#define CANInit_Ignore() CANInit_CMockIgnore()
void CANInit_CMockIgnore(void);
#define CANInit_StopIgnore() CANInit_CMockStopIgnore()
void CANInit_CMockStopIgnore(void);
#define CANInit_ExpectAnyArgs() CANInit_CMockExpectAnyArgs(__LINE__)
void CANInit_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANInit_Expect(ui32Base) CANInit_CMockExpect(__LINE__, ui32Base)
void CANInit_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base);
typedef void (* CMOCK_CANInit_CALLBACK)(uint32 ui32Base, int cmock_num_calls);
void CANInit_AddCallback(CMOCK_CANInit_CALLBACK Callback);
void CANInit_Stub(CMOCK_CANInit_CALLBACK Callback);
#define CANInit_StubWithCallback CANInit_Stub
#define CANInit_IgnoreArg_ui32Base() CANInit_CMockIgnoreArg_ui32Base(__LINE__)
void CANInit_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANIntClear_Ignore() CANIntClear_CMockIgnore()
void CANIntClear_CMockIgnore(void);
#define CANIntClear_StopIgnore() CANIntClear_CMockStopIgnore()
void CANIntClear_CMockStopIgnore(void);
#define CANIntClear_ExpectAnyArgs() CANIntClear_CMockExpectAnyArgs(__LINE__)
void CANIntClear_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANIntClear_Expect(ui32Base, ui32IntClr) CANIntClear_CMockExpect(__LINE__, ui32Base, ui32IntClr)
void CANIntClear_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32IntClr);
typedef void (* CMOCK_CANIntClear_CALLBACK)(uint32 ui32Base, uint32 ui32IntClr, int cmock_num_calls);
void CANIntClear_AddCallback(CMOCK_CANIntClear_CALLBACK Callback);
void CANIntClear_Stub(CMOCK_CANIntClear_CALLBACK Callback);
#define CANIntClear_StubWithCallback CANIntClear_Stub
#define CANIntClear_IgnoreArg_ui32Base() CANIntClear_CMockIgnoreArg_ui32Base(__LINE__)
void CANIntClear_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANIntClear_IgnoreArg_ui32IntClr() CANIntClear_CMockIgnoreArg_ui32IntClr(__LINE__)
void CANIntClear_CMockIgnoreArg_ui32IntClr(UNITY_LINE_TYPE cmock_line);
#define CANIntDisable_Ignore() CANIntDisable_CMockIgnore()
void CANIntDisable_CMockIgnore(void);
#define CANIntDisable_StopIgnore() CANIntDisable_CMockStopIgnore()
void CANIntDisable_CMockStopIgnore(void);
#define CANIntDisable_ExpectAnyArgs() CANIntDisable_CMockExpectAnyArgs(__LINE__)
void CANIntDisable_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANIntDisable_Expect(ui32Base, ui32IntFlags) CANIntDisable_CMockExpect(__LINE__, ui32Base, ui32IntFlags)
void CANIntDisable_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32IntFlags);
typedef void (* CMOCK_CANIntDisable_CALLBACK)(uint32 ui32Base, uint32 ui32IntFlags, int cmock_num_calls);
void CANIntDisable_AddCallback(CMOCK_CANIntDisable_CALLBACK Callback);
void CANIntDisable_Stub(CMOCK_CANIntDisable_CALLBACK Callback);
#define CANIntDisable_StubWithCallback CANIntDisable_Stub
#define CANIntDisable_IgnoreArg_ui32Base() CANIntDisable_CMockIgnoreArg_ui32Base(__LINE__)
void CANIntDisable_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANIntDisable_IgnoreArg_ui32IntFlags() CANIntDisable_CMockIgnoreArg_ui32IntFlags(__LINE__)
void CANIntDisable_CMockIgnoreArg_ui32IntFlags(UNITY_LINE_TYPE cmock_line);
#define CANIntEnable_Ignore() CANIntEnable_CMockIgnore()
void CANIntEnable_CMockIgnore(void);
#define CANIntEnable_StopIgnore() CANIntEnable_CMockStopIgnore()
void CANIntEnable_CMockStopIgnore(void);
#define CANIntEnable_ExpectAnyArgs() CANIntEnable_CMockExpectAnyArgs(__LINE__)
void CANIntEnable_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANIntEnable_Expect(ui32Base, ui32IntFlags) CANIntEnable_CMockExpect(__LINE__, ui32Base, ui32IntFlags)
void CANIntEnable_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32IntFlags);
typedef void (* CMOCK_CANIntEnable_CALLBACK)(uint32 ui32Base, uint32 ui32IntFlags, int cmock_num_calls);
void CANIntEnable_AddCallback(CMOCK_CANIntEnable_CALLBACK Callback);
void CANIntEnable_Stub(CMOCK_CANIntEnable_CALLBACK Callback);
#define CANIntEnable_StubWithCallback CANIntEnable_Stub
#define CANIntEnable_IgnoreArg_ui32Base() CANIntEnable_CMockIgnoreArg_ui32Base(__LINE__)
void CANIntEnable_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANIntEnable_IgnoreArg_ui32IntFlags() CANIntEnable_CMockIgnoreArg_ui32IntFlags(__LINE__)
void CANIntEnable_CMockIgnoreArg_ui32IntFlags(UNITY_LINE_TYPE cmock_line);
#define CANIntRegister_Ignore() CANIntRegister_CMockIgnore()
void CANIntRegister_CMockIgnore(void);
#define CANIntRegister_StopIgnore() CANIntRegister_CMockStopIgnore()
void CANIntRegister_CMockStopIgnore(void);
#define CANIntRegister_ExpectAnyArgs() CANIntRegister_CMockExpectAnyArgs(__LINE__)
void CANIntRegister_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANIntRegister_Expect(ui32Base, pfnHandler) CANIntRegister_CMockExpect(__LINE__, ui32Base, pfnHandler)
void CANIntRegister_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, cmock_can_lib_func_ptr1 pfnHandler);
typedef void (* CMOCK_CANIntRegister_CALLBACK)(uint32 ui32Base, cmock_can_lib_func_ptr1 pfnHandler, int cmock_num_calls);
void CANIntRegister_AddCallback(CMOCK_CANIntRegister_CALLBACK Callback);
void CANIntRegister_Stub(CMOCK_CANIntRegister_CALLBACK Callback);
#define CANIntRegister_StubWithCallback CANIntRegister_Stub
#define CANIntRegister_IgnoreArg_ui32Base() CANIntRegister_CMockIgnoreArg_ui32Base(__LINE__)
void CANIntRegister_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANIntRegister_IgnoreArg_pfnHandler() CANIntRegister_CMockIgnoreArg_pfnHandler(__LINE__)
void CANIntRegister_CMockIgnoreArg_pfnHandler(UNITY_LINE_TYPE cmock_line);
#define CANIntStatus_IgnoreAndReturn(cmock_retval) CANIntStatus_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void CANIntStatus_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, uint32 cmock_to_return);
#define CANIntStatus_StopIgnore() CANIntStatus_CMockStopIgnore()
void CANIntStatus_CMockStopIgnore(void);
#define CANIntStatus_ExpectAnyArgsAndReturn(cmock_retval) CANIntStatus_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void CANIntStatus_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, uint32 cmock_to_return);
#define CANIntStatus_ExpectAndReturn(ui32Base, eIntStsReg, cmock_retval) CANIntStatus_CMockExpectAndReturn(__LINE__, ui32Base, eIntStsReg, cmock_retval)
void CANIntStatus_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, tCANIntStsReg eIntStsReg, uint32 cmock_to_return);
typedef uint32 (* CMOCK_CANIntStatus_CALLBACK)(uint32 ui32Base, tCANIntStsReg eIntStsReg, int cmock_num_calls);
void CANIntStatus_AddCallback(CMOCK_CANIntStatus_CALLBACK Callback);
void CANIntStatus_Stub(CMOCK_CANIntStatus_CALLBACK Callback);
#define CANIntStatus_StubWithCallback CANIntStatus_Stub
#define CANIntStatus_IgnoreArg_ui32Base() CANIntStatus_CMockIgnoreArg_ui32Base(__LINE__)
void CANIntStatus_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANIntStatus_IgnoreArg_eIntStsReg() CANIntStatus_CMockIgnoreArg_eIntStsReg(__LINE__)
void CANIntStatus_CMockIgnoreArg_eIntStsReg(UNITY_LINE_TYPE cmock_line);
#define CANIntUnregister_Ignore() CANIntUnregister_CMockIgnore()
void CANIntUnregister_CMockIgnore(void);
#define CANIntUnregister_StopIgnore() CANIntUnregister_CMockStopIgnore()
void CANIntUnregister_CMockStopIgnore(void);
#define CANIntUnregister_ExpectAnyArgs() CANIntUnregister_CMockExpectAnyArgs(__LINE__)
void CANIntUnregister_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANIntUnregister_Expect(ui32Base) CANIntUnregister_CMockExpect(__LINE__, ui32Base)
void CANIntUnregister_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base);
typedef void (* CMOCK_CANIntUnregister_CALLBACK)(uint32 ui32Base, int cmock_num_calls);
void CANIntUnregister_AddCallback(CMOCK_CANIntUnregister_CALLBACK Callback);
void CANIntUnregister_Stub(CMOCK_CANIntUnregister_CALLBACK Callback);
#define CANIntUnregister_StubWithCallback CANIntUnregister_Stub
#define CANIntUnregister_IgnoreArg_ui32Base() CANIntUnregister_CMockIgnoreArg_ui32Base(__LINE__)
void CANIntUnregister_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANMessageClear_Ignore() CANMessageClear_CMockIgnore()
void CANMessageClear_CMockIgnore(void);
#define CANMessageClear_StopIgnore() CANMessageClear_CMockStopIgnore()
void CANMessageClear_CMockStopIgnore(void);
#define CANMessageClear_ExpectAnyArgs() CANMessageClear_CMockExpectAnyArgs(__LINE__)
void CANMessageClear_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANMessageClear_Expect(ui32Base, ui32ObjID) CANMessageClear_CMockExpect(__LINE__, ui32Base, ui32ObjID)
void CANMessageClear_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32ObjID);
typedef void (* CMOCK_CANMessageClear_CALLBACK)(uint32 ui32Base, uint32 ui32ObjID, int cmock_num_calls);
void CANMessageClear_AddCallback(CMOCK_CANMessageClear_CALLBACK Callback);
void CANMessageClear_Stub(CMOCK_CANMessageClear_CALLBACK Callback);
#define CANMessageClear_StubWithCallback CANMessageClear_Stub
#define CANMessageClear_IgnoreArg_ui32Base() CANMessageClear_CMockIgnoreArg_ui32Base(__LINE__)
void CANMessageClear_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANMessageClear_IgnoreArg_ui32ObjID() CANMessageClear_CMockIgnoreArg_ui32ObjID(__LINE__)
void CANMessageClear_CMockIgnoreArg_ui32ObjID(UNITY_LINE_TYPE cmock_line);
#define CANMessageGet_Ignore() CANMessageGet_CMockIgnore()
void CANMessageGet_CMockIgnore(void);
#define CANMessageGet_StopIgnore() CANMessageGet_CMockStopIgnore()
void CANMessageGet_CMockStopIgnore(void);
#define CANMessageGet_ExpectAnyArgs() CANMessageGet_CMockExpectAnyArgs(__LINE__)
void CANMessageGet_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANMessageGet_Expect(ui32Base, ui32ObjID, psMsgObject, bClrPendingInt) CANMessageGet_CMockExpect(__LINE__, ui32Base, ui32ObjID, psMsgObject, bClrPendingInt)
void CANMessageGet_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32ObjID, tCANMsgObject* psMsgObject, boolean bClrPendingInt);
typedef void (* CMOCK_CANMessageGet_CALLBACK)(uint32 ui32Base, uint32 ui32ObjID, tCANMsgObject* psMsgObject, boolean bClrPendingInt, int cmock_num_calls);
void CANMessageGet_AddCallback(CMOCK_CANMessageGet_CALLBACK Callback);
void CANMessageGet_Stub(CMOCK_CANMessageGet_CALLBACK Callback);
#define CANMessageGet_StubWithCallback CANMessageGet_Stub
#define CANMessageGet_ExpectWithArray(ui32Base, ui32ObjID, psMsgObject, psMsgObject_Depth, bClrPendingInt) CANMessageGet_CMockExpectWithArray(__LINE__, ui32Base, ui32ObjID, psMsgObject, psMsgObject_Depth, bClrPendingInt)
void CANMessageGet_CMockExpectWithArray(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32ObjID, tCANMsgObject* psMsgObject, int psMsgObject_Depth, boolean bClrPendingInt);
#define CANMessageGet_ReturnThruPtr_psMsgObject(psMsgObject) CANMessageGet_CMockReturnMemThruPtr_psMsgObject(__LINE__, psMsgObject, sizeof(tCANMsgObject))
#define CANMessageGet_ReturnArrayThruPtr_psMsgObject(psMsgObject, cmock_len) CANMessageGet_CMockReturnMemThruPtr_psMsgObject(__LINE__, psMsgObject, cmock_len * sizeof(*psMsgObject))
#define CANMessageGet_ReturnMemThruPtr_psMsgObject(psMsgObject, cmock_size) CANMessageGet_CMockReturnMemThruPtr_psMsgObject(__LINE__, psMsgObject, cmock_size)
void CANMessageGet_CMockReturnMemThruPtr_psMsgObject(UNITY_LINE_TYPE cmock_line, tCANMsgObject const* psMsgObject, size_t cmock_size);
#define CANMessageGet_IgnoreArg_ui32Base() CANMessageGet_CMockIgnoreArg_ui32Base(__LINE__)
void CANMessageGet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANMessageGet_IgnoreArg_ui32ObjID() CANMessageGet_CMockIgnoreArg_ui32ObjID(__LINE__)
void CANMessageGet_CMockIgnoreArg_ui32ObjID(UNITY_LINE_TYPE cmock_line);
#define CANMessageGet_IgnoreArg_psMsgObject() CANMessageGet_CMockIgnoreArg_psMsgObject(__LINE__)
void CANMessageGet_CMockIgnoreArg_psMsgObject(UNITY_LINE_TYPE cmock_line);
#define CANMessageGet_IgnoreArg_bClrPendingInt() CANMessageGet_CMockIgnoreArg_bClrPendingInt(__LINE__)
void CANMessageGet_CMockIgnoreArg_bClrPendingInt(UNITY_LINE_TYPE cmock_line);
#define CANMessageSet_Ignore() CANMessageSet_CMockIgnore()
void CANMessageSet_CMockIgnore(void);
#define CANMessageSet_StopIgnore() CANMessageSet_CMockStopIgnore()
void CANMessageSet_CMockStopIgnore(void);
#define CANMessageSet_ExpectAnyArgs() CANMessageSet_CMockExpectAnyArgs(__LINE__)
void CANMessageSet_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANMessageSet_Expect(ui32Base, ui32ObjID, psMsgObject, eMsgType) CANMessageSet_CMockExpect(__LINE__, ui32Base, ui32ObjID, psMsgObject, eMsgType)
void CANMessageSet_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32ObjID, tCANMsgObject* psMsgObject, tMsgObjType eMsgType);
typedef void (* CMOCK_CANMessageSet_CALLBACK)(uint32 ui32Base, uint32 ui32ObjID, tCANMsgObject* psMsgObject, tMsgObjType eMsgType, int cmock_num_calls);
void CANMessageSet_AddCallback(CMOCK_CANMessageSet_CALLBACK Callback);
void CANMessageSet_Stub(CMOCK_CANMessageSet_CALLBACK Callback);
#define CANMessageSet_StubWithCallback CANMessageSet_Stub
#define CANMessageSet_ExpectWithArray(ui32Base, ui32ObjID, psMsgObject, psMsgObject_Depth, eMsgType) CANMessageSet_CMockExpectWithArray(__LINE__, ui32Base, ui32ObjID, psMsgObject, psMsgObject_Depth, eMsgType)
void CANMessageSet_CMockExpectWithArray(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, uint32 ui32ObjID, tCANMsgObject* psMsgObject, int psMsgObject_Depth, tMsgObjType eMsgType);
#define CANMessageSet_ReturnThruPtr_psMsgObject(psMsgObject) CANMessageSet_CMockReturnMemThruPtr_psMsgObject(__LINE__, psMsgObject, sizeof(tCANMsgObject))
#define CANMessageSet_ReturnArrayThruPtr_psMsgObject(psMsgObject, cmock_len) CANMessageSet_CMockReturnMemThruPtr_psMsgObject(__LINE__, psMsgObject, cmock_len * sizeof(*psMsgObject))
#define CANMessageSet_ReturnMemThruPtr_psMsgObject(psMsgObject, cmock_size) CANMessageSet_CMockReturnMemThruPtr_psMsgObject(__LINE__, psMsgObject, cmock_size)
void CANMessageSet_CMockReturnMemThruPtr_psMsgObject(UNITY_LINE_TYPE cmock_line, tCANMsgObject const* psMsgObject, size_t cmock_size);
#define CANMessageSet_IgnoreArg_ui32Base() CANMessageSet_CMockIgnoreArg_ui32Base(__LINE__)
void CANMessageSet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANMessageSet_IgnoreArg_ui32ObjID() CANMessageSet_CMockIgnoreArg_ui32ObjID(__LINE__)
void CANMessageSet_CMockIgnoreArg_ui32ObjID(UNITY_LINE_TYPE cmock_line);
#define CANMessageSet_IgnoreArg_psMsgObject() CANMessageSet_CMockIgnoreArg_psMsgObject(__LINE__)
void CANMessageSet_CMockIgnoreArg_psMsgObject(UNITY_LINE_TYPE cmock_line);
#define CANMessageSet_IgnoreArg_eMsgType() CANMessageSet_CMockIgnoreArg_eMsgType(__LINE__)
void CANMessageSet_CMockIgnoreArg_eMsgType(UNITY_LINE_TYPE cmock_line);
#define CANRetryGet_IgnoreAndReturn(cmock_retval) CANRetryGet_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void CANRetryGet_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, boolean cmock_to_return);
#define CANRetryGet_StopIgnore() CANRetryGet_CMockStopIgnore()
void CANRetryGet_CMockStopIgnore(void);
#define CANRetryGet_ExpectAnyArgsAndReturn(cmock_retval) CANRetryGet_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void CANRetryGet_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, boolean cmock_to_return);
#define CANRetryGet_ExpectAndReturn(ui32Base, cmock_retval) CANRetryGet_CMockExpectAndReturn(__LINE__, ui32Base, cmock_retval)
void CANRetryGet_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, boolean cmock_to_return);
typedef boolean (* CMOCK_CANRetryGet_CALLBACK)(uint32 ui32Base, int cmock_num_calls);
void CANRetryGet_AddCallback(CMOCK_CANRetryGet_CALLBACK Callback);
void CANRetryGet_Stub(CMOCK_CANRetryGet_CALLBACK Callback);
#define CANRetryGet_StubWithCallback CANRetryGet_Stub
#define CANRetryGet_IgnoreArg_ui32Base() CANRetryGet_CMockIgnoreArg_ui32Base(__LINE__)
void CANRetryGet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANRetrySet_Ignore() CANRetrySet_CMockIgnore()
void CANRetrySet_CMockIgnore(void);
#define CANRetrySet_StopIgnore() CANRetrySet_CMockStopIgnore()
void CANRetrySet_CMockStopIgnore(void);
#define CANRetrySet_ExpectAnyArgs() CANRetrySet_CMockExpectAnyArgs(__LINE__)
void CANRetrySet_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define CANRetrySet_Expect(ui32Base, bAutoRetry) CANRetrySet_CMockExpect(__LINE__, ui32Base, bAutoRetry)
void CANRetrySet_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, boolean bAutoRetry);
typedef void (* CMOCK_CANRetrySet_CALLBACK)(uint32 ui32Base, boolean bAutoRetry, int cmock_num_calls);
void CANRetrySet_AddCallback(CMOCK_CANRetrySet_CALLBACK Callback);
void CANRetrySet_Stub(CMOCK_CANRetrySet_CALLBACK Callback);
#define CANRetrySet_StubWithCallback CANRetrySet_Stub
#define CANRetrySet_IgnoreArg_ui32Base() CANRetrySet_CMockIgnoreArg_ui32Base(__LINE__)
void CANRetrySet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANRetrySet_IgnoreArg_bAutoRetry() CANRetrySet_CMockIgnoreArg_bAutoRetry(__LINE__)
void CANRetrySet_CMockIgnoreArg_bAutoRetry(UNITY_LINE_TYPE cmock_line);
#define CANStatusGet_IgnoreAndReturn(cmock_retval) CANStatusGet_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void CANStatusGet_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, uint32 cmock_to_return);
#define CANStatusGet_StopIgnore() CANStatusGet_CMockStopIgnore()
void CANStatusGet_CMockStopIgnore(void);
#define CANStatusGet_ExpectAnyArgsAndReturn(cmock_retval) CANStatusGet_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void CANStatusGet_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, uint32 cmock_to_return);
#define CANStatusGet_ExpectAndReturn(ui32Base, eStatusReg, cmock_retval) CANStatusGet_CMockExpectAndReturn(__LINE__, ui32Base, eStatusReg, cmock_retval)
void CANStatusGet_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32 ui32Base, tCANStsReg eStatusReg, uint32 cmock_to_return);
typedef uint32 (* CMOCK_CANStatusGet_CALLBACK)(uint32 ui32Base, tCANStsReg eStatusReg, int cmock_num_calls);
void CANStatusGet_AddCallback(CMOCK_CANStatusGet_CALLBACK Callback);
void CANStatusGet_Stub(CMOCK_CANStatusGet_CALLBACK Callback);
#define CANStatusGet_StubWithCallback CANStatusGet_Stub
#define CANStatusGet_IgnoreArg_ui32Base() CANStatusGet_CMockIgnoreArg_ui32Base(__LINE__)
void CANStatusGet_CMockIgnoreArg_ui32Base(UNITY_LINE_TYPE cmock_line);
#define CANStatusGet_IgnoreArg_eStatusReg() CANStatusGet_CMockIgnoreArg_eStatusReg(__LINE__)
void CANStatusGet_CMockIgnoreArg_eStatusReg(UNITY_LINE_TYPE cmock_line);

#ifdef __cplusplus
}
#endif

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
