set(
    can_swc_tests_sources_list

    ${can_swc}/tests/unit/test_can_swc.c
    # /workspace/software/bsw/mcal/can_swc/
    ${MOCK_FILE_PATH}/mocks/mock_Det.c
    ${MOCK_FILE_PATH}/mocks/mock_stub.c
    ${MOCK_FILE_PATH}/mocks/mock_can_lib.c
    ${MOCK_FILE_PATH}/mocks/mock_test_can_swc_stubs.c
    # Include Test Runners 
    ${can_swc}/tests/unit/test_runners/can_Runner.c
    ${can_swc}/tests/unit/test_runners/all_tests.c
)

set(
    can_swc_ut_sources_list

    ${can_swc}/core/Can.c
    ${gendata}/Can_PBcfg.c
)

set (
    can_swc_mock_header_files
    
    ${stubs}/Det.h
    ${can_swc}/tests/unit/stubs/stub.h
    ${platform}/can_lib.h
    ${can_swc}/tests/unit/stubs/test_can_swc_stubs.h
)

# Create a list of all files in ${platform}/inc
file(GLOB PLATFORM_INCLUDES "${platform}/*.h")

# Create a temporary directory to store the filtered header files
set(filtered_platform_includes "${CMAKE_CURRENT_BINARY_DIR}/filtered_include")

# Create the temporary directory
file(MAKE_DIRECTORY ${filtered_platform_includes})

# Iterate over each file in the list
foreach(file ${PLATFORM_INCLUDES})
    # Get the file name
    get_filename_component(filename ${file} NAME)

    # Check if the file is not cmsis_gcc.h
    if(NOT filename MATCHES "cmsis_gcc\\.h$")
        # Copy the file to the temporary directory
        file(COPY ${file} DESTINATION ${filtered_platform_includes})
    endif()
endforeach()

set(
    can_swc_tests_includes

    ${can_swc}/core
    ${can_swc}/tests/unit/stubs
    ${MOCK_FILE_PATH}/mocks
    ${gendata}

    ${common_includes}
    ${filtered_platform_includes} 
    ${stubs}

)
set(
    can_swc_tests_compile_options
)

set(
    can_swc_tests_defines
)
