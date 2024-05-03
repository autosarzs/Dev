set(
    dio_swc_tests_sources_list

    ${dio_swc}/tests/test_dio_swc.c

    # Any mocked file will be under stub/mock_headerFileName.c
    ${dio_swc}/tests/stubs/mock_Det.c
    # Include Test Runners 
    ${dio_swc}/tests/test_runners/dio_Runner.c
    ${dio_swc}/tests/test_runners/all_tests.c
)

set(
    dio_swc_ut_sources_list
    
    ${dio_swc}/core/Dio.c
    ${gendata}/Dio_Lcfg.c

    # Add Unity/CMock Framework Source files [WILL BE FIXED IN EACH UNIT TEST DIR]
    ${UNITY_ROOT_DIR}/src/unity.c
    ${UNITY_ROOT_DIR}/extras/fixture/src/unity_fixture.c
    ${CMOCK_ROOT_DIR}/src/cmock.c
)

set (
    dio_swc_mock_header_files
    
    ${stubs}/Det.h

)

set(
    dio_swc_tests_includes

    ${dio_swc}/core
    ${port_swc}/core
    ${gendata}
    ${common_includes}
    ${platform}
    ${stubs}
    #Include mocked folder 
    ${dio_swc}/tests/stubs
    # Include Unity/CMock Framework [WILL BE FIXED IN EACH UNIT TEST DIR]
    ${CMOCK_ROOT_DIR}/src
    ${UNITY_ROOT_DIR}/src
    ${UNITY_ROOT_DIR}/extras/fixture/src
    ${UNITY_ROOT_DIR}/extras/memory/src/
)

set(
    dio_swc_tests_compile_options

)

set(
    dio_swc_tests_defines
)

set(
    dio_swc_tests_libs
    "dio_swc"
    "port_swc"
)

