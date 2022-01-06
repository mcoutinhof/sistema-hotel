#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/telas.h"

int cadastrar_reserva() {
    clrscr();
    //Recupera os dados da reserva
    struct Reserva reserva = {};
    form(0, Reservas, &reserva);

    //Cria a reserva
    DATABASE->open(Reservas);
    DATABASE->insert(Reservas, &reserva);
    DATABASE->close(Reservas);

    return EXIT_SUCCESS;
}

int ver_reserva() {
    DATABASE->open(Reservas);

    DATABASE_forEach(struct Reserva, reserva, Reservas) {
        clrscr();
        form(1, Reservas, &reserva);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Reservas, &reserva);
            DATABASE->update(Reservas, &reserva);
            break;
        case 2:
            DATABASE->delete (Reservas);
            break;
        }
        if (option == 3)
            break;
    }

    DATABASE->close(Reservas);
}