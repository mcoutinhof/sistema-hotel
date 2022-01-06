#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/telas.h"

int cadastrar_hotel() {
    clrscr();

    struct Hotel hotel = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hoteis, &hotel); // Modo 0 = Inserir

    DATABASE->open(Hoteis);
    DATABASE->insert(Hoteis, &hotel); // Insere o hotel no banco de dados
    DATABASE->close(Hoteis);
    return EXIT_SUCCESS;
}

int ver_hotel() {
    DATABASE->open(Hoteis);

    DATABASE_forEach(struct Hotel, hotel, Hoteis) {
        clrscr();
        form(1, Hoteis, &hotel);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr();
            form(2, Hoteis, &hotel);
            DATABASE->update(Hoteis, &hotel);
            break;
        case 2:
            DATABASE->delete (Hoteis);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Hoteis);
}