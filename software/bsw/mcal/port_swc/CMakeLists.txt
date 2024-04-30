# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(port_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "port_swc")

##############################################################################
# Include Common Compilation Settings                                       #
##############################################################################

include(tools/cmake/port_swc_compile.cmake)

##############################################################################
# Build Configuration                                                        #
##############################################################################

# Compilation Mode: Only build the library

if(MODE STREQUAL "COMPILING")
  add_library(port_swc ${port_swc_sources_list})
  target_compile_options(port_swc PRIVATE ${port_swc_compile_options})
  target_include_directories(port_swc PRIVATE ${port_swc_includes})
  target_compile_definitions(port_swc PRIVATE ${port_swc_defines})
elseif (MODE STREQUAL "TESTING")
  include(tools/cmake/port_swc_tests.cmake)
  add_library(port_swc ${port_swc_ut_sources_list})
  target_compile_options(port_swc PRIVATE ${port_swc_tests_compile_options})
  target_include_directories(port_swc PRIVATE ${port_swc_tests_includes})
  target_compile_definitions(port_swc PRIVATE ${port_swc_tests_defines})
endif()

if(MODE STREQUAL "TESTING")
  # Testing Mode: Build the library and test executable
  include(tools/cmake/port_swc_tests.cmake)
  add_executable(port_swc_test ${port_swc_tests_sources_list})
  target_compile_definitions(port_swc_test PRIVATE ${port_swc_tests_defines})
  target_include_directories(port_swc_test PRIVATE ${port_swc_tests_includes})
  target_link_libraries(port_swc_test PRIVATE port_swc)
  add_test(NAME port_swc_test COMMAND port_swc_test)
endif()
