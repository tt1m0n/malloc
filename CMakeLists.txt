cmake_minimum_required(VERSION 3.13)
project(malloc C)

set(CMAKE_C_STANDARD 99)

add_executable(malloc src/malloc.c main.c include/malloc.h src/zone_creation.c src/zone_operations.c src/block_operations.c src/helpers.c src/block_creation.c)
