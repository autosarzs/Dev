set(
    dio_swc_tests_sources_list

    ${dio_swc}/tests/unit/test_dio_swc.c

    # Any mocked file will be under ${MOCK_FILE_PATH}/mocks/mock_headerFileName.c
    ${MOCK_FILE_PATH}/mocks/mock_Det.c
    # Include Test Runners 
    ${dio_swc}/tests/unit/test_runners/dio_Runner.c
    ${dio_swc}/tests/unit/test_runners/all_tests.c
)

set(
    dio_swc_ut_sources_list
    
    ${dio_swc}/core/Dio.c
    ${gendata}/Dio_Lcfg.c

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
    ${dio_swc}/tests/unit/stubs
    ${MOCK_FILE_PATH}/mocks/
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

