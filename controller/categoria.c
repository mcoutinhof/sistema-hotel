/**
 * @authors Ryan W. Fonseca
 */

#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int cadastrar_categoria() {
    clrscr();
    struct Categoria cat = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Categorias, &cat); // Modo 0 = Inserir
    DATABASE->open(Categorias);
    DATABASE->insert(Categorias, &cat);
    DATABASE->close(Categorias);
    return EXIT_SUCCESS;
}

int ver_categoria() {
    DATABASE->open(Categorias);
    DATABASE_forEach(struct Categoria, cat, Categorias) {
        clrscr();
        form(1, Categorias, &cat);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Categorias, &cat);
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
}