cmake_minimum_required (VERSION 2.6)
project (Chess)
include(sourcelist)
add_executable(chess ${sources})
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(chess ${Boost_LIBRARIES})
SET_TARGET_PROPERTIES(chess
                               PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra\
                                            -g -std=c++17 -pedantic")
set(CMAKE_CXX_STANDARD_LIBRARIES -ldl)
