message(STATUS "SW_DIR = ${SW_DIR}")

set( CMAKE_INSTALL_PREFIX "./" CACHE PATH "Default install path")

# Common Directories
set( common_includes "${SW_DIR}/common/includes" CACHE PATH "Default")
set( platform "${SW_DIR}/common/platform" CACHE PATH "Default")
set( stubs "${SW_DIR}/common/stubs" CACHE PATH "Default")

set( application_dir "${SW_DIR}/application" CACHE PATH "Default")
set( bsw_dir "${SW_DIR}/bsw" CACHE PATH "Default")
set( mcal_dir "${SW_DIR}/bsw/mcal" CACHE PATH "Default")

set( gendata "${SW_DIR}/gendata" CACHE PATH "Default")

# MCAL Software Components
set( can_swc  "${SW_DIR}/bsw/mcal/can_swc" CACHE PATH "Default")
set( port_swc  "${SW_DIR}/bsw/mcal/port_swc" CACHE PATH "Default")
set( dio_swc  "${SW_DIR}/bsw/mcal/dio_swc" CACHE PATH "Default")

# App Software Components
set( app_swc  "${SW_DIR}/application/app_swc" CACHE PATH "Default")
