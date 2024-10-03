cmake_minimum_required(VERSION 3.8)

set(This VathTests)

set(TestSources
    MonomialTests.cpp
    PolynomialTests.cpp
)

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

