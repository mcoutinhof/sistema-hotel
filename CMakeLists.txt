cmake_minimum_required(VERSION 3.16.3)
project(sistema-hotel C)

set(CMAKE_C_STANDARD 11)

add_executable(sistema-hotel
        main.c
        lcurses.c
        model/database.c model/database_bin.c model/database_xml.c model/tables.c
        view/telas.c view/utils.c
)

# Se precisar usar funções da math.h
# target_link_libraries(sistema-hotel m)