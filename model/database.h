#pragma once

#include <stdio.h>

/**
 * Uma array de endereços para structs que guardam informações que designam a tabela.
 * O primeiro endereço deve ser para uma TableState (inicialmente vazia);
 * O segundo endereço deve ser para uma TableInfo;
 * Os demais endereços deve ser para uma ou mais ColumnMetas;
 * O último endereço deve ser NULL, para denotar o final da array.
 */
typedef void *Table[];

/**
 * Guarda o estado da tabela.
 * São variáveis usadas por cada implementação de banco de dados para ler e escrever nos arquivos de tabela.
 */
typedef struct {
    /** O arquivo que armazena os registros. */
    FILE *stream;
    /** Tamanho em bytes de cada registro, calculado a partir dos metadados das colunas. */
    size_t regSize;
    /** Última posição válida do cursor. */
    fpos_t cursorPos;
} TableState;

/**
 * Guarda informações sobre a tabela.
 */
typedef struct {
    /** Caminho para o arquivo que armazena a tabela. */
    const char *filename;
} TableInfo;

/**
 * Metadados da coluna, especificam com devem ser tratados os dados que nela forem armazenados.
 */
typedef struct {
    /** Nome mostrado para o usuário, quando necessário. */
    const char *displayName;
    /** Nome da tag que representa essa coluna em arquivos XML. */
    const char *tagName;
    /** Formato como o valor é lido e escrito. */
    const char *format;
    /** Tamanho em bytes do espaço de memória em que o valor será guardado. */
    size_t size;
    /** TODO: descrever as flags, quando adicionar alguma. */
    char flags;
} ColumnMeta;

/**
 * Uma espécie de interface para os diferentes tipos de armazenamento (binário, XML, etc).
 */
typedef struct {
    /**
     * Abre uma tabela com o cursor no início. Se o arquivo não existir, ele é criado. É necessário fecha-la usando close().
     * @param table A tabela a ser aberta.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*open)(const Table table);

    /**
     * Fecha uma tabela que foi aberta por open().
     * @param table A tabela a ser fechada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*close)(const Table table);

    /**
     * Volta o cursor ao início da tabela.
     * @param table A tabela a ser rebobinada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*rewind)(const Table table);

    /**
     * Copia o próximo registro, se ele existir, para uma posição de memória e avança o cursor.
     * @param table A tabela a ser lida.
     * @param ptr Ponteiro para a posição de memória para onde o registro será copiado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*next)(const Table table, void *ptr);

    /**
     * Deleta o último registro retornado por next().
     * @param table A tabela a ser modificada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*delete)(const Table table);

    /**
     * Copia um registro de uma posição de memória sobrescrevendo o último registro retornado por next().
     * @param table A tabela a ser modificada.
     * @param ptr Ponteiro para a posição de memória de onde o registro será copiado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*update)(const Table table, const void *ptr);

    /**
     * Copia um registro de uma posição de memória para um espaço livre na tabela e coloca o cursor à frente dele.
     * @param table A tabela a ser modificada.
     * @param ptr Ponteiro para a posição de memória de onde o registro será copiado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*insert)(const Table table, const void *ptr);
} Database;

/** Itera por todos os registros de uma tabela. */
#define DATABASE_forEach(elementType, elementName, table) \
DATABASE->rewind((table));                                \
for (elementType (elementName); DATABASE->next((table), &(elementName));)

/** Itera por todos os registros de uma tabela e atualiza o registro ao final de cada iteração. */
#define DATABASE_map(elementType, elementName, table) \
DATABASE->rewind((table));                            \
for (elementType (elementName); DATABASE->next((table), &(elementName)); DATABASE->update((table), &(elementName)))

extern const Database *DATABASE;

int initDatabase();