message(STATUS "SW_DIR = ${SW_DIR}")

set( CMAKE_INSTALL_PREFIX "./" CACHE PATH "Default install path")

# Common Directories
set( Infrastructure_inc "${SW_DIR}/bsw/static/Infrastructure/inc" CACHE PATH "Default")
set( platform_inc "${SW_DIR}/bsw/static/Infrastructure/platform/inc" CACHE PATH "Default")
set( platform_src "${SW_DIR}/bsw/static/Infrastructure/platform/src" CACHE PATH "Default")
set( stubs "${SW_DIR}/bsw/stub" CACHE PATH "Default")

set( mcal_dir "${SW_DIR}/bsw/static/mcal" CACHE PATH "Default")

# MCAL Software Components
set( can_swc  "${SW_DIR}/bsw/static/mcal/can_swc" CACHE PATH "Default")

# App Software Components
set( app_swc  "${SW_DIR}/swc/app_swc" CACHE PATH "Default")
