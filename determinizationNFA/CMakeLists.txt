cmake_minimum_required(VERSION 3.17)
project(formal_languages)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

add_library(NFA SHARED NFA.cpp NFA.h)

find_package(GTest)

IF(GTest_FOUND)
    add_executable(tests test.cpp mainTest.cpp)
    target_link_libraries(tests NFA ${GTEST_LIBRARIES} Threads::Threads)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_dependencies(tests NFA)
ENDIF()


add_executable(NFA_determinization main.cpp)
target_link_libraries(NFA_determinization NFA)

add_dependencies(NFA_determinization NFA)
