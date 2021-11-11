/**
 * O armazenamento binário guarda registros (preferencialmente structs) de tamanho fixo (todas tem n bytes).
 * Antes de cada registro há um byte de controle: 1 se o registro está ocupado, 0 se está livre e pode ser sobrescrito.
 */

#include "database_bin.h"
#include <stdlib.h>

static Table *bin_open(const char *filename, size_t regSize) {
    register Table *table;
    if ((table = malloc(sizeof(Table)))) {
        if ((table->stream = fopen(filename, "a+"))) {
            if ((freopen(NULL, "r+", table->stream))) {
                table->regSize = regSize;
                if (fgetpos(table->stream, &table->cursorPos) == 0) {
                    return table;
                }
            }
            fclose(table->stream);
        }
        free(table);
    }
    return NULL;
}

static int bin_close(Table *table) {
    register FILE *stream = table->stream;
    free(table);
    return fclose(stream) == 0;
}

static int bin_rewind(Table *table) {
    return fseek(table->stream, 0, SEEK_SET) == 0
           && fgetpos(table->stream, &table->cursorPos) == 0;
}

static int bin_next(Table *table, void *ptr) {
    if (fsetpos(table->stream, &table->cursorPos) != 0) {
        return 0;
    }
    while (1)
        switch (fgetc(table->stream)) {
            case 0:
                if (fseek(table->stream, table->regSize, SEEK_CUR) == 0) {
                    break;
                }
            case EOF:
                return 0;
            default:
                return fread(ptr, table->regSize, 1, table->stream) == 1
                       && fgetpos(table->stream, &table->cursorPos) == 0;
        }
}

static int bin_delete(Table *table) {
    if (fsetpos(table->stream, &table->cursorPos) != 0) {
        return 0;
    }
    return fseek(table->stream, -1 * (table->regSize + 1), SEEK_CUR) == 0
           && fgetc(table->stream) > 0
           && fseek(table->stream, -1, SEEK_CUR) == 0
           && fputc(0, table->stream) == 0
           && fseek(table->stream, table->regSize, SEEK_CUR) == 0;
}

static int bin_update(Table *table, const void *ptr) {
    if (fsetpos(table->stream, &table->cursorPos) != 0) {
        return 0;
    }
    return fseek(table->stream, -1 * (table->regSize + 1), SEEK_CUR) == 0
           && fgetc(table->stream) > 0
           && fwrite(ptr, table->regSize, 1, table->stream) == 1;
}

static int bin_insert(Table *table, const void *ptr) {
    if (fseek(table->stream, 0, SEEK_SET) != 0) {
        return 0;
    }
    while (1)
        switch (fgetc(table->stream)) {
            case EOF:
                if (fputc(0, table->stream) != 0) {
                    return 0;
                }
            case 0:
                return fwrite(ptr, table->regSize, 1, table->stream) == 1
                       && fseek(table->stream, -1 * (table->regSize + 1), SEEK_CUR) == 0
                       && fputc(1, table->stream) > 0
                       && fseek(table->stream, table->regSize, SEEK_CUR) == 0
                       && fgetpos(table->stream, &table->cursorPos) == 0;
            default:
                if (fseek(table->stream, table->regSize, SEEK_CUR) != 0) {
                    return 0;
                }
        }
}

const Database *BINARY_DATABASE = &(Database) {
        .open = bin_open,
        .close = bin_close,
        .rewind = bin_rewind,
        .next = bin_next,
        .delete = bin_delete,
        .update = bin_update,
        .insert = bin_insert,
};