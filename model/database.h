/**
 * @author Mateus Coutinho
 */

#pragma once

/**
 * Um vetor de ponteiros para structs que armazenam informações sobre a tabela.
 * O primeiro ponteiro deve apontar para uma TableState (inicialmente vazia);
 * O segundo ponteiro deve apontar para uma TableInfo;
 * Os demais ponteiros devem apontar para uma ou mais ColumnMeta;
 * O último ponteiro deve ser NULL para denotar o fim do vetor.
 * @note Table não armazena os registros, mas armazena informações suficientes para interagir com eles.
 */
typedef const void *Table[];

/**
 * Uma espécie de interface (POO) para os diferentes tipos de armazenamento (binário ou XML).
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
     * Lê o próximo registro, o armazena na struct e avança o cursor.
     * @param table A tabela a ser lida.
     * @param ptr Ponteiro para a struct onde o registro será armazenado.
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

/**
 * Volta ao início da tabela e procura por um registro com um campo `id` específico.
 * @param table A tabela a ser lida.
 * @param ptr Ponteiro para a struct onde o registro será armazenado.
 * @param id O ID que está sendo procurado.
 * @return 1 ao encontrar, 0 caso contrário.
 */
int DATABASE_findById(const Table table, void *ptr, unsigned int id);

/** O sistema de banco de dados (binário ou xml) que está sendo usado. */
extern const Database *DATABASE;

/** Inicia o banco de dados. @return 1 se tiver sucesso, 0 caso contrário. */
int initDatabase();

/** @return 1 se o usuário logado tem permissões de administração, 0 caso contrário. */
int isAdmin();