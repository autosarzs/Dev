set(
    app_swc_sources_list

    ${app_swc}/core/main.c
    ${app_swc}/core/tm4c123gh6pz_startup_ccs_gcc.c
    ${stubs}/stub.c
    ${platform}/can_lib.c
    ${platform}/irq.c
    ${platform}/Timer0A.c
)

set(
    app_swc_includes

    ${app_swc}/core
    ${can_swc}/core
    ${gendata}
    
    ${common_includes}
    ${platform}
    ${stubs}
)


set(
    app_swc_compile_options
)

set(
    app_swc_defines
)


set(
    app_swc_libs

    "can_swc"
    "port_swc"
    "dio_swc"
    "-T ${app_swc}/core/tm4c123gh6pz.lds"
)

    