cmake_minimum_required(VERSION 3.10)

project(autosarz)

include(CTest)

include("${CMAKE_PROJECT_DIR}/user.cmake")

add_subdirectory("${mcal_dir}")
add_subdirectory("${app_swc}")
