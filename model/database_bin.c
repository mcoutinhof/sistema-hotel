/**
 * @author Mateus Coutinho
 * O armazenamento binário guarda registros (preferencialmente structs) de tamanho fixo (todas tem n bytes).
 * Antes de cada registro há um byte de controle: 1 se o registro está ocupado, 0 se está livre e pode ser sobrescrito.
 * @note Os retornos com múltiplas condições são usados para mimicar um try-catch:
 * Se uma função retorna código de sucesso, prossegue, se não, retorna 0. Se todas as funções tiverem sucesso, retorna 1.
 */

#include "database_bin.h"
#include "database_local.h"

static int bin_open(const Table table) {
    TableState *tableState = *table++;
    const TableInfo *tableInfo = *table++;
    if ((tableState->stream = fopen(tableInfo->fileName, "a+"))) { // a+ porque cria o arquivo se ele não existir.
        if ((freopen(NULL, "r+", tableState->stream))) { // r+ porque permite sobrescrever os dados.
            if (fgetpos(tableState->stream, &tableState->cursorPos) == 0) {
                tableState->regSize = 0;
                for (ColumnMeta *colMeta; (colMeta = *table) != NULL; ++table) {
                    tableState->regSize += colMeta->size;
                }
                return 1;
            }
        }
        fclose(tableState->stream);
    }
    return 0;
}

static int bin_close(const Table table) {
    const TableState *tableState = *table;
    return fclose(tableState->stream) == 0;
}

static int bin_rewind(const Table table) {
    TableState *tableState = *table;
    return fseek(tableState->stream, 0, SEEK_SET) == 0
           && fgetpos(tableState->stream, &tableState->cursorPos) == 0;
}

static int bin_next(const Table table, void *ptr) {
    TableState *tableState = *table;
    if (fsetpos(tableState->stream, &tableState->cursorPos) != 0) {
        return 0;
    }
    while (1) {
        switch (fgetc(tableState->stream)) {
            case 0:
                if (fseek(tableState->stream, tableState->regSize, SEEK_CUR) == 0) {
                    break;
                }
            case EOF:
                return 0;
            default:
                return fread(ptr, tableState->regSize, 1, tableState->stream) == 1
                       && fgetpos(tableState->stream, &tableState->cursorPos) == 0;
        }
    }
}

static int bin_delete(const Table table) {
    const TableState *tableState = *table;
    return fsetpos(tableState->stream, &tableState->cursorPos) == 0
           && fseek(tableState->stream, -1 * (tableState->regSize + 1), SEEK_CUR) == 0
           && fgetc(tableState->stream) > 0
           && fseek(tableState->stream, -1, SEEK_CUR) == 0
           && fputc(0, tableState->stream) == 0
           && fseek(tableState->stream, tableState->regSize, SEEK_CUR) == 0;
}

static int bin_update(const Table table, const void *ptr) {
    const TableState *tableState = *table;
    return fsetpos(tableState->stream, &tableState->cursorPos) == 0
           && fseek(tableState->stream, -1 * (tableState->regSize + 1), SEEK_CUR) == 0
           && fgetc(tableState->stream) > 0
           && fwrite(ptr, tableState->regSize, 1, tableState->stream) == 1;
}

static int bin_insert(const Table table, const void *ptr) {
    TableState *tableState = *table;
    if (fseek(tableState->stream, 0, SEEK_SET) != 0) {
        return 0;
    }
    while (1) {
        switch (fgetc(tableState->stream)) {
            case EOF:
                if (fputc(0, tableState->stream) != 0) {
                    return 0;
                }
            case 0:
                return fwrite(ptr, tableState->regSize, 1, tableState->stream) == 1
                       && fseek(tableState->stream, -1 * (tableState->regSize + 1), SEEK_CUR) == 0
                       && fputc(1, tableState->stream) > 0
                       && fseek(tableState->stream, tableState->regSize, SEEK_CUR) == 0
                       && fgetpos(tableState->stream, &tableState->cursorPos) == 0;
            default:
                if (fseek(tableState->stream, tableState->regSize, SEEK_CUR) != 0) {
                    return 0;
                }
        }
    }
}

const Database *BINARY_DATABASE = &(Database) {
        .open   = bin_open,
        .close  = bin_close,
        .rewind = bin_rewind,
        .next   = bin_next,
        .delete = bin_delete,
        .update = bin_update,
        .insert = bin_insert,
};