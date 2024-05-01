set(
    dio_swc_tests_sources_list

    ${dio_swc}/tests/test_dio_swc.c
    ${dio_swc}/tests/stubs/test_dio_swc_stubs.c
)

set(
    dio_swc_ut_sources_list

    ${dio_swc}/core/Dio.c
    ${gendata}/Dio_Lcfg.c
)

set(
    dio_swc_tests_includes

    ${dio_swc}/core
    ${port_swc}/core
    ${dio_swc}/tests/stubs
    ${gendata}

    ${common_includes}
    ${platform}
    ${stubs}
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
