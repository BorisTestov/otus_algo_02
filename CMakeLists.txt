cmake_minimum_required(VERSION 3.10)

project(homework_2)

if (CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "CMAKE_BUILD_TYPE not defined, 'Release' will be used")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# Set sources
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

# Add executables
add_executable(${PROJECT_NAME} ${SOURCES})