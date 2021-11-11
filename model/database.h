#pragma once

#include <stdio.h>

typedef struct Table {
    /** O arquivo que armazena os registros */
    FILE *stream;
    /** Tamanho em bytes de cada registro */
    size_t regSize;
    /** Última posição válida do cursor */
    fpos_t cursorPos;
} Table;

/**
 * Uma espécie de interface para os diferentes tipos de armazenamento (binário, texto, etc).
 */
typedef struct Database {
    /**
     * Abre uma tabela e posiciona o cursor no início. Se ela não existir, ela é criada.
     * É necessário fecha-la usando close().
     * @param filename Caminho para o arquivo que armazena a tabela.
     * @param regSize Tamanho em bytes de cada registro da tabela.
     * @return um ponteiro para a tabela se tiver sucesso, NULL caso contrário.
     */
    Table *(*open)(const char *filename, size_t regSize);

    /**
     * Fecha uma tabela que foi aberta por open().
     * @param table Ponteiro para a tabela, retornado por open().
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*close)(Table *table);

    /**
     * Volta o cursor ao início da tabela.
     * @param table Ponteiro para a tabela, retornado por open().
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*rewind)(Table *table);

    /**
     * Copia o próximo registro, se ele existir, para uma posição de memória e avança o cursor.
     * @param table Ponteiro para a tabela, retornado por open().
     * @param ptr Ponteiro para onde o registro será copiado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*next)(Table *table, void *ptr);

    /**
     * Deleta o último registro retornado por next().
     * @param table Ponteiro para a tabela, retornado por open().
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*delete)(Table *table);

    /**
     * Copia um registro de uma posição de memória sobrescrevendo o último registro retornado por next().
     * @param table Ponteiro para a tabela, retornado por open().
     * @param ptr Ponteiro para donde o registro será copiado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*update)(Table *table, const void *ptr);

    /**
     * Copia um registro de uma posição de memória para um espaço livre na tabela e coloca o cursor à frente dele.
     * @param table Ponteiro para a tabela, retornado por open().
     * @param ptr Ponteiro para donde o registro será copiado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*insert)(Table *table, const void *ptr);
} Database;

extern const Database *DATABASE;

int initDatabase();