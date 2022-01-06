#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int cadastrar_hospede() {
    clrscr();
    struct Hospede hosp = {}; // Sempre coloque as chaves pra zerar os valores da struct
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
        form(1, Hospedes, &hosp);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Hospedes, &hosp);
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
}