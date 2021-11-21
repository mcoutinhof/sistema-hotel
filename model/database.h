#pragma once

/**
 * Um vetor de ponteiros para structs que armazenam informações sobre a tabela.
 * O primeiro ponteiro deve apontar para uma TableState (inicialmente vazia);
 * O segundo ponteiro deve apontar para uma TableInfo;
 * Os demais ponteiros devem apontar para uma ou mais ColumnMeta;
 * O último ponteiro deve ser NULL para denotar o fim do vetor.
 */
typedef void *Table[];

/**
 * Uma espécie de interface (POO) para os diferentes tipos de armazenamento (binário, XML, etc).
 */
typedef struct {
    /**
     * Abre a tabela e posiciona o cursor no início.
     * @param table A tabela a ser aberta.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*open)(const Table table);

    /**
     * Fecha a tabela aberta por open().
     * @param table A tabela a ser fechada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*close)(const Table table);

    /**
     * Retorna o cursor ao início da tabela.
     * @param table A tabela a ser rebobinada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*rewind)(const Table table);

    /**
     * Lê o próximo registro, o armazena na memória e avança o cursor.
     * @param table A tabela a ser lida.
     * @param ptr Ponteiro para o local da memória onde o registro será armazenado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*next)(const Table table, void *ptr);

    /**
     * Deleta o registro anterior ao cursor.
     * @param table A tabela a ser modificada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*delete)(const Table table);

    /**
     * Atualiza o registro anterior ao cursor.
     * @param table A tabela a ser modificada.
     * @param ptr Ponteiro para o registro atualizado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*update)(const Table table, const void *ptr);

    /**
     * Insere um registro na tabela e posiciona o cursor após ele.
     * @param table A tabela a ser modificada.
     * @param ptr Ponteiro para o registro a ser inserido.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*insert)(const Table table, const void *ptr);
} Database;

/** Itera por todos os registros da tabela. */
#define DATABASE_forEach(elementType, elementName, table) \
DATABASE->rewind((table));                                \
for (elementType (elementName); DATABASE->next((table), &(elementName));)

/** Itera por todos os registros da tabela e os atualiza ao final de cada iteração. */
#define DATABASE_map(elementType, elementName, table) \
DATABASE->rewind((table));                            \
for (elementType (elementName); DATABASE->next((table), &(elementName)); DATABASE->update((table), &(elementName)))

extern const Database *DATABASE;

int initDatabase();