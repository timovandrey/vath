cmake_minimum_required(VERSION 3.8)

set(This Vath)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    ./application/headers/firsttest.hpp
)

set(Sources
    ./application/Sources/firsttest.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)