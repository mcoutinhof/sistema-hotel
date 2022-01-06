#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int cadastrar_produto() {
    clrscr();

    struct Produto prod = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Produtos, &prod);

    DATABASE->open(Produtos);
    DATABASE->insert(Produtos, &prod);
    DATABASE->close(Produtos);
    return EXIT_SUCCESS;
}

int ver_produto() {
    DATABASE->open(Produtos);

    DATABASE_forEach(struct Produto, prod, Produtos) {
        clrscr();
        form(1, Produtos, &prod);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Produtos, &prod);
            DATABASE->update(Produtos, &prod);
            break;
        case 2:
            DATABASE->delete (Produtos);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Produtos);
}