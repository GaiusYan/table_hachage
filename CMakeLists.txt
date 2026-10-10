cmake_minimum_required(VERSION 4.3)
project(TP2___Tables_de_hachage C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TP2___Tables_de_hachage
        ensemble.h
        liste.c
        liste.h
        liste_chainee.h
        main.c)
