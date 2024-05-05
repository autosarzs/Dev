message(STATUS "SW_DIR = ${SW_DIR}")
message(STATUS "BUILD_TESTS_DIR = ${BUILD_TESTS_DIR}")

set( CMAKE_INSTALL_PREFIX "./" CACHE PATH "Default install path")

##############################################################################
# Common Directories                                                         #
##############################################################################
set( common_includes "${SW_DIR}/common/includes" CACHE PATH "Default")
set( platform "${SW_DIR}/common/platform" CACHE PATH "Default")
set( stubs "${SW_DIR}/common/stubs" CACHE PATH "Default")

set( application_dir "${SW_DIR}/application" CACHE PATH "Default")
set( bsw_dir "${SW_DIR}/bsw" CACHE PATH "Default")
set( mcal_dir "${SW_DIR}/bsw/mcal" CACHE PATH "Default")

set( gendata "${SW_DIR}/gendata" CACHE PATH "Default")

##############################################################################
# MCAL Software Components                                                   #
##############################################################################
set( can_swc  "${SW_DIR}/bsw/mcal/can_swc" CACHE PATH "Default")
set( port_swc  "${SW_DIR}/bsw/mcal/port_swc" CACHE PATH "Default")
set( dio_swc  "${SW_DIR}/bsw/mcal/dio_swc" CACHE PATH "Default")

##############################################################################
# App Software Components                                                    #
############################################################################## 
set( app_swc  "${SW_DIR}/application/app_swc" CACHE PATH "Default")

##############################################################################
# Frameworks                                                                 #
############################################################################## 

set( CMOCK_ROOT_DIR  "/workspace/tools/frameworks/CMock" CACHE PATH "Default")
set( UNITY_ROOT_DIR  "${CMOCK_ROOT_DIR}/vendor/unity" CACHE PATH "Default")

set(CMOCK_SCRIPT "${CMOCK_ROOT_DIR}/lib/cmock.rb")
set(CMOCK_CONFIG_FILE "/workspace/tools/build/CMake/cmockConfig.yml")

##############################################################################
# Dependencies                                                               #
##############################################################################
set(
    unity_common_sources

    ${UNITY_ROOT_DIR}/src/unity.c
    ${UNITY_ROOT_DIR}/extras/fixture/src/unity_fixture.c
    ${CMOCK_ROOT_DIR}/src/cmock.c
)
set(
    unity_common_includes

    ${CMOCK_ROOT_DIR}/src
    ${UNITY_ROOT_DIR}/src
    ${UNITY_ROOT_DIR}/extras/fixture/src
    ${UNITY_ROOT_DIR}/extras/memory/src/
)
##############################################################################
# Functions                                                                 #
##############################################################################
function(extract_module_path source_var_name dest_var_name)
    # Extract the desired path
    string(REGEX REPLACE "^/workspace" "" MODULE_PATH "${${source_var_name}}")

    # Concatenate with BUILD_TESTS_DIR
    set(${dest_var_name} "${BUILD_TESTS_DIR}${MODULE_PATH}" PARENT_SCOPE)
endfunction()