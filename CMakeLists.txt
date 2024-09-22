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
