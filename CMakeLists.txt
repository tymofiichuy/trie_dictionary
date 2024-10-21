cmake_minimum_required(VERSION 3.5)
project(trie_dictionary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${SOURCE_DIR})

# ADD_SUBDIRECTORY(googletest-release-1.10.0)
# enable_testing()
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# add_executable(runUnitTests ${TEST_DIR}/unit_test.cpp ${SOURCE_DIR}/graph.cpp ${SOURCE_DIR}/random_graph.cpp)
# target_link_libraries(runUnitTests gtest gtest_main)
# add_test(runUnitTests runUnitTests)