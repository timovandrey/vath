cmake_minimum_required(VERSION 3.8)

set(This Vath)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

# set(CMAKE_INCLUDE_DIR
#     /spdlog/
# )

# include_directories(${CMAKE_INCLUDE_DIR})

set(Headers
    ./application/headers/monomial.hpp
    ./application/headers/polynomial.hpp
)

set(Sources
    ./application/main.cpp    
    ./application/sources/monomial.cpp
    ./application/sources/polynomial.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)

# target_include_directories(${This} PRIVATE ${CMAKE_SOURCE_DIR})

