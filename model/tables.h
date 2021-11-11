#pragma once

#include <stdbool.h>

struct Hotel {
    unsigned int id; // 0 a 4294967295
    char nome_fantasia[64];
    char razao_social[64];
    char inscricao_estadual[20]; // Cada estado tem seu padrão
    char cnpj[20]; // 00.000.000/0000-00
    char endereco[256];
    char telefone[20];
    char email[256];
    char nome_responsavel[64];
    char telefone_responsavel[20];
    char check_in[16]; // 14:00:00
    char check_out[16]; // 12:00:00
    float margem_lucro; // 60.000 (%)
};

struct Hospede {
    unsigned int id; // 0 a 4294967295
    char nome[64];
    char endereco[256];
    char cpf[16]; // 000.000.000-00
    char telefone[20];
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
    float preco_custo;
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
    char telefone[20];
    char email[256];
};

struct Funcionario {
    unsigned int id; // 0 a 4294967295
    char nome[64];
    char usuario[20];
    char senha[20];
    char funcao[64];
    unsigned int hotel_id; // 0 a 4294967295
};

struct Reserva {
    unsigned int id; // 0 a 4294967295
    char metodo_pagamento[64];
    char data_inicial[16]; // 01/01/1970
    char data_final[16]; // 01/01/1970
    unsigned int periodo; // 0 a 4294967295
    bool check_in; // true ou false
    bool check_out; // true ou false
    unsigned int acomodacao_id; // 0 a 4294967295
    unsigned int hospede_id; // 0 a 4294967295
};