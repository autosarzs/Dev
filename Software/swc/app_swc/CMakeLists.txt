# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(app_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "app_swc")


##############################################################################
# Include Common Compilation Settings                                       #
##############################################################################

include(tools/cmake/app_swc_compile.cmake)

##############################################################################
# Build Configuration                                                        #
##############################################################################

# Compilation Mode: Only build the library

if(MODE STREQUAL "COMPILING")
  add_executable(app_swc ${app_swc_sources_list})
  target_compile_options(app_swc PRIVATE ${app_swc_compile_options})
  target_include_directories(app_swc PRIVATE ${app_swc_includes})
  target_compile_definitions(app_swc PRIVATE ${app_swc_defines})
  target_link_libraries(app_swc PRIVATE ${app_swc_libs})

  # Installation
  install( PROGRAMS $<TARGET_FILE:app_swc>  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ DESTINATION ${CMAKE_BINARY_DIR}/../output/build RENAME autosar_app.out)
  install( FILES    $<TARGET_FILE:app_swc>.map DESTINATION ${CMAKE_BINARY_DIR}/../output/build RENAME autosar_app.map  )

elseif (MODE STREQUAL "TESTING")
  include(tools/cmake/app_swc_tests.cmake)
  add_executable(app_swc_test ${app_swc_tests_sources_list})
endif()

