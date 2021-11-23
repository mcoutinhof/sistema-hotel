#include "database_bin.h"
#include "database_local.h"
#include <string.h>

const Database *DATABASE;

// TODO: Adicionar suporte a configurações
int initDatabase() {
    DATABASE = BINARY_DATABASE;
    return 1;
}

// TODO: Adicionar função para migrar binário pra XML e vice-versa

// TODO: Adicionar função para importar e exportar tabelas em XML

int DATABASE_findById(const Table table, void *ptr, unsigned int id) {
    TableState *tableState = *table++;
    const TableInfo *tableInfo = *table++;
    size_t offset = 0;
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; offset += colMeta->size) {
        if (strcmp(colMeta->tagName, "id") == 0) {
            DATABASE->open(table);
            DATABASE->rewind((table));
            while (DATABASE->next((table), ptr)) {
                if (memcmp(ptr + offset, &id, colMeta->size) == 0) {
                    DATABASE->close(table);
                    return 1;
                }
            }
            DATABASE->close(table);
            break;
        }
    }
    return 0;
}