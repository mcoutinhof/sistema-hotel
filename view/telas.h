#pragma once

// main -> principal
int menu_principal();

// principal -> cadastros
int menu_cadastros();

/*ORDEM 
Hospedes --- e logo em seguida tudo relacionado com ele
hotel
Categoria de acomodação
Operadores
Acomodações
Produtos
Fornecedores
*/

//###HOSPEDE

// principal -> cadastros -> hospedes
int menu_hospedes();

// principal -> cadastro -> hospede -> cadastrar_hospede
int cadastrar_hospede();

// principal -> cadastro -> hospede -> ver_hospede
int ver_hospede();

//###HOTEL

// principal -> cadastros -> hotel
int menu_hotel();

// principal -> cadastro -> hotel -> cadastrar_hotel
int cadastrar_hotel();

// principal -> cadastro -> hotel -> ver_hotel
//int ver_hotel();

//###CATEGORIA

// principal -> cadastros -> categoria
int menu_categoria();

// principal -> cadastro -> categoria -> cadastrar_categoria
int cadastrar_categoria();

// principal -> cadastro -> categoria -> ver_categoria
//int ver_categoria();

//###ACOMODACAO

// principal -> cadastros -> acomodacao
int menu_acomodacao();

// principal -> cadastro -> acomodacao -> cadastrar_acomodacao
int cadastrar_acomodacao();

// principal -> cadastro -> acomodacao -> ver_acomodacao
//int ver_acomodacao();

//###PRODUTO

// principal -> cadastros -> produto
//int menu_produto();

// principal -> cadastro -> produto -> cadastrar_produto
//int cadastrar_produto();

// principal -> cadastro -> produto -> ver_produto
//int ver_produto();

//###FORNECEDOR

// principal -> cadastros -> fornecedor
//int menu_fornecedor();

// principal -> cadastro -> fornecedor -> cadastrar_fornecedor
//int cadastrar_forncedor();

// principal -> cadastro -> fornecedor -> ver_fornecedor
//int ver_forncedor();
