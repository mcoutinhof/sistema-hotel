#include "telas.h"
#include "utils.h"
#include "../lcurses.h"
#include "../model/tables.h"
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
        switch (menu(6, "Hóspedes", "Acomodações", "Categorias de acomodações", "Operadores", "Hotel", "Voltar")) {
            case 0:
                menu_hospedes();
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
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
        switch (menu(3, "Cadastrar novo hóspede", "Procurar hóspede cadastrado", "Voltar")) {
            case 0:
                cadastrar_hospede();
                break;
            case 1:
                procurar_hospede();
                break;
            default: // Voltar
                return EXIT_SUCCESS;
        }
    }
}

int cadastrar_hospede() {
    clrscr(); // Sempre limpar a tela ...
    gotoxy(3, 2); // ... e reposicionar quando mudar de tela

    struct Hospede hosp = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hospedes, &hosp); // Modo 0 = Inserir

    // Validações, se necessário

    DATABASE->open(Hospedes);
    DATABASE->insert(Hospedes, &hosp); // Insere o hóspede no banco de dados
    DATABASE->close(Hospedes);
    return EXIT_SUCCESS;
}

int procurar_hospede() {
    return EXIT_SUCCESS;
}