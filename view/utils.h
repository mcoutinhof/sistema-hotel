/**
 * @author Mateus Coutinho
 */

#pragma once

#include "../model/database.h"

/**
 * Mostra um formulário com campos de acordo com os metadados das colunas da tabela.
 * @param mode 0 = inserir, 1 = visualizar, 2 = editar.
 * @param table A tabela que contém as colunas.
 * @param ptr Ponteiro para a struct de onde os dados serão lidos e/ou onde os dados serão armazenados.
 */
void form(int mode, const Table table, void *ptr);

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