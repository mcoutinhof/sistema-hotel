/**
 * @authors Ryan W. Fonseca
 */

#include "rotas.h"
#include "utils.h"
#include "../lcurses.h"
#include <stdlib.h>

int menu_principal() {
    while (1) {
        clrscr();
        switch (menu($f, 8, "Cadastros", "Reservas", "Check-in", "Check-out", "Vendas", "Entrada de produtos",
                     "Relatórios", "Sair")) {
            case 0:
                menu_cadastros();
                break;
            case 1:
                menu_reservas();
                break;
            case 2:
                check_in_out(0);
                break;
            case 3:
                check_in_out(1);
                break;
            case 4:
                menu_vendas();
                break;
            case 5:
                menu_entradas();
                break;
            case 6:
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
    return menu($f, 8, "Hóspedes", "Hotel", "Categorias de acomodações", "Operadores", "Acomodações", "Produtos",
                "Fornecedores", "Voltar");
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
                break;
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
        switch (menu($f, 3, "Inserir reserva", "Ver reserva", "Voltar")) {
            case 0:
                cadastrar_reserva();
                break;
            case 1:
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
        switch (menu($f, 4, "Realizar venda", "Baixa de notas", "Ver venda", "Voltar")) {
            case 0:
                realizar_venda();
                break;
            case 1:
                baixar_nota_venda();
                break;
            case 2:
                ver_venda();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_entradas() {
    while (1) {
        clrscr();
        switch (menu($f, 4, "Realizar entrada", "Baixa de notas", "Ver entrada", "Voltar")) {
            case 0:
                realizar_entrada();
                break;
            case 1:
                baixar_nota_entrada();
                break;
            case 2:
                ver_entrada();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int menu_relatorios() {
    while (1) {
        clrscr();
        printf($a "Onde deseja imprimir os dados? \n");
        char path[256] = {};
        int option = menu($f, 3, "Em tela", "Em arquivo", "Voltar");
        if (option == 1) {
            clrscr();
            printf($a "Caminho do arquivo: " $f);
            readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 256}, &path);
        } else if (option == 2) return 1;
        clrscr();

        switch (menu($f, 10, "Hóspedes", "Acomodações", "Movimentação de acomodações", "Reservas", "Produtos", "Vendas",
                     "Movimentação de caixa", "Contas a pagar", "Contas a receber", "Voltar")) {
            case 0:
                relatorio_hospedes(path);
                break;
            case 1:
                relatorio_acomodacoes(path);
                break;
            case 2:
                relatorio_movimentacao_acomodacoes(path);
                break;
            case 3:
                relatorio_reservas(path);
                break;
            case 4:
                relatorio_produtos(path);
                break;
            case 5:
                relatorio_vendas(path);
                break;
            case 6:
                relatorio_caixas(path);
                break;
            case 7:
                relatorio_contas_pagar(path);
                break;
            case 8:
                relatorio_contas_receber(path);
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}