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
} TableState;

/** As informações da tabela são dados permanentes informados pelo programador e usados para se referir à tabela. */
typedef struct {
    /** Nome da tabela exibido ao usuário. */
    const char *displayName;
    /** Nome da tag XML que armazena a tabela. */
    const char *tagName;
    /** Caminho para o arquivo que armazena a tabela. */
    const char *fileName;
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
    const char flags;
} ColumnMeta;

/** Possíveis valores para o campo type em ColumnMeta. */
#define COL_TYPE_BOOL   0
#define COL_TYPE_CHAR   1
//#define COL_TYPE_UCHAR  2
//#define COL_TYPE_SCHAR  3
#define COL_TYPE_INT    4
#define COL_TYPE_UINT   5
//#define COL_TYPE_SHORT  6
//#define COL_TYPE_USHORT 7
//#define COL_TYPE_LONG   8
//#define COL_TYPE_ULONG  9
#define COL_TYPE_FLOAT  10
#define COL_TYPE_DOUBLE 11
#define COL_TYPE_STRING 12


/** Possíveis bit flags para o campo flags em ColumnMeta. */
#define COL_FLAG_PRIMARY_KEY    (0b00000101) // 00000101
#define COL_FLAG_UNIQUE_KEY     (0b00000001) // 00000001
#define COL_FLAG_AUTO_INCREMENT (0b00001010) // 00001010
#define COL_FLAG_NOT_NULL       (0b00000100) // 00000100
#define COL_FLAG_SYS_GENERATED  (0b00001000) // 00001000
//#define COL_FLAG_LSB4           (0b00010000) // 00010000
//#define COL_FLAG_LSB5           (0b00100000) // 00100000
//#define COL_FLAG_LSB6           (0b01000000) // 01000000
//#define COL_FLAG_LSB7           (0b10000000) // 10000000