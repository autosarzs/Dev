set(
    dio_swc_tests_sources_list

    tests/test_dio_swc.c
    ${port_swc}/core/Port.c
    ${stubs}/stub.c
)

set(
    dio_swc_tests_includes

    ${dio_swc}/core
    ${dio_swc}/config

    ${port_swc}/core
    ${port_swc}/config

    ${can_swc}/core
    ${can_swc}/config

    ${Infrastructure_inc}
    ${platform_inc}
    ${stubs}
)

set(
    dio_swc_tests_compile_options
)

set(
    dio_swc_tests_defines
)
