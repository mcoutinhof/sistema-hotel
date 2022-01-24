/**
 * @author Mateus Coutinho
 * Work in progress.
 */

#include "database_xml.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>

static int xml_insert(Table table, void *ptr);

static int xml_open(Table table) {
    void **tablePtr = table;
    TableState *tableState = *tablePtr++;
    TableInfo *tableInfo = *tablePtr++;

    tableState->regSize = 0;
    for (ColumnMeta *colMeta; (colMeta = *tablePtr++) != NULL;) {
        tableState->regSize += colMeta->size;
    }

    tableState->arr = NULL;
    tableState->arrIndex = 0;
    tableState->arrSize = 0;


    char fileName[256];
    sprintf(fileName, "%s.xml", tableInfo->tagName);

    if ((tableState->stream = fopen(fileName, "a+"))) { // a+ porque cria o arquivo se ele não existir.
        if ((freopen(NULL, "r+", tableState->stream))) { // r+ porque permite sobrescrever os dados.
            void *ptr = malloc(tableState->regSize);
            char buf[64] = {};

            while (readVal(tableState->stream, '>', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, buf)) {
                if (strcasecmp(buf, "<registro") == 0) {
                    memset(ptr, 0, tableState->regSize);
                } else if (strcasecmp(buf, "</registro") == 0) {
                    xml_insert(table, ptr);
                } else {
                    size_t offset = 0;
                    tablePtr = table + 2;
                    for (ColumnMeta *colMeta; (colMeta = *tablePtr++) != NULL; offset += colMeta->size) {
                        if (strcasecmp(buf + 1, colMeta->tagName) == 0) {
                            readVal(tableState->stream, '<', colMeta, ptr + offset);
                            readVal(tableState->stream, '>', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, buf);
                            break;
                        }
                    }
                }
            }

            free(ptr);
            tableState->arrIndex = 0;
            fclose(tableState->stream);
            return 1;
        }
        fclose(tableState->stream);
    }
    return 0;
}

static int xml_close(Table table) {
    void **tablePtr = table;
    TableState *tableState = *tablePtr++;
    TableInfo *tableInfo = *tablePtr++;
    char fileName[256];
    sprintf(fileName, "%s.xml", tableInfo->tagName);
    if ((tableState->stream = fopen(fileName, "w"))) { // w sobrescreve o arquivo
        for (size_t i = 0; i < tableState->arrSize; i++) {
            void *ptr = tableState->arr + i * tableState->regSize;
            fprintf(tableState->stream, "<registro>");
            tablePtr = table + 2;
            for (ColumnMeta *colMeta; (colMeta = *tablePtr++) != NULL; ptr += colMeta->size) {
                fprintf(tableState->stream, "<%s>", colMeta->tagName);
                printVal(tableState->stream, colMeta, ptr);
                fprintf(tableState->stream, "</%s>", colMeta->tagName);
            }
            fprintf(tableState->stream, "</registro>");
        }
        fclose(tableState->stream);
        free(tableState->arr);
        return 1;
    }
    free(tableState->arr);
    return 0;
}

static int xml_rewind(Table table) {
    TableState *tableState = *table;
    tableState->arrIndex = 0;
    return 1;
}

static int xml_next(Table table, void *ptr) {
    TableState *tableState = *table;
    if (tableState->arrIndex < tableState->arrSize) {
        memcpy(ptr, tableState->arr + tableState->arrIndex++ * tableState->regSize, tableState->regSize);
        return 1;
    }
    return 0;
}

static int xml_delete(Table table) {
    TableState *tableState = *table;
    if (tableState->arrIndex > 0) {
        if (--tableState->arrIndex < tableState->arrSize) {
            if (tableState->arrIndex < --tableState->arrSize) {
                memmove(tableState->arr + (tableState->arrIndex) * tableState->regSize,
                        tableState->arr + (tableState->arrIndex + 1) * tableState->regSize,
                        (tableState->arrSize - tableState->arrIndex) * tableState->regSize);
            }
            tableState->arr = realloc(tableState->arr, tableState->arrSize * tableState->regSize);
            return 1;
        }
    }
    return 0;
}

static int xml_update(Table table, const void *ptr) {
    TableState *tableState = *table;
    if (tableState->arrIndex > 0) {
        memcpy(tableState->arr + (tableState->arrIndex - 1) * tableState->regSize, ptr, tableState->regSize);
        return 1;
    }
    return 0;
}

static int xml_insert(Table table, void *ptr) {
    TableState *tableState = *table++;
    TableState *tableInfo = *table++;
    size_t offset = 0;

    tableState->arrIndex = tableState->arrSize++;

    // Auto-increment
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; offset += colMeta->size) {
        if ((colMeta->flags & COL_FLAG_AUTO_INCREMENT)) {
            *((unsigned int *) ptr + offset) = tableState->arrIndex;
        }
    }

    tableState->arr = realloc(tableState->arr, tableState->arrSize * tableState->regSize);
    memcpy(tableState->arr + tableState->arrIndex * tableState->regSize, ptr, tableState->regSize);
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