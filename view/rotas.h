/**
 * @authors Ryan W. Fonseca & Arthur Gomes.
 */

#pragma once

/** 1 se o usuário logado tem permissões de administração, 0 caso contrário. */
extern int isAdmin;

// Ao iniciar
int logar_operador();

// main -> principal
int menu_principal();

// principal -> cadastros
int menu_cadastros();

// principal -> cadastros -> ver
int menu_ver();

// principal -> cadastros -> inserir
int menu_inserir();

//###HOSPEDE

// principal -> cadastro -> hospede -> cadastrar_hospede
int cadastrar_hospede();

// principal -> cadastro -> hospede -> ver_hospede
int ver_hospede();

//###HOTEL

// principal -> cadastro -> hotel -> cadastrar_hotel
int cadastrar_hotel();

// principal -> cadastro -> hotel -> ver_hotel
int ver_hotel();

//###CATEGORIA

// principal -> cadastro -> categoria -> cadastrar_categoria
int cadastrar_categoria();

// principal -> cadastro -> categoria -> ver_categoria
int ver_categoria();

//###OPERADOR

// principal -> cadastro -> operador -> cadastrar_operador
int cadastrar_operador();

// principal -> cadastro -> operador -> ver_operador
int ver_operador();

//###ACOMODACAO

// principal -> cadastro -> acomodacao -> cadastrar_acomodacao
int cadastrar_acomodacao();

// principal -> cadastro -> acomodacao -> ver_acomodacao
int ver_acomodacao();

//###PRODUTO

// principal -> cadastro -> produto -> cadastrar_produto
int cadastrar_produto();

// principal -> cadastro -> produto -> ver_produto
int ver_produto();

//###FORNECEDOR

// principal -> cadastro -> fornecedor -> cadastrar_fornecedor
int cadastrar_fornecedor();

// principal -> cadastro -> fornecedor -> ver_fornecedor
int ver_fornecedor();

//###RESERVA

// principal -> reserva
int menu_reservas();

// principal -> reserva -> cadastrar_reserva
int cadastrar_reserva();

// principal -> reserva -> ver_reserva
int ver_reserva();

//###VENDA

// principal -> vendas
int menu_vendas();

// principal -> vendas -> realizar_venda
int realizar_venda();

// principal -> vendas -> ver_venda
int ver_venda();

// principal -> vendas -> realizar_pagamento_venda
int realizar_pagamento_venda(float total, unsigned int hospede_id, int payment);

// principal -> entrada -> baixar_nota_venda
int baixar_nota_venda();

//###ENTRADA

// principal -> entrada
int menu_entradas();

// principal -> entrada -> realizar_entrada
int realizar_entrada();

// principal -> vendas -> ver_entrada
int ver_entrada();

// entradas.c
int realizar_pagamento_entrada(float total, unsigned int fornecedor_id);

// principal -> entrada -> baixar_nota_entrada
int baixar_nota_entrada();


//###RELATÓRIOS

// principal -> relatorios 
int menu_relatorios();

// principal -> relatorios -> hospede
int relatorio_hospedes(char *path);

// principal -> relatorios -> acomodacoes
int relatorio_acomodacoes(char *path);

// principal -> relatorios -> movimentacao_acomodacoes
int relatorio_movimentacao_acomodacoes(char *path);

// principal -> relatorios -> reservas
int relatorio_reservas(char *path);

// principal -> relatorios -> produtos
int relatorio_produtos(char *path);

// principal -> relatorios -> produtos
int relatorio_caixas(char *path);

// principal -> relatorios -> contas_pagar
int relatorio_contas_pagar(char *path);

// principal -> relatorios -> contas_receber
int relatorio_contas_receber(char *path);

// principal -> relatorios -> relatorio_vendas
int relatorio_vendas(char *path);

// principal -> check_in_out
int check_in_out(int operation);
