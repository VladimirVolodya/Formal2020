cmake_minimum_required(VERSION 3.17)
project(formal_languages)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

add_library(CDFA SHARED CDFA.cpp CDFA.h)

find_package(GTest)

IF(GTest_FOUND)
    add_executable(tests test.cpp mainTest.cpp)
    target_link_libraries(tests CDFA ${GTEST_LIBRARIES} Threads::Threads)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_dependencies(tests CDFA)
ENDIF()


add_executable(CDFA_minimization main.cpp)
target_link_libraries(CDFA_minimization CDFA)

add_dependencies(CDFA_minimization CDFA)