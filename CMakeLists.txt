cmake_minimum_required(VERSION 3.16.3)
project(sistema-hotel C)

set(CMAKE_C_STANDARD 11)

add_executable(
        sistema-hotel
        main.c
        lcurses.c
        model/database.c
        model/database_bin.c
        model/database_xml.c
        model/tables.c
        view/rotas.c
        view/utils.c
        controller/acomodacao.c
        controller/categoria.c
        controller/fornecedor.c
        controller/hospede.c
        controller/hotel.c
        controller/operador.c
        controller/produto.c
        controller/reserva.c
        controller/venda.c
        controller/entrada.c
        controller/caixa.c
        controller/contaPagar.c
        controller/contaReceber.c
)

# Se precisar usar funções da math.h
# target_link_libraries(sistema-hotel m)