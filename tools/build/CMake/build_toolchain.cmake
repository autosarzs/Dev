set(COMMON_FLAGS "-mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 -DPART_TM4C123GH6PZ -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall")

set(CMAKE_C_FLAGS          "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS        "${COMMON_FLAGS}")

set(CMAKE_C_COMPILER       ${TOOLCHAIN_DIR}/bin/arm-eabi-gcc)
set(CMAKE_CXX_COMPILER     ${TOOLCHAIN_DIR}/bin/arm-eabi-gcc)
set(CMAKE_AR               ${TOOLCHAIN_DIR}/bin/arm-eabi-ar)

set(CMAKE_EXE_LINKER_FLAGS "-specs=nosys.specs -mthumb -Wl,-Map,app_swc.map -Wl,--build-id=none")

set(CMAKE_C_CREATE_STATIC_LIBRARY "<CMAKE_AR> -crs <TARGET> <LINK_FLAGS> <OBJECTS>")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
