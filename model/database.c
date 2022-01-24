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

int DATABASE_findBy(const char *colName, const void *colValue, Table table, void *saveHere) {
    size_t offset = 0;
    DATABASE->rewind((table));
    void **table2 = table;
    TableState *tableState = *table++;
    TableInfo *tableInfo = *table++;
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; offset += colMeta->size) {
        if (strcasecmp(colMeta->tagName, colName) == 0) {
            while (DATABASE->next(table2, saveHere)) {
                if (memcmp(saveHere + offset, colValue, colMeta->size) == 0) {
                    return 1;
                }
            }
            return 0;
        }
    }
    return 0;
}