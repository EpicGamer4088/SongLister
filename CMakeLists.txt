cmake_minimum_required(VERSION 3.26.4)
project(Projekt2AHITNGr1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Projekt2AHITNGr1 main.c
        songs.c
        songs.h
        songs.h
        songs.c
        songs.h)

target_link_libraries(Projekt2AHITNGr1 shlwapi)