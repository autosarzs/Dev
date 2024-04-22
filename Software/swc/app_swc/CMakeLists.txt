# CMake Version Check
cmake_minimum_required(VERSION 3.14)

# Project
project(app_swc 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "app_swc")


# Sources
include( tools/cmake/app_swc_sources.cmake )
add_executable( app_swc  ${app_swc_sources_list} )

# Compilation Options
include( tools/cmake/app_swc_compile_options.cmake )
target_compile_options( app_swc PRIVATE ${app_swc_compile_options})

# C Defninitions
include( tools/cmake/app_swc_defines.cmake )
target_compile_definitions( app_swc PRIVATE ${app_swc_defines})

# Includes
include( tools/cmake/app_swc_includes.cmake )
target_include_directories( app_swc PRIVATE ${app_swc_includes})

# Libraries
include(tools/cmake/app_swc_libs.cmake)
target_link_libraries(app_swc PRIVATE ${app_swc_libs})


install( PROGRAMS $<TARGET_FILE:app_swc>  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ DESTINATION ${CMAKE_BINARY_DIR}/../output/build RENAME autosar_app.out)
install( FILES    $<TARGET_FILE:app_swc>.map DESTINATION ${CMAKE_BINARY_DIR}/../output/build RENAME autosar_app.map  )

