

set(
    port_swc_sources_list

    ${port_swc}/core/Port.c
    ${gendata}/Port_Lcfg.c
    ${gendata}/Port_PBcfg.c
)

set(
    port_swc_includes

    ${port_swc}/core
    ${gendata}
    ${common_includes}
    ${platform}
    ${stubs}
)

set(
    port_swc_defines
)

set(
    port_swc_compile_options
)
