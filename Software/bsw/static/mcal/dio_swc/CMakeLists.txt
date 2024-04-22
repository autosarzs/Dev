# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(dio_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "dio_swc")

##############################################################################
# Include Common Compilation Settings                                       #
##############################################################################

include(tools/cmake/dio_swc_compile.cmake)

##############################################################################
# Build Configuration                                                        #
##############################################################################

# Compilation Mode: Only build the library

if(MODE STREQUAL "COMPILING")
  add_library(dio_swc ${dio_swc_sources_list})
  target_compile_options(dio_swc PRIVATE ${dio_swc_compile_options})
  target_include_directories(dio_swc PRIVATE ${dio_swc_includes})
  target_compile_definitions(dio_swc PRIVATE ${dio_swc_defines})
elseif (MODE STREQUAL "TESTING")
  include(tools/cmake/dio_swc_tests.cmake)
  add_library(dio_swc ${dio_swc_ut_sources_list})
  target_compile_options(dio_swc PRIVATE ${dio_swc_tests_compile_options})
  target_include_directories(dio_swc PRIVATE ${dio_swc_tests_includes})
  target_compile_definitions(dio_swc PRIVATE ${dio_swc_tests_defines})
endif()


if(MODE STREQUAL "TESTING")
  # Testing Mode: Build the library and test executable
  add_executable(dio_swc_test ${dio_swc_tests_sources_list})
  target_compile_definitions(dio_swc_test PRIVATE ${dio_swc_tests_defines})
  target_compile_options(dio_swc_test PRIVATE ${dio_swc_tests_compile_options})
  target_include_directories(dio_swc_test PRIVATE ${dio_swc_tests_includes})
  target_link_libraries(dio_swc_test PRIVATE ${dio_swc_tests_libs})
  add_test(NAME dio_swc_test COMMAND dio_swc_test)
endif()
