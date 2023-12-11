cmake_minimum_required(VERSION 3.25)
project(Satellite_Categorizer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Satellite_Categorizer
        controller.c
        controller.h
        displayer.c
        displayer.h
        hashmap.c
        hashmap.h
        list.c
        list.h
        main.c
        structs.c
        structs.h
        vector.c
        vector.h)
