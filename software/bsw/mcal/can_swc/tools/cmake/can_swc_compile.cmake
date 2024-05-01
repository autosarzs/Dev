set(
    can_swc_sources_list

    ${can_swc}/core/Can.c
    ${gendata}/Can_PBcfg.c

)

set(
    can_swc_includes

    ${can_swc}/core

    ${gendata}
    ${platform}
    ${common_includes}
    ${stubs}
)

set(
    can_swc_compile_options
)

set(
    can_swc_defines
)
