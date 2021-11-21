#pragma once

#include "../model/database.h"

/**
 * Mostra um formulário de acordo com os campos de uma tabela.
 * @param mode 0 = inserir, 1 = visualizar, 2 = editar.
 * @param table A tabela que contém os campos.
 * @param ptr Ponteiro para a struct onde os dados serão armazenados.
 * @example <code>form(0, Hospedes, &hosp);</code>
 * @return 1 se tiver sucesso, 0 caso contrário.
 */
int form(int mode, const Table table, void *ptr);

/**
 * @param nitems Quantidade de itens do menu.
 * @param ... Strings contendo os nomes dos itens.
 * @example <code>menu(">>", 3, "Item zero", "Item um", "Item dois");</code>
 * @return Retorna o índice do item selecionado pelo usuário.
 */
int menu(int nitems, ...);