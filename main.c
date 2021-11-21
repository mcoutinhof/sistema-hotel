#include "model/database.h"
#include "view/telas.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (!initDatabase()) {
        fprintf(stderr, "Não foi possível iniciar o banco de dados!\n");
        return EXIT_FAILURE;
    }
    fputs("\033[?1049h", stdout); // Entra na tela alternativa
    menu_principal();
    return EXIT_SUCCESS;
}

static inline void __attribute__((destructor)) eb36934a08a2d175838bd684cf7eab95() {
    fputs("\033[?1049l", stdout); // Volta à tela principal
}