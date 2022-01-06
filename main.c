/**
 * @author Mateus Coutinho
 */

#include "model/database.h"
#include "view/rotas.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (!initDatabase()) {
        fprintf(stderr, "Não foi possível iniciar o banco de dados!\n");
        return EXIT_FAILURE;
    }
    fputs("\033[?1049h", stdout); // Entra na tela alternativa
    if (logar_operador()) {
        menu_principal();
    }
    return EXIT_SUCCESS;
}

/**
 * static: a função está limitada ao escopo do arquivo (mas ainda pode ser chamada por endereço).
 * inline: sugere ao compilador inserir o código da função onde ela é chamada, ao invés de perder tempo chamando-a.
 * __attribute__((destructor)): a função será automaticamente chamada quando o programa finalizar.
 */
static inline void __attribute__((destructor)) eb36934a08a2d175838bd684cf7eab95() { // O nome da função não importa.
    fputs("\033[?1049l", stdout); // Volta à tela principal
}