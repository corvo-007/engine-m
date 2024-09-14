cmake_minimum_required(VERSION 3.25)
project(MathEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(MathEngine STATIC ${SOURCES})

target_include_directories(MathEngine PUBLIC ${CMAKE_SOURCE_DIR}/include)