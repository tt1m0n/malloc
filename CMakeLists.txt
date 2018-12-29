cmake_minimum_required(VERSION 3.12)
project(malloc C)

set(CMAKE_C_STANDARD 99)

add_executable(malloc src/malloc.c
        main.c
        include/malloc.h
        src/zone_creation.c
        src/zone_operations.c
        src/block_operations.c
        src/helpers.c
        src/block_creation.c
        src/realloc.c
        src/free.c
        src/zone_release.c
        src/ft_putchar.c
        src/ft_bzero.c
        src/ft_memset.c
        src/ft_putnbr.c
        src/ft_putstr.c src/show_alloc_mem.c)
