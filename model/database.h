/**
 * @author Mateus Coutinho
 */

#pragma once

#include <stdio.h>

/** O estado da tabela são dados temporários gerados e usados pela própria implementação. */
typedef struct {
    /** Arquivo que armazena os registros da tabela. */
    FILE *stream;
    /** Tamanho em bytes de cada registro, calculado a partir dos metadados das colunas (ColumnMeta). */
    size_t regSize;
    /** Última posição segura do cursor, para retornar em caso de erros de leitura ou escrita. */
    fpos_t cursorPos;

    /** Array de registros usada no XML */
    void *arr;
    /** Índice atual na array de registros */
    size_t arrIndex;
    /** Tamanho da array de registros */
    size_t arrSize;
} TableState;

/** As informações da tabela são dados permanentes informados pelo programador e usados para se referir à tabela. */
typedef struct {
    /** Nome da tabela exibido ao usuário. */
    const char *displayName;
    /** Nome da tag XML que armaz   ena a tabela, e o nome (sem extensão) do arquivo da tabela. */
    const char *tagName;
} TableInfo;

/** Os metadados de uma coluna definem como devem ser tratados os dados armazenados nessa coluna. */
typedef struct {
    /** Nome da coluna exibido ao usuário. */
    const char *displayName;
    /** Nome da tag XML que armazena o valor da coluna. */
    const char *tagName;
    /** Tipo do valor da coluna, especifica como deve ser lido e escrito. */
    const int type;
    /** Tamanho em bytes do espaço em memória em que o valor da coluna será armazenado. */
    const size_t size;
    /** Bit flags que indicam algum tratamento especial da coluna. */
    const int flags;
} ColumnMeta;

/** Possíveis valores para o campo type em ColumnMeta. */
#define COL_TYPE_BOOL       0
#define COL_TYPE_CHAR       1
//#define COL_TYPE_UCHAR      2
//#define COL_TYPE_SCHAR      3
#define COL_TYPE_INT        4
#define COL_TYPE_UINT       5
//#define COL_TYPE_SHORT      6
//#define COL_TYPE_USHORT     7
//#define COL_TYPE_LONG       8
//#define COL_TYPE_ULONG      9
#define COL_TYPE_FLOAT     10
#define COL_TYPE_DOUBLE    11
#define COL_TYPE_STRING    12
#define COL_TYPE_DATE      13
#define COL_TYPE_TIME      14
#define COL_TYPE_DATE_TIME 15


/** Possíveis bit flags para o campo flags em ColumnMeta. */
#define COL_FLAG_PRIMARY_KEY    (0b00000101)
#define COL_FLAG_UNIQUE_KEY     (0b00000001)
#define COL_FLAG_AUTO_INCREMENT (0b00001010)
#define COL_FLAG_NOT_NULL       (0b00000100)
#define COL_FLAG_SYS_GENERATED  (0b00001000)
//#define COL_FLAG_LSB4           (0b00010000)
//#define COL_FLAG_LSB5           (0b00100000)
//#define COL_FLAG_LSB6           (0b01000000)
//#define COL_FLAG_LSB7           (0b10000000)

/**
 * Um vetor de ponteiros para structs que armazenam informações sobre a tabela.
 * O primeiro ponteiro deve apontar para uma TableState (inicialmente vazia);
 * O segundo ponteiro deve apontar para uma TableInfo;
 * Os demais ponteiros devem apontar para uma ou mais ColumnMeta;
 * O último ponteiro deve ser NULL para denotar o fim do vetor.
 * @note Table não armazena os registros, mas armazena informações suficientes para interagir com eles.
 */
typedef void *Table[];

/**
 * Uma espécie de interface (POO) para os diferentes tipos de armazenamento (binário ou XML).
 */
typedef struct {
    /**
     * Abre a tabela e posiciona o cursor no início.
     * @param table A tabela a ser aberta.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*open)(Table table);

    /**
     * Fecha a tabela aberta por open().
     * @param table A tabela a ser fechada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*close)(Table table);

    /**
     * Retorna o cursor ao início da tabela.
     * @param table A tabela a ser rebobinada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*rewind)(Table table);

    /**
     * Lê o próximo registro, o armazena na struct e avança o cursor.
     * @param table A tabela a ser lida.
     * @param ptr Ponteiro para a struct onde o registro será armazenado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*next)(Table table, void *ptr);

    /**
     * Deleta o registro anterior ao cursor.
     * @param table A tabela a ser modificada.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*delete)(Table table);

    /**
     * Atualiza o registro anterior ao cursor.
     * @param table A tabela a ser modificada.
     * @param ptr Ponteiro para o registro atualizado.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*update)(Table table, const void *ptr);

    /**
     * Insere um registro na tabela e posiciona o cursor após ele.
     * @param table A tabela a ser modificada.
     * @param ptr Ponteiro para o registro a ser inserido.
     * @return 1 se tiver sucesso, 0 caso contrário.
     */
    int (*insert)(Table table, void *ptr);
} Database;

/** Itera por todos os registros da tabela. */
#define DATABASE_forEach(elementType, elementName, table) \
DATABASE->rewind((table));                                \
for (elementType (elementName); DATABASE->next((table), &(elementName));)

/**
 * Volta ao início da tabela e procura um registro com uma coluna de nome igual a `colName` e valor igual a `colValue`
 * e guarda em `saveHere`.
 * @param colName Nome da coluna que está sendo procurada.
 * @param colValue Ponteiro para o valor que está sendo procurado.
 * @param table A tabela a ser lida.
 * @param saveHere Ponteiro para a struct onde o registro será armazenado.
 * @return 1 ao encontrar, 0 caso contrário.
 */
int DATABASE_findBy(const char *colName, const void *colValue, Table table, void *saveHere);

/** O sistema de banco de dados (binário ou xml) que está sendo usado. */
extern Database *DATABASE;

/** Inicia o banco de dados. @return 1 se tiver sucesso, 0 caso contrário. */
int initDatabase();