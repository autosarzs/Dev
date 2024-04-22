# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(dio_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "dio_swc")

##############################################################################
# Component Compilation                                                      #
##############################################################################

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

##############################################################################
# Component Testing                                                          #
##############################################################################

# Tests
# Add the test to CTest
include( tools/cmake/dio_swc_tests.cmake )

# Add test executable
add_executable(dio_swc_test ${dio_swc_tests_sources_list})

# Compilation Options
target_compile_options( dio_swc_test PRIVATE ${dio_swc_tests_compile_options})

# C Defninitions
target_compile_definitions( dio_swc_test PRIVATE ${dio_swc_tests_defines})

# Add test includes
target_include_directories(dio_swc_test PRIVATE ${dio_swc_tests_includes})

# Link with libraries
target_link_libraries(dio_swc_test PRIVATE dio_swc)

# Register Tests
add_test(NAME dio_swc_test COMMAND dio_swc_test)
