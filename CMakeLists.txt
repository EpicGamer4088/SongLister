cmake_minimum_required(VERSION 3.26.4)
project(SongLister C)

set(CMAKE_C_STANDARD 11)

add_executable(
        SongLister
        main.c
        songs.c
        songs.h
        )

target_link_libraries(SongLister shlwapi)
target_link_libraries(SongLister winmm)
