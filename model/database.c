/**
 * @author Mateus Coutinho
 */

#include "database_bin.h"
#include "database_xml.h"
#include "../lcurses.h"
#include "../view/utils.h"
#include <string.h>

Database *DATABASE;

// TODO: Adicionar suporte a configurações.
int initDatabase() {
    int opt = 0;
    FILE *f = NULL;
    if ((f = fopen("config.dat", "a+"))) { // a+ porque cria o arquivo se ele não existir.
        if ((freopen(NULL, "r+", f))) { // r+ porque permite ler e (sobre)escrever.
            if ((opt = fgetc(f)) == EOF) {
                printf($a "Escolha o método de armazenamento:\n");
                opt = menu($f, 2, "Binário", "XML");
                fputc(opt, f);
                clrscr();
            }
            DATABASE = opt ? XML_DATABASE : BINARY_DATABASE;
            fclose(f);
            return 1;
        }
        fclose(f);
    }
    return 0;
}

// TODO: Adicionar função para migrar binário pra XML e vice-versa.

// TODO: Adicionar função para importar e exportar tabelas em XML.

int DATABASE_findBy(const char *colName, const void *colValue, Table table, void *saveHere) {
    size_t offset = 0;
    DATABASE->rewind(table);
    void **tablePtr = table + 2;
    for (ColumnMeta *colMeta; (colMeta = *tablePtr++) != NULL; offset += colMeta->size) {
        if (strcasecmp(colMeta->tagName, colName) == 0) {
            while (DATABASE->next(table, saveHere)) {
                if (memcmp(saveHere + offset, colValue, colMeta->size) == 0) {
                    return 1;
                }
            }
            break;
        }
    }
    return 0;
}