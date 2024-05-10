# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(port_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "port_swc")

##############################################################################
# Extract Module Path in build/CMake/Test/                                   #
##############################################################################
extract_module_path(port_swc MOCK_FILE_PATH)

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
  # Execute CMock script
  execute_process(
    COMMAND ruby ${CMOCK_SCRIPT} -o${CMOCK_CONFIG_FILE} ${port_swc_mock_header_files}
    OUTPUT_VARIABLE CMOCK_OUTPUT
    WORKING_DIRECTORY ${MOCK_FILE_PATH}
  )
  message("CMock output: ${CMOCK_OUTPUT}")

  # Testing Mode: Build the library and test executable
  include(tools/cmake/port_swc_tests.cmake)
  add_executable(port_swc_test ${port_swc_tests_sources_list} ${unity_common_sources})
  target_compile_definitions(port_swc_test PRIVATE ${port_swc_tests_defines})
  target_compile_options(port_swc_test PRIVATE ${dio_swc_tests_compile_options})
  target_include_directories(port_swc_test PRIVATE ${port_swc_tests_includes} ${unity_common_includes})
  target_link_libraries(port_swc_test PRIVATE port_swc)
  # Until Integrate Gcovr 
  add_test(NAME port_swc_test COMMAND port_swc_test)
endif()
