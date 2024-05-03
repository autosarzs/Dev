set(
    port_swc_tests_sources_list
    # Main test files
    ${port_swc}/tests/test_port_swc.c
    # Any mocked file will be under stub/mock_headerFileName.c
    ${port_swc}/tests/stubs/mock_Det.c
    # Include Test Runners 
    ${port_swc}/tests/test_runners/port_Runner.c
    ${port_swc}/tests/test_runners/all_tests.c

)

set(
    port_swc_ut_sources_list

    ${port_swc}/core/Port.c
    ${gendata}/Port_Lcfg.c
    ${gendata}/Port_PBcfg.c

    # Add Unity/CMock Framework Source files [WILL BE FIXED IN EACH UNIT TEST DIR]
    ${UNITY_ROOT_DIR}/src/unity.c
    ${UNITY_ROOT_DIR}/extras/fixture/src/unity_fixture.c
    ${CMOCK_ROOT_DIR}/src/cmock.c
)

set (
    port_swc_mock_header_files
    
    ${stubs}/Det.h

)

set(
    port_swc_tests_includes

    ${port_swc}/core
    ${gendata}

    ${common_includes}
    ${platform}
    ${stubs}
    #Include mocked folder 
    ${dio_swc}/tests/stubs
    # Include Unity/CMock Framework [WILL BE FIXED IN EACH UNIT TEST DIR]
    ${UNITY_ROOT_DIR}/src
    ${UNITY_ROOT_DIR}/extras/fixture/src
    ${UNITY_ROOT_DIR}/extras/memory/src/
    ${CMOCK_ROOT_DIR}/src
)

set(
    port_swc_tests_compile_options
)

set(
    port_swc_tests_defines
)
