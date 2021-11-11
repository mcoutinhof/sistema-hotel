#include "database_bin.h"

const Database *DATABASE;

// TODO: Adicionar suporte a configurações
int initDatabase() {
    DATABASE = BINARY_DATABASE;
    return 1;
}

// TODO: Adicionar função para migrar binário pra XML e vice-versa

// TODO: Adicionar função para importar e exportar tabelas em XML