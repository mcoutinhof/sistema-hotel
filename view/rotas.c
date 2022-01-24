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
        switch (menu($f, 5, "Cadastros", "Entrada de produtos", "Reservas", "Vendas", "Relatórios", "Sair")) {
            case 0:
                menu_cadastros();
                break;
            case 1:
                menu_entradas();
                break;
            case 2:
                menu_reservas();
                break;
            case 3:
                menu_vendas();
                break;
            case 4:
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
                break;
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

int menu_vendas() {
    while (1) {
        clrscr();
        switch (menu($f, 3, "Realizar venda", "Ver venda", "Voltar")) {
            case 0:
                realizar_venda();
                break;
            case 1:
                //ver_venda();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_entradas() {
    while (1) {
        clrscr();
        switch (menu($f, 3, "Realizar entrada", "Baixa de notas", "Voltar")) {
            case 0:
                realizar_entrada();
                break;
            case 1:
                baixar_nota();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_relatorios() {
    while (1) {
        clrscr();
        switch (menu($f, 8, "Hóspedes", "Acomodações", "Movimentação de acomodações", "Reservas", "Produtos", "Caixas", "Contas a pagar", "Voltar")) {
            case 0:
                relatorio_hospedes();
                break;
            case 1:
                relatorio_acomodacoes();
                break;
            case 2:
                relatorio_movimentacao_acomodacoes();
                break;
            case 3:
                relatorio_reservas();
                break;
            case 4:
                relatorio_produtos();
                break;
            case 5:
                relatorio_caixas();
                break;
            case 6:
                relatorio_contas_pagar();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}