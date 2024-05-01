cmake_minimum_required(VERSION 3.14)

# building mcal
message( STATUS "Building MCAL")

add_subdirectory("${can_swc}")
add_subdirectory("${port_swc}")
add_subdirectory("${dio_swc}")
