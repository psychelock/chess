cmake_minimum_required (VERSION 2.6)
project (Chess)
include(sourcelist)
add_executable(chess ${sources} src/main.cc)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
find_package (Threads)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(chess ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
SET_TARGET_PROPERTIES(chess
                               PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra\
                               -g -std=c++17 -pedantic")
set (CMAKE_EXE_LINKER_FLAGS "-lpthread -ldl")

enable_testing()
add_subdirectory( build/googletest )

# this sets the output dir to /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

include_directories(${CMAKE_SOURCE_DIR}/build/googletest/googletest/include)
add_executable(mytest ${sources} src/tests/test.cc)
target_link_libraries(mytest gtest_main gtest)
SET_TARGET_PROPERTIES(mytest
                               PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra\
                               -g -std=c++17 -pedantic ")
