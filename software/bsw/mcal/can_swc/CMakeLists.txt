# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(can_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "can_swc")

##############################################################################
# Include Common Compilation Settings                                       #
##############################################################################

include(tools/cmake/can_swc_compile.cmake)

##############################################################################
# Build Configuration                                                        #
##############################################################################

# Compilation Mode: Only build the library

# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(can_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "can_swc")

##############################################################################
# Include Common Compilation Settings                                       #
##############################################################################

include(tools/cmake/can_swc_compile.cmake)

##############################################################################
# Build Configuration                                                        #
##############################################################################

# Compilation Mode: Only build the library


if(MODE STREQUAL "COMPILING")
  add_library(can_swc ${can_swc_sources_list})
  target_compile_options(can_swc PRIVATE ${can_swc_compile_options})
  target_include_directories(can_swc PRIVATE ${can_swc_includes})
  target_compile_definitions(can_swc PRIVATE ${can_swc_defines})
elseif (MODE STREQUAL "TESTING")
  include(tools/cmake/can_swc_tests.cmake)
  add_library(can_swc ${can_swc_ut_sources_list})
  target_compile_options(can_swc PRIVATE ${can_swc_tests_compile_options})
  target_include_directories(can_swc PRIVATE ${can_swc_tests_includes})
  target_compile_definitions(can_swc PRIVATE ${can_swc_tests_defines})
endif()


if(MODE STREQUAL "TESTING")
  # Execute CMock script
  execute_process(
    COMMAND ruby ${CMOCK_SCRIPT} -o${CMOCK_CONFIG_FILE} ${can_swc_mock_header_files}
    OUTPUT_VARIABLE CMOCK_OUTPUT
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
  )
  message("CMock output: ${CMOCK_OUTPUT}")

  # Testing Mode: Build the library and test executable
  add_executable(can_swc_test ${can_swc_tests_sources_list})
  target_compile_definitions(can_swc_test PRIVATE ${can_swc_tests_defines})
  target_compile_options(can_swc_test PRIVATE ${can_swc_tests_compile_options})
  target_include_directories(can_swc_test PRIVATE ${can_swc_tests_includes})
  target_link_libraries(can_swc_test PRIVATE can_swc)
endif()
