#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/telas.h"

int cadastrar_acomodacao() {
    clrscr();

    struct Acomodacao acomo = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Acomodacoes, &acomo); // Modo 0 = Inserir

    DATABASE->open(Acomodacoes);
    DATABASE->insert(Acomodacoes, &acomo);
    DATABASE->close(Acomodacoes);
    return EXIT_SUCCESS;
}

int ver_acomodacao() {
    DATABASE->open(Acomodacoes);

    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        clrscr();
        form(1, Acomodacoes, &acom);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
        case 0:
            continue;
        case 1:
            clrscr(); // Sempre limpar a tela ...
            form(2, Acomodacoes, &acom);
            DATABASE->update(Acomodacoes, &acom);
            break;
        case 2:
            DATABASE->delete (Acomodacoes);
            break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Acomodacoes);
}