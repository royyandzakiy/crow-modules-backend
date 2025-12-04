# cmake/conan-preconfigure.cmake
# Minimal Conan pre-configure script

# Find Conan
find_program(CONAN_PATH conan REQUIRED)

# Determine build type (default to Release if not specified)
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CONAN_BUILD_TYPE "Release")
else()
    set(CONAN_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
endif()

# Run Conan install
message(STATUS "Running Conan install for Clang 20 (${CONAN_BUILD_TYPE})...")
execute_process(
    COMMAND ${CONAN_PATH} install . 
            -of ${CMAKE_BINARY_DIR}
            --build=missing
            -s compiler=clang
            -s compiler.version=20
            -s compiler.runtime_type=${CONAN_BUILD_TYPE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE CONAN_RESULT
)

if(NOT CONAN_RESULT EQUAL 0)
    message(FATAL_ERROR "Conan install failed with exit code: ${CONAN_RESULT}")
endif()

# Include the generated toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/conan_toolchain.cmake" CACHE FILEPATH "Conan toolchain")