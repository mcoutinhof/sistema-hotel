/**
 * @authors Ryan W. Fonseca & Arthur Gomes.
 */

#include "telas.h"
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
                // menu_relatorios();
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

int cadastrar_hospede() {
    clrscr();

    struct Hospede hosp = {};
    form(0, Hospedes, &hosp); // Modo 0 = Inserir

    DATABASE->open(Hospedes);
    DATABASE->insert(Hospedes, &hosp);
    DATABASE->close(Hospedes);
    return EXIT_SUCCESS;
}

int ver_hospede() {
    DATABASE->open(Hospedes);
    DATABASE_forEach(struct Hospede, hosp, Hospedes) {
        clrscr();
        form(1, Hospedes, &hosp); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Hospedes, &hosp); // Modo 2 = Editar
                DATABASE->update(Hospedes, &hosp);
                break;
            case 2:
                DATABASE->delete(Hospedes);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Hospedes);
    return EXIT_SUCCESS;
}

int cadastrar_hotel() {
    clrscr();

    struct Hotel hotel = {};
    form(0, Hoteis, &hotel); // Modo 0 = Inserir

    DATABASE->open(Hoteis);
    DATABASE->insert(Hoteis, &hotel);
    DATABASE->close(Hoteis);
    return EXIT_SUCCESS;
}

int ver_hotel() {
    DATABASE->open(Hoteis);
    DATABASE_forEach(struct Hotel, hotel, Hoteis) {
        clrscr();
        form(1, Hoteis, &hotel); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Hoteis, &hotel); // Modo 2 = Editar
                DATABASE->update(Hoteis, &hotel);
                break;
            case 2:
                DATABASE->delete(Hoteis);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Hoteis);
    return EXIT_SUCCESS;
}

int cadastrar_categoria() {
    clrscr();

    struct Categoria categ = {};
    form(0, Categorias, &categ); // Modo 0 = Inserir

    DATABASE->open(Categorias);
    DATABASE->insert(Categorias, &categ);
    DATABASE->close(Categorias);
    return EXIT_SUCCESS;
}

int ver_categoria() {
    DATABASE->open(Categorias);
    DATABASE_forEach(struct Categoria, cat, Categorias) {
        clrscr();
        form(1, Categorias, &cat); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Categorias, &cat); // Modo 2 = Editar
                DATABASE->update(Categorias, &cat);
                break;
            case 2:
                DATABASE->delete(Categorias);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Categorias);
    return EXIT_SUCCESS;
}

int cadastrar_operador() {
    clrscr();

    struct Operador ope = {};
    form(0, Operadores, &ope); // Modo 0 = Inserir

    DATABASE->open(Operadores);
    DATABASE->insert(Operadores, &ope);
    DATABASE->close(Operadores);
    return EXIT_SUCCESS;
}

int ver_operador() {
    DATABASE->open(Operadores);
    DATABASE_forEach(struct Operador, ope, Operadores) {
        clrscr();
        form(1, Operadores, &ope); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Operadores, &ope); // Modo 2 = Editar
                DATABASE->update(Operadores, &ope);
                break;
            case 2:
                DATABASE->delete(Operadores);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Operadores);
    return EXIT_SUCCESS;
}

int cadastrar_acomodacao() {
    clrscr();

    struct Acomodacao acomo = {};
    form(0, Acomodacoes, &acomo); // Modo 0 = Inserir

    DATABASE->open(Acomodacoes);
    DATABASE->insert(Acomodacoes, &acomo);
    DATABASE->close(Acomodacoes);
    return EXIT_SUCCESS;
}

int ver_acomodacao() {
    DATABASE->open(Acomodacoes);
    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        clrscr();
        form(1, Acomodacoes, &acom); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Acomodacoes, &acom); // Modo 2 = Editar
                DATABASE->update(Acomodacoes, &acom);
                break;
            case 2:
                DATABASE->delete(Acomodacoes);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Acomodacoes);
    return EXIT_SUCCESS;
}

int cadastrar_produto() {
    clrscr();

    struct Produto prod = {};
    form(0, Produtos, &prod); // Modo 0 = Inserir

    DATABASE->open(Produtos);
    DATABASE->insert(Produtos, &prod);
    DATABASE->close(Produtos);
    return EXIT_SUCCESS;
}

int ver_produto() {
    DATABASE->open(Produtos);
    DATABASE_forEach(struct Produto, prod, Produtos) {
        clrscr();
        form(1, Produtos, &prod); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Produtos, &prod); // Modo 2 = Editar
                DATABASE->update(Produtos, &prod);
                break;
            case 2:
                DATABASE->delete(Produtos);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Produtos);
    return EXIT_SUCCESS;
}

int cadastrar_fornecedor() {
    clrscr();

    struct Fornecedor forn = {};
    form(0, Fornecedores, &forn); // Modo 0 = Inserir

    DATABASE->open(Fornecedores);
    DATABASE->insert(Fornecedores, &forn);
    DATABASE->close(Fornecedores);
    return EXIT_SUCCESS;
}

int ver_fornecedor() {
    DATABASE->open(Fornecedores);
    DATABASE_forEach(struct Fornecedor, forn, Fornecedores) {
        clrscr();
        form(1, Fornecedores, &forn); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Fornecedores, &forn); // Modo 2 = Editar
                DATABASE->update(Fornecedores, &forn);
                break;
            case 2:
                DATABASE->delete(Fornecedores);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Fornecedores);
    return EXIT_SUCCESS;
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

int cadastrar_reserva() {
    clrscr();

    struct Reserva reserva = {};
    form(0, Reservas, &reserva); // Modo 0 = Inserir

    DATABASE->open(Reservas);
    DATABASE->insert(Reservas, &reserva);
    DATABASE->close(Reservas);
    return EXIT_SUCCESS;
}

int ver_reserva() {
    DATABASE->open(Reservas);
    DATABASE_forEach(struct Reserva, reserva, Reservas) {
        clrscr();
        form(1, Reservas, &reserva); // Modo 1 = Visualizar
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Reservas, &reserva); // Modo 2 = Editar
                DATABASE->update(Reservas, &reserva);
                break;
            case 2:
                DATABASE->delete(Reservas);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Reservas);
    return EXIT_SUCCESS;
}
