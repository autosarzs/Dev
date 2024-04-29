set(
    port_swc_tests_sources_list

    ${port_swc}/tests/test_port_swc.c
)

set(
    port_swc_ut_sources_list

    ${port_swc}/core/Port.c
    ${port_swc}/config/Port_Lcfg.c
    ${port_swc}/config/Port_PBcfg.c
)

set(
    port_swc_tests_includes

    ${port_swc}/core
    ${port_swc}/config
    ${port_swc}/tests/stubs

    ${infrastructure}/inc
    ${platform}/inc

    ${stubs}
)

set(
    port_swc_tests_compile_options
)

set(
    port_swc_tests_defines
)
