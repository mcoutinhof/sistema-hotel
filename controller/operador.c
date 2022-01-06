#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int isAdmin = 0;

int logar_operador() {
    isAdmin = 2;
    return 1;
}

int cadastrar_operador() {
    clrscr();
    struct Operador op = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Operadores, &op); // Modo 0 = Inserir
    DATABASE->open(Operadores);
    DATABASE->insert(Operadores, &op);
    DATABASE->close(Operadores);
    return EXIT_SUCCESS;
}

int ver_operador() {
    DATABASE->open(Operadores);
    DATABASE_forEach(struct Operador, op, Operadores) {
        clrscr();
        form(1, Operadores, &op);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Operadores, &op);
                DATABASE->update(Operadores, &op);
                break;
            case 2:
                DATABASE->delete(Operadores);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Operadores);
}