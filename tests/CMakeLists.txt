cmake_minimum_required(VERSION 3.8)

set(This VathTests)

set(TestSources
    MonomialTests.cpp
    PolynomialTests.cpp
)

# set(CMAKE_INCLUDE_DIR
#     ../spdlog/
# )

#include_directories(${CMAKE_INCLUDE_DIR})

add_executable(${This} ${TestSources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Vath
)

include(GoogleTest)
gtest_discover_tests(${This})

add_test(
    NAME ${This}
    COMMAND ${This}
)

# target_include_directories(${This} PRIVATE ${CMAKE_SOURCE_DIR})

