message(STATUS "WARNING_AS_ERROR = ${WARNING_AS_ERROR}")
message(STATUS "SW_DIR = ${SW_DIR}")

set( CMAKE_INSTALL_PREFIX "./" CACHE PATH "Default install path")

# MCAL Software Components
set( MCAL_Can  "${SW_DIR}/bsw/static/Mcal/CAN" CACHE PATH "Default")
