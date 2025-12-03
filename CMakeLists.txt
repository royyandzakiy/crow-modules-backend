# =============================================================================
# Project Configuration
# =============================================================================
cmake_minimum_required(VERSION 3.28)

project(cmake_project_template 
    LANGUAGES CXX
    VERSION 1.0.0
)

# =============================================================================
# Platform Configuration
# =============================================================================

# =============================================================================
# Compiler Configuration
# =============================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#==============================================================================
# Toolchain Configuration
#==============================================================================
if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "generators\\conan_toolchain.cmake")
endif()

if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using Conan toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# =============================================================================
# Dependencies
# =============================================================================
find_package(fmt REQUIRED)

# =============================================================================
# Main Executable
# =============================================================================
add_executable(${PROJECT_NAME} 
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)