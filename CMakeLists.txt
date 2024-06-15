cmake_minimum_required(VERSION 3.27)
project(T3_Deividi_Lab_II C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(T3_Deividi_Lab_II
        main.c
        telag.c
        telag_exemplo.c
        arvore.c
        arvore.h)
