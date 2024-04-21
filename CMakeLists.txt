cmake_minimum_required(VERSION 3.10)

project(autosarz)

include("${CMAKE_PROJECT_DIR}/user.cmake")

message( STATUS "Building MCAL Layer")
add_subdirectory("${mcal_dir}")


message( STATUS "Building App Component")
add_subdirectory("${app_swc}")
