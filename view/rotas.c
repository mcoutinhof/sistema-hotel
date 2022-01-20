/**
 * @authors Ryan W. Fonseca & Arthur Gomes.
 */

#include "rotas.h"
#include "utils.h"
#include "../lcurses.h"
#include "../model/tables.h"
#include <stdlib.h>

int menu_principal() {
    while (1) {
        clrscr();
        switch (menu($f, 5, "Cadastros", "Gestão de Estoque", "Reservas", "Relatórios", "Sair")) {
            case 0:
                menu_cadastros();
                break;
            case 1:
                // menu_produtos();
                break;
            case 2:
                menu_reservas();
                break;
            case 3:
                menu_relatorios();
                break;
            default: // Sair
                return EXIT_SUCCESS;
        }
    }
}

int menu_cadastros() {
    while (1) {
        clrscr();
        switch (menu($f, 3, "Inserir", "Ver", "Voltar")) {
            case 0:
                menu_inserir();
                break;
            case 1:
                menu_ver();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

static inline int entidades() {
    return menu($f, 8, "Hóspedes", "Hotel", "Categorias de acomodações", "Operadores", "Acomodações", "Produtos", "Fornecedores", "Voltar");
}

int menu_ver() {
    while (1) {
        clrscr();
        switch (entidades()) {
            case 0:
                ver_hospede();
                break;
            case 1:
                ver_hotel();
                break;
            case 2:
                ver_categoria();
                break;
            case 3:
                ver_operador();
                break;
            case 4:
                ver_acomodacao();
                break;
            case 5:
                ver_produto();
                break;
            case 6:
                ver_fornecedor();
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_inserir() {
    while (1) {
        clrscr();
        switch (entidades()) {
            case 0:
                cadastrar_hospede();
                break;
            case 1:
                cadastrar_hotel();
                break;
            case 2:
                cadastrar_categoria();
                break;
            case 3:
                cadastrar_operador();
                break;
            case 4:
                cadastrar_acomodacao();
                break;
            case 5:
                cadastrar_produto();
                break;
            case 6:
                cadastrar_fornecedor();
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_reservas() {
    while (1) {
        clrscr();
        switch (menu($f, 4, "Verificar reserva", "Inserir reserva", "Ver reserva", "Voltar")) {
            case 0:
                // verificar_reserva();
                break;
            case 1:
                cadastrar_reserva();
                break;
            case 2:
                ver_reserva();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_relatorios() {
    while (1) {
        clrscr();
        switch (menu($f, 4, "Hóspedes", "Acomodações", "Reservas", "Voltar")) {
            case 0:
                relatorio_hospede();
                break;
            case 1:
                relatorio_acomodacoes();
                break;
            case 2:
                relatorio_reservas();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}