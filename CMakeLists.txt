cmake_minimum_required(VERSION 3.20)
project(sistema-hotel C)

set(CMAKE_C_STANDARD 11)

add_executable(sistema-hotel main.c
        lcurses.c
        model/database.c model/database_bin.c model/database_xml.c model/tables.c
        view/telas.c view/utils.c)
target_link_libraries(sistema-hotel m)