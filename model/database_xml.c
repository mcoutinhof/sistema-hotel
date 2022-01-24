/**
 * @author Mateus Coutinho
 * Work in progress.
 */

#include "database_xml.h"
#include <stdlib.h>
#include <string.h>

static int xml_open(Table table) {
    TableState *tableState = *table++;
    TableInfo *tableInfo = *table++;

    char fileName[256];
    strcpy(fileName, tableInfo->tagName);
    strcat(fileName, ".xml");

    if ((tableState->stream = fopen(fileName, "a+"))) { // a+ porque cria o arquivo se ele não existir.
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

static int xml_close(Table table) {
    return 0;
}

static int xml_rewind(Table table) {
    TableState *tableState = *table++;
    tableState->arrIndex = 0;
    return 1;
}

static int xml_next(Table table, void *ptr) {
    TableState *tableState = *table++;
    if (tableState->arrIndex < tableState->arrSize) {
        memcpy(ptr, tableState->arr + tableState->arrIndex++ * tableState->regSize, tableState->regSize);
        return 1;
    }
    return 0;
}

static int xml_delete(Table table) {
    TableState *tableState = *table++;
    tableState->arrIndex--;
    memmove(tableState->arr + (tableState->arrIndex - 1) * tableState->regSize,
            tableState->arr + (tableState->arrIndex) * tableState->regSize,
            (tableState->arrSize - tableState->arrIndex) * tableState->regSize);
    tableState->arr = realloc(tableState->arr, --tableState->arrSize * tableState->regSize);
    return 1;
}

static int xml_update(Table table, const void *ptr) {
    TableState *tableState = *table++;
    memcpy(tableState->arr + (tableState->arrIndex - 1) * tableState->regSize, ptr, tableState->regSize);
    return 1;
}

static int xml_insert(Table table, void *ptr) {
    TableState *tableState = *table++;
    TableInfo *tableInfo = *table++;
    size_t offset = 0;
    tableState->arrIndex = tableState->arrSize;

    // Auto-increment
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; offset += colMeta->size) {
        if ((colMeta->flags & COL_FLAG_AUTO_INCREMENT)) {
            *((unsigned int *) ptr + offset) = tableState->arrIndex;
        }
    }

    tableState->arr = realloc(tableState->arr, ++tableState->arrSize * tableState->regSize);
    memcpy(tableState->arr + tableState->arrIndex++ * tableState->regSize, ptr, tableState->regSize);
    return 1;
}

Database *XML_DATABASE = &(Database) {
        .open   = xml_open,
        .close  = xml_close,
        .rewind = xml_rewind,
        .next   = xml_next,
        .delete = xml_delete,
        .update = xml_update,
        .insert = xml_insert,
};