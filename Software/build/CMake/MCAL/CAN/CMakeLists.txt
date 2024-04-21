# CMake Version Check
cmake_minimum_required(VERSION 3.10)

# Project
project(MCAL_CAN 
        LANGUAGES C CXX
        VERSION "1.0.0"
        DESCRIPTION "Can Mcal Layer")

        
# Includes
set(
  MCAL_CAN_INCLUDES

  inc/can.h
)

# Sources List
set(
    MCAL_CAN_SOURCES_LIST

    src/Can.c
)

# Compilation Options
set(
    MCAL_CAN_DEFINES
)

# C Defninitions
set(
    MCAL_CAN_DEFINES
)

add_library( MCAL_CAN  ${MCAL_CAN_SOURCES_LIST} )
target_compile_options( MCAL_CAN PRIVATE ${MCAL_CAN_COMPILE_OPTIONS} )
target_compile_definitions( MCAL_CAN PRIVATE ${MCAL_CAN_DEFINES})
target_include_directories( MCAL_CAN PRIVATE ${MCAL_CAN_INCLUDES})
target_link_libraries(MCAL_CAN PRIVATE "MCAL_CAN")
