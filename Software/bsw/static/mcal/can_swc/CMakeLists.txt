# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(can_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "can_swc")


# Sources
include( tools/cmake/can_swc_sources.cmake )
add_library( can_swc  ${can_swc_sources_list} )

# Compilation Options
include( tools/cmake/can_swc_compile_options.cmake )
target_compile_options( can_swc PRIVATE ${can_swc_compile_options})

# C Defninitions
include( tools/cmake/can_swc_defines.cmake )
target_compile_definitions( can_swc PRIVATE ${can_swc_defines})

# Includes
include( tools/cmake/can_swc_includes.cmake )
target_include_directories( can_swc PRIVATE ${can_swc_includes})