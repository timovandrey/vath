cmake_minimum_required(VERSION 3.8)

set(This VathTests)

set(TestSources
    VathTests.cpp
)

add_executable(${This} ${TestSources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Vath
)

add_test(
    NAME ${This}
    COMMAND ${This}
)