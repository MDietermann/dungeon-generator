cmake_minimum_required(VERSION 4.1)
project(dungeon_generator C)

set(CMAKE_C_STANDARD 11)

add_library(dungengenerator STATIC
        src/constants.c
        src/helper.c
        src/map.c
        src/room.c
        include/dungeon_generator.h.c)

target_include_directories(dungengenerator PUBLIC include)
target_link_libraries(dungengenerator PUBLIC raylib m)

# Test executable
add_executable(dungeon_generator_test src/dungeon_generator.c)
target_link_libraries(dungeon_generator_test dungengenerator)
