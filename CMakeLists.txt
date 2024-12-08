cmake_minimum_required(VERSION 3.25)
project(EngineM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(EngineM_build_tests "Build test files" ON)

add_compile_options(-mavx2)

add_library(EngineM ${SOURCES})

if (BUILD_SHARED_LIBS)
    target_compile_definitions(EngineM PRIVATE DYNAMIC_LINK BUILD_DLL)
endif()

target_include_directories(EngineM PRIVATE ${EngineM_SOURCE_DIR}/include)

if (EngineM_build_tests)
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
endif()
