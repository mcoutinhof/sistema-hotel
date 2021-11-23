#include "tables.h"
#include "database_local.h"

const Table Hoteis = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Hotel", .tagName = "hotel", .fileName = "hotel.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome fantasia", .tagName = "nome_fantasia", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Razão social", .tagName = "razao_social", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Inscrição estadual", .tagName = "inscricao_estadual", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "CNPJ", .tagName = "cnpj", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .type = COL_TYPE_STRING, .size = 24},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "Nome do responsável", .tagName = "nome_responsavel", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Telefone do responsável", .tagName = "telefone_responsavel", .type = COL_TYPE_STRING, .size = 24},
        &(ColumnMeta) {.displayName = "Horário de check-in", .tagName = "check_in", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Horário de check-out", .tagName = "check_out", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Margem de lucro de produtos vendidos", .tagName = "margem_lucro", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        NULL
};

const Table Hospedes = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Hóspede", .tagName = "hospede", .fileName = "hospede.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome completo", .tagName = "nome", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "CPF", .tagName = "cpf", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .type = COL_TYPE_STRING, .size = 24},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "Sexo", .tagName = "sexo", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Estado civil", .tagName = "estado_civil", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Data de nascimento", .tagName = "nascimento", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

const Table Acomodacoes = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Acomodação", .tagName = "acomodacao", .fileName = "acomodacao.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Título", .tagName = "titulo", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Facilidades", .tagName = "facilidades", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "ID da categoria", .tagName = "categoria_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

const Table Categorias = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Categoria de acomodação", .tagName = "categoria", .fileName = "categoria.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Título", .tagName = "titulo", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Valor da diária", .tagName = "valor_diaria", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Lotação máxima", .tagName = "lotacao", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

const Table Produtos = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Produtos disponíveis para consumo dos hóspedes", .tagName = "produto", .fileName = "produto.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome", .tagName = "nome", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Estoque", .tagName = "estoque", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Estoque mínimo", .tagName = "estoque_minimo", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Preço de custo", .tagName = "preco_custo", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Preço de venda", .tagName = "preco_venda", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "ID do fornecedor", .tagName = "fornecedor_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

const Table Fornecedores = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Fornecedor", .tagName = "fornecedor", .fileName = "fornecedor.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome fantasia", .tagName = "nome_fantasia", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Razão social", .tagName = "razao_social", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Inscrição estadual", .tagName = "inscricao_estadual", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "CNPJ", .tagName = "cnpj", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .type = COL_TYPE_STRING, .size = 24},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .type = COL_TYPE_STRING, .size = 256},
        NULL
};

const Table Operadores = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Operador do sistema", .tagName = "operador", .fileName = "operador.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome", .tagName = "nome", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Usuário", .tagName = "usuario", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Senha", .tagName = "senha", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Função", .tagName = "funcao", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

const Table Reservas = {
        &(TableState) {},
        &(TableInfo)  {.displayName = "Reserva", .tagName = "reserva", .fileName = "reserva.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Método de pagamento", .tagName = "metodo_pagamento", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Data inicial", .tagName = "data_inicial", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Data final", .tagName = "data_final", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Período", .tagName = "periodo", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Check-in", .tagName = "check_in", .type = COL_TYPE_BOOL, .size = sizeof(bool)},
        &(ColumnMeta) {.displayName = "Check-out", .tagName = "check_out", .type = COL_TYPE_BOOL, .size = sizeof(bool)},
        &(ColumnMeta) {.displayName = "ID da acomodação", .tagName = "acomodacao_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hóspede", .tagName = "hospede_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};