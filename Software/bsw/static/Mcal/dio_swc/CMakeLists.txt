# CMake Version Check
cmake_minimum_required(VERSION 3.10)

# Project
project(dio_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "dio_swc")


# Sources
include( tools/cmake/dio_swc_sources.cmake )
add_library( dio_swc  ${dio_swc_sources_list} )

# Compilation Options
include( tools/cmake/dio_swc_compile_options.cmake )
target_compile_options( dio_swc PRIVATE ${dio_swc_compile_options})

# C Defninitions
include( tools/cmake/dio_swc_defines.cmake )
target_compile_definitions( dio_swc PRIVATE ${dio_swc_defines})

# Includes
include( tools/cmake/dio_swc_includes.cmake )
target_include_directories( dio_swc PRIVATE ${dio_swc_includes})