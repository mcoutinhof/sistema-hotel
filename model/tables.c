#include "database.h"

const Table Hotel = {
        &(TableState) {},
        &(TableInfo)  {.filename = "hotel.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Nome fantasia", .tagName = "nome_fantasia", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Razão social", .tagName = "razao_social", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Inscrição estadual", .tagName = "inscricao_estadual", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "CNPJ", .tagName = "cnpj", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .format = "%[^\n]", .size = 256},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .format = "%[^\n]", .size = 256},
        &(ColumnMeta) {.displayName = "Nome do responsável", .tagName = "nome_responsavel", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Telefone do responsável", .tagName = "telefone_responsavel", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "Horário de check-in", .tagName = "check_in", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Horário de check-out", .tagName = "check_out", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Margem de lucro de produtos vendidos", .tagName = "margem_lucro", .format = "%f", .size = sizeof(float)},
        NULL
};

const Table Hospede = {
        &(TableState) {},
        &(TableInfo)  {.filename = "hospede.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Nome completo", .tagName = "nome", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .format = "%[^\n]", .size = 256},
        &(ColumnMeta) {.displayName = "CPF", .tagName = "cpf", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .format = "%[^\n]", .size = 256},
        &(ColumnMeta) {.displayName = "Sexo", .tagName = "sexo", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Estado civil", .tagName = "estado_civil", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Data de nascimento", .tagName = "nascimento", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .format = "%u", .size = sizeof(unsigned int)},
        NULL
};

const Table Acomodacao = {
        &(TableState) {},
        &(TableInfo)  {.filename = "acomodacao.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Título", .tagName = "titulo", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .format = "%[^\n]", .size = 512},
        &(ColumnMeta) {.displayName = "Facilidades", .tagName = "facilidades", .format = "%[^\n]", .size = 512},
        &(ColumnMeta) {.displayName = "ID da categoria", .tagName = "categoria_id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .format = "%u", .size = sizeof(unsigned int)},
        NULL
};

const Table Categoria = {
        &(TableState) {},
        &(TableInfo)  {.filename = "categoria.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Título", .tagName = "titulo", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .format = "%[^\n]", .size = 512},
        &(ColumnMeta) {.displayName = "Valor da diária", .tagName = "valor_diaria", .format = "%f", .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Lotação máxima", .tagName = "lotacao", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .format = "%u", .size = sizeof(unsigned int)},
        NULL
};

const Table Produto = {
        &(TableState) {},
        &(TableInfo)  {.filename = "produto.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Nome", .tagName = "nome", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .format = "%[^\n]", .size = 512},
        &(ColumnMeta) {.displayName = "Estoque", .tagName = "estoque", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Estoque mínimo", .tagName = "estoque_minimo", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Preço de custo", .tagName = "preco_custo", .format = "%f", .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Preço de venda", .tagName = "preco_venda", .format = "%f", .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "ID do fornecedor", .tagName = "fornecedor_id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .format = "%u", .size = sizeof(unsigned int)},
        NULL
};

const Table Fornecedor = {
        &(TableState) {},
        &(TableInfo)  {.filename = "fornecedor.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Nome fantasia", .tagName = "nome_fantasia", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Razão social", .tagName = "razao_social", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Inscrição estadual", .tagName = "inscricao_estadual", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "CNPJ", .tagName = "cnpj", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .format = "%[^\n]", .size = 256},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .format = "%[^\n]", .size = 256},
        NULL
};

const Table Funcionario = {
        &(TableState) {},
        &(TableInfo)  {.filename = "funcionario.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Nome", .tagName = "nome", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Usuário", .tagName = "usuario", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "Senha", .tagName = "senha", .format = "%[^\n]", .size = 20},
        &(ColumnMeta) {.displayName = "Função", .tagName = "funcao", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .format = "%u", .size = sizeof(unsigned int)},
        NULL
};

const Table Reserva = {
        &(TableState) {},
        &(TableInfo)  {.filename = "reserva.dat"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Método de pagamento", .tagName = "metodo_pagamento", .format = "%[^\n]", .size = 64},
        &(ColumnMeta) {.displayName = "Data inicial", .tagName = "data_inicial", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Data final", .tagName = "data_final", .format = "%[^\n]", .size = 16},
        &(ColumnMeta) {.displayName = "Período", .tagName = "periodo", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Check-in", .tagName = "check_in", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Check-out", .tagName = "check_out", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID da acomodação", .tagName = "acomodacao_id", .format = "%u", .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hóspede", .tagName = "hospede_id", .format = "%u", .size = sizeof(unsigned int)},
        NULL
};