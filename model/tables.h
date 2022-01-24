/**
 * @authors Mateus Coutinho, Ryan W. Fonseca & Arthur Gomes.
 */

#pragma once

#include "database.h"
#include <stdbool.h>

struct Hotel {
    unsigned int id; // 0 a 4294967295
    char nome_fantasia[64];
    char razao_social[64];
    char inscricao_estadual[20]; // Cada estado tem seu padrão
    char cnpj[20]; // 00.000.000/0000-00
    char endereco[256];
    char telefone[24];
    char email[256];
    char nome_responsavel[64];
    char telefone_responsavel[24];
    char check_in[16]; // 14:00:00
    char check_out[16]; // 12:00:00
    float margem_lucro; // 60.000 (%)
};

struct Hospede {
    unsigned int id; // 0 a 4294967295
    char nome[64];
    char endereco[256];
    char cpf[16]; // 000.000.000-00
    char telefone[24];
    char email[256];
    char sexo[16]; // Masculino, Feminino
    char estado_civil[16]; // Solteiro, Casado, Divorciado ou Viúvo
    char nascimento[16]; // 01/01/1970
    unsigned int hotel_id; // 0 a 4294967295
};

struct Acomodacao {
    unsigned int id; // 0 a 4294967295
    char titulo[64];
    char descricao[512];
    char facilidades[512];
    unsigned int categoria_id; // 0 a 4294967295
    unsigned int hotel_id; // 0 a 4294967295
};

struct Categoria {
    unsigned int id; // 0 a 4294967295
    char titulo[64];
    char descricao[512];
    float valor_diaria;
    unsigned int lotacao; // 0 a 4294967295
    unsigned int hotel_id; // 0 a 4294967295
};

struct Produto {
    unsigned int id; // 0 a 4294967295
    char nome[64];
    char descricao[512];
    unsigned int estoque; // 0 a 4294967295
    unsigned int estoque_minimo; // 0 a 4294967295
    float preco_venda;
    unsigned int fornecedor_id; // 0 a 4294967295
    unsigned int hotel_id; // 0 a 4294967295
};

struct Fornecedor {
    unsigned int id; // 0 a 4294967295
    char nome_fantasia[64];
    char razao_social[64];
    char inscricao_estadual[20]; // Cada estado tem seu padrão
    char cnpj[20]; // 00.000.000/0000-00
    char endereco[256];
    char telefone[24];
    char email[256];
};

struct Operador {
    unsigned int id; // 0 a 4294967295
    char nome[64];
    char usuario[20];
    char senha[20];
    char funcao[64];
    unsigned int hotel_id; // 0 a 4294967295
};

struct Reserva {
    unsigned int id; // 0 a 4294967295
    unsigned int data_inicial; // YYYYMMDD
    unsigned int data_final; // YYYYMMDD
    unsigned int periodo; // 0 a 4294967295
    unsigned int check_in; // 1 (true) ou 0 (false)
    unsigned int check_out; // 1 (true) ou 0 (false)
    unsigned int pago;
    unsigned int acomodacao_id; // 0 a 4294967295
    unsigned int hospede_id; // 0 a 4294967295
};

struct Venda {
    unsigned int id; // 0 a 4294967295
    float total;
    char metodo_pagamento[64];
    unsigned int hospede_id; // 0 a 4294967295
};

struct ItemVenda {
    unsigned int id; // 0 a 4294967295
    unsigned int produto_id;
    unsigned int venda_id;
    float preco;
    unsigned int quantidade; // YYYYMMDD
};

struct Comanda {
    unsigned int id; // 0 a 4294967295
    unsigned int produto_id;
    unsigned int hospede_id;
    float preco;
    unsigned int quantidade; // YYYYMMDD
};

struct Entrada {
    unsigned int id; // 0 a 4294967295
    unsigned int fornecedor_id;
    float frete;
    float imposto;
};

struct ItemEntrada {
    unsigned int id; // 0 a 4294967295
    unsigned int produto_id;
    unsigned int entrada_id;
    float preco;
    unsigned int quantidade; // YYYYMMDD
};

struct ContaPagar {
    unsigned int id; // 0 a 4294967295
    unsigned int fornecedor_id;
    unsigned int hotel_id;
    float valor_parcela;
    unsigned int num_parcela;
    unsigned int data_vencimento; // YYYYMMDD
    unsigned int pago;
};

struct ContaReceber {
    unsigned int id; // 0 a 4294967295
    unsigned int hospede_id;
    unsigned int hotel_id;
    float valor_parcela;
    unsigned int num_parcela;
    unsigned int data_recebimento; // YYYYMMDD
    unsigned int data_vencimento; // YYYYMMDD
    unsigned int pago;
};

struct Caixa {
    unsigned int id; // 0 a 4294967295
    unsigned int hotel_id;
    float valor;
    char descricao[512];
    char natureza[16];
    unsigned int data; // YYYYMMDD
};

extern Table Hoteis;
extern Table Hospedes;
extern Table Acomodacoes;
extern Table Categorias;
extern Table Produtos;
extern Table Fornecedores;
extern Table Operadores;
extern Table Reservas;
extern Table Vendas;
extern Table ItensVenda;
extern Table Comandas;
extern Table Entradas;
extern Table ItensEntrada;
extern Table ContasPagar;
extern Table ContasReceber;
extern Table Caixas;
