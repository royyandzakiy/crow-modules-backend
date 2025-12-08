cmake_minimum_required(VERSION 3.28..3.31)

# =============================================================================
# Compiler Configuration
# =============================================================================
cmake_policy(SET CMP0091 NEW)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# =============================================================================
# Conan Pre-configure
# =============================================================================
include(cmake/conan-preconfigure.cmake)

# =============================================================================
# Project Configuration
# =============================================================================
project(crow-modules-backend 
    LANGUAGES CXX
    VERSION 1.0.0
)

if(MSVC)
    add_compile_options(/W4 /permissive-)
    # add_compile_options(/WX) # more strict
else()
    # Clang/GCC
    add_compile_options(-Wall -Wextra)
    # add_compile_options(-Werror -pedantic) # more strict
endif()

# =============================================================================
# Dependencies
# =============================================================================
find_package(Crow REQUIRED)
find_package(SQLiteCpp REQUIRED)

# =============================================================================
# Main Executable
# =============================================================================
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/globals.cpp
    src/models/user.cpp
    src/models/post.cpp
    src/routes/user_routes.cpp
    src/routes/post_routes.cpp
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		Crow::Crow
		SQLiteCpp
)
# target_link_libraries(${PROJECT_NAME} PRIVATE asio::asio)