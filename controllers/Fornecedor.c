#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int cadastrar_fornecedor() {
    clrscr();

    struct Fornecedor forn = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Fornecedores, &forn);

    DATABASE->open(Fornecedores);
    DATABASE->insert(Fornecedores, &forn);
    DATABASE->close(Fornecedores);
    return EXIT_SUCCESS;
}

int ver_fornecedor() {
    DATABASE->open(Fornecedores);

    DATABASE_forEach(struct Fornecedor, forn, Fornecedores) {
        clrscr();
        form(1, Fornecedores, &forn);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Fornecedores, &forn);
            DATABASE->update(Fornecedores, &forn);
            break;
        case 2:
            DATABASE->delete (Fornecedores);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Fornecedores);
}