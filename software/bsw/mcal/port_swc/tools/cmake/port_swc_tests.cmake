set(
    port_swc_tests_sources_list
    # Main test files
    ${port_swc}/tests/unit/test_port_swc.c
    # Any mocked file will be under ${MOCK_FILE_PATH}/mocks/mock_headerFileName.c
    ${MOCK_FILE_PATH}/mocks/mock_Det.c
    # Include Test Runners 
    ${port_swc}/tests/unit/test_runners/port_Runner.c
    ${port_swc}/tests/unit/test_runners/all_tests.c

)

set(
    port_swc_ut_sources_list

    ${port_swc}/core/Port.c
    ${gendata}/Port_Lcfg.c
    ${gendata}/Port_PBcfg.c

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
    ${MOCK_FILE_PATH}/mocks
)

set(
    port_swc_tests_compile_options
)

set(
    port_swc_tests_defines
)
