/**
 * @author Mateus Coutinho
 */

#pragma once

#include "../model/database.h"
#include <stdbool.h>

/**
 * Escreve um valor de acordo com os metadados da coluna a qual ele pertence.
 * @param stream Stream onde o valor será escrito.
 * @param colMeta Metadados da coluna a qual tal valor pertence.
 * @param ptr Ponteiro para a variável de onde o valor será lido.
 * @return a quantidade de caracteres impressos.
 */
int printVal(FILE *stream, const ColumnMeta *colMeta, const void *ptr);

/**
 * Lê um valor de acordo com os metadados da coluna a qual ele pertence.
 * @param stream Stream de onde o valor será escrito.
 * @param delimiter Caractere que delimita até quando ler a stream.
 * @param colMeta Metadados da coluna a qual tal valor pertence.
 * @param ptr Ponteiro para a variável onde o valor será armazenado.
 * @return 1 se conseguir ler um valor válido, 0 caso contrário.
 */
int readVal(FILE *stream, int delimiter, const ColumnMeta *colMeta, void *ptr);

/**
 * Mostra um formulário com campos de acordo com os metadados das colunas da tabela.
 * @param mode 0 = inserir, 1 = visualizar, 2 = editar.
 * @param table A tabela que contém as colunas.
 * @param ptr Ponteiro para a struct de onde os dados serão lidos e/ou onde os dados serão armazenados.
 *
 */
bool *form(int mode, const Table table, void *ptr);

/**
 * Mostra um menu com n itens, permite ao usuário navegar pressionando TAB e selecionar um item pressionando ENTER.
 * @param prefix O que é impresso antes do nome de cada item.
 * @param nitems Número de itens do menu.
 * @param ... Strings contendo o nome de cada item.
 * @return o índice do item selecionado pelo usuário.
 */
int menu(const char *prefix, int nitems, ...);

/** Mostra uma mensagem e retorna quando o usuário pressionar uma tecla. */
void alert(const char *message);

void feedback(const char *message);

unsigned int current_date();

/**
 * @param table A tabela que contém as colunas.
 * @param oneReg Um registro a ser comparado.
 * @param otherReg Outro registro a ser comparado.
 * @param fieldsToFilter Quais campos comparar.
 * @return 1 se os campos selecionados de um registro são iguais aos de outro, 0 caso contrário.
 */
int compareFields(const Table table, void *oneReg, void *otherReg,  bool *fieldsToFilter);