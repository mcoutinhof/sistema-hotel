#include "../lcurses.h"
#include "../model/tables.h"
#include "utils.h"
#include <stdlib.h>
#include "telas.h"

int cadastrar_operador() {
    clrscr();

    struct Operador ope = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Operadores, &ope);

    DATABASE->open(Operadores);
    DATABASE->insert(Operadores, &ope);
    DATABASE->close(Operadores);
    return EXIT_SUCCESS;
}

int ver_operador() {
    DATABASE->open(Operadores);

    DATABASE_forEach(struct Operador, ope, Operadores) {
        clrscr();
        form(1, Operadores, &ope);
        gotoxy(3, wherey() + 2);
        int option = menu(4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Operadores, &ope);
            DATABASE->update(Operadores, &ope);
            break;
        case 2:
            DATABASE->delete (Operadores);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Operadores);
}