#include <stdio.h>
#include <stdlib.h>
#include "model/database.h"
#include "model/tables.h"

int main() {
    if (!initDatabase()) {
        fprintf(stderr, "TODO: Adicionar mensagem de erro.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}