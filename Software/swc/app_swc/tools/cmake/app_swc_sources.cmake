set(
    app_swc_sources_list

    core/main.c
    ${stubs}/stub.c
    ${platform_src}/can_lib.c
    ${platform_src}/irq.c
    ${platform_src}/Timer0A.c
    core/tm4c123gh6pz_startup_ccs_gcc.c

)
