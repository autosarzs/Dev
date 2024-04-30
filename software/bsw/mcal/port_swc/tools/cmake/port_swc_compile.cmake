

set(
    port_swc_sources_list

    ${port_swc}/core/Port.c
    ${port_swc}/config/Port_Lcfg.c
    ${port_swc}/config/Port_PBcfg.c
)

set(
    port_swc_includes

    ${port_swc}/core
    ${port_swc}/config

    ${infrastructure}/inc
    ${platform}/inc
    ${stubs}
)

set(
    port_swc_defines
)

set(
    port_swc_compile_options
)
