#include "telas.h"
#include "../lcurses.h"
#include "../model/tables.h"
#include "utils.h"
#include <stdlib.h>

int menu_principal() {
    while (1) {
        clrscr();
        gotoxy(3, 2);
        switch (menu(5, "Cadastros", "Produtos", "Reservas", "Relatórios", "Sair")) {
        case 0:
            menu_cadastros();
            break;
        case 1:
            // menu_produtos();
            break;
        case 2:
            // menu_reservas();
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
        gotoxy(3, 2);
        switch (menu(8, "Hóspedes", "Hotel", "Categorias de acomodações", "Operadores", "Acomodações", "Produtos", "Fornecedores", "Voltar")) {
        case 0:
            menu_hospedes();
            break;
        case 1:
            menu_hotel();
            break;
        case 2:
            menu_categoria();
            break;
        case 3:
            break;
        case 4:
            menu_acomodacao();
            break;
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int menu_hospedes() {
    while (1) {
        clrscr();
        gotoxy(3, 2);
        switch (menu(3, "Inserir hóspede", "Ver Hospede", "Voltar")) {
        case 0:
            cadastrar_hospede();
            break;
        case 1:
            ver_hospede();
            break;
        case 3:

            //procurar_hospede();
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int menu_hotel() {
    while (1) {
        clrscr();
        gotoxy(3, 2);
        switch (menu(4, "Cadastrar Hotel", "Editar Hotel", "Remover Hotel", "Exibir Hoteis", "Voltar")) {
        case 0:
            cadastrar_hotel();
            break;
        case 1:
            //editar_hotel(); //need code
            break;
        case 2:
            //remover_hotel(); //need code
            break;
        case 3:
            //exibir_hotel(); //need code
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int menu_categoria() {
    while (1) {
        clrscr();
        gotoxy(3, 2);
        switch (menu(4, "Cadastrar Categoria de Acomodação", "Editar Categoria de Acomodação", "Remover Categoria de Acomodação", "Exibir Categorias de Acomodações", "Voltar")) {
        case 0:
            cadastrar_categoria();
            break;
        case 1:
            //editar_hotel(); //need code
            break;
        case 2:
            //remover_hotel(); //need code
            break;
        case 3:
            //exibir_hotel(); //need code
        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int menu_acomodacao() {
    while (1) {
        clrscr();
        gotoxy(3, 2);
        switch (menu(4, "Cadastrar Acomodação", "Editar Acomodação", "Remover Acomodação", "Exibir Acomodação", "Voltar")) {
        case 0:
            cadastrar_acomodacao();
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

        default: // Voltar
            return EXIT_SUCCESS;
        }
    }
}

int cadastrar_hospede() {
    clrscr();     // Sempre limpar a tela ...
    gotoxy(3, 2); // ... e reposicionar quando mudar de tela

    struct Hospede hosp = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hospedes, &hosp); // Modo 0 = Inserir

    // Validações, se necessário

    DATABASE->open(Hospedes);
    DATABASE->insert(Hospedes, &hosp); // Insere o hóspede no banco de dados
    DATABASE->close(Hospedes);
    return EXIT_SUCCESS;
}

int ver_hospede() {
    clrscr();     // Sempre limpar a tela ...
    gotoxy(3, 2); // ... e reposicionar quando mudar de tela

    DATABASE->open(Hospedes);

    DATABASE_forEach(struct Hospede, hosp, Hospedes) {
        clrscr();
        gotoxy(3, 2);
        form(1, Hospedes, &hosp);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr();     // Sempre limpar a tela ...
            gotoxy(3, 2); // ... e reposicionar quando mudar de tela
            form(2, Hospedes, &hosp);
            DATABASE->update(Hospedes, &hosp);
            break;
        case 2:
            DATABASE->delete (Hospedes);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Hospedes);
}

int cadastrar_hotel() {
    clrscr();
    gotoxy(3, 2);

    struct Hotel hote = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hoteis, &hote); // Modo 0 = Inserir

    // Validações, se necessário

    DATABASE->open(Hoteis);
    DATABASE->insert(Hoteis, &hote); // Insere o hotel no banco de dados
    DATABASE->close(Hoteis);
    return EXIT_SUCCESS;
}

int cadastrar_categoria() {
    clrscr();
    gotoxy(3, 2);

    struct Categoria categ = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Categorias, &categ); // Modo 0 = Inserir

    // Validações, se necessário

    DATABASE->open(Categorias);
    DATABASE->insert(Categorias, &categ); // Insere a categoria no banco de dados
    DATABASE->close(Categorias);
    return EXIT_SUCCESS;
}

int cadastrar_acomodacao() {
    clrscr();
    gotoxy(3, 2);

    struct Acomodacao acomo = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Acomodacoes, &acomo); // Modo 0 = Inserir

    // Validações, se necessário

    DATABASE->open(Acomodacoes);
    DATABASE->insert(Acomodacoes, &acomo);
    DATABASE->close(Acomodacoes);
    return EXIT_SUCCESS;
}
