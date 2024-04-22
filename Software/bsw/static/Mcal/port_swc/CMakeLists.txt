# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(port_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "port_swc")


# Sources
include( tools/cmake/port_swc_sources.cmake )
add_library( port_swc  ${port_swc_sources_list} )

# Compilation Options
include( tools/cmake/port_swc_compile_options.cmake )
target_compile_options( port_swc PRIVATE ${port_swc_compile_options})

# C Defninitions
include( tools/cmake/port_swc_defines.cmake )
target_compile_definitions( port_swc PRIVATE ${port_swc_defines})

# Includes
include( tools/cmake/port_swc_includes.cmake )
target_include_directories( port_swc PRIVATE ${port_swc_includes})