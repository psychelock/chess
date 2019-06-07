cmake_minimum_required (VERSION 2.6)
project (Chess)
include(sourcelist)
add_executable(engine-mithun ${sources} src/main.cc)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
find_package (Threads)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(engine-mithun ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
SET_TARGET_PROPERTIES(engine-mithun
                               PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra\
                               -g -std=c++17 -pedantic")
set (CMAKE_EXE_LINKER_FLAGS "-lpthread -ldl -lgtest -lgtest_main")

add_executable(test ${sources} src/tests/test.cc)
SET_TARGET_PROPERTIES(test
                               PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra\
                               -g -std=c++17 -pedantic ")
