cmake_minimum_required(VERSION 3.25)
project(MathEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(MathEngine ${SOURCES})

if (BUILD_SHARED_LIBS)
    target_compile_definitions(MathEngine PRIVATE DYNAMIC_LINK BUILD_DLL)
endif()

target_include_directories(MathEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
    googletest URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)
