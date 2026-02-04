cmake_minimum_required(VERSION 3.25)
project(EngineM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(EngineM_build_tests "Build test files" ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(EngineM ${SOURCES})

if (MSVC)
    set_source_files_properties(src/kernels/avx/matrix_kernels.cpp PROPERTIES COMPILE_FLAGS "/arch:AVX")
    set_source_files_properties(src/kernels/avx2/matrix_kernels.cpp PROPERTIES COMPILE_FLAGS "/arch:AVX2")
else()
    set_source_files_properties(src/kernels/avx/matrix_kernels.cpp PROPERTIES COMPILE_FLAGS "-mavx")
    set_source_files_properties(src/kernels/avx2/matrix_kernels.cpp PROPERTIES COMPILE_FLAGS "-mavx2")
endif()

if (BUILD_SHARED_LIBS)
    target_compile_definitions(EngineM PRIVATE DYNAMIC_LINK BUILD_DLL)
endif()

target_include_directories(EngineM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
