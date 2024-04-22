cmake_minimum_required(VERSION 3.14)

project(autosarz)

message( STATUS "Building MCAL Components")
add_subdirectory("${can_swc}")
add_subdirectory("${port_swc}")
add_subdirectory("${dio_swc}")
