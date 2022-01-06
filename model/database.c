/**
 * @author Mateus Coutinho
 */

#include "database_bin.h"
#include <string.h>

Database *DATABASE;

// TODO: Adicionar suporte a configurações.
int initDatabase() {
    DATABASE = BINARY_DATABASE;
    return 1;
}

// TODO: Adicionar função para migrar binário pra XML e vice-versa.

// TODO: Adicionar função para importar e exportar tabelas em XML.

int DATABASE_findById(Table table, void *ptr, unsigned int id) {
    size_t offset = 0;
    DATABASE->rewind((table));
    TableState *tableState = *table++;
    TableInfo *tableInfo = *table++;
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; offset += colMeta->size) {
        if (strcasecmp(colMeta->tagName, "id") == 0) {
            while (DATABASE->next(table, ptr)) {
                if (*(unsigned int *) (ptr + offset) == id) {
                    return 1;
                }
            }
            return 0;
        }
    }
    return 0;
}