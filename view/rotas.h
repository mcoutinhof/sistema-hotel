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

//###RELATÓRIOS

// principal -> relatorios 
int menu_relatorios();

// principal -> relatorios -> hospede
int relatorio_hospedes();

// principal -> relatorios -> acomodacoes
int relatorio_acomodacoes();

// principal -> relatorios -> reservas
int relatorio_reservas();
