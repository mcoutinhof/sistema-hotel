/**
 * @author Mateus Coutinho
 */

#include "tables.h"

Table Hoteis = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Hotel", .tagName = "hotel"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
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

Table Hospedes = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Hóspede", .tagName = "hospede"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome completo", .tagName = "nome", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "CPF", .tagName = "cpf", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .type = COL_TYPE_STRING, .size = 24},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "Sexo", .tagName = "sexo", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Estado civil", .tagName = "estado_civil", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Data de nascimento", .tagName = "nascimento", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        NULL
};

Table Acomodacoes = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Acomodação", .tagName = "acomodacao"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Título", .tagName = "titulo", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Facilidades", .tagName = "facilidades", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "ID da categoria", .tagName = "categoria_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        NULL
};

Table Categorias = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Categoria de acomodação", .tagName = "categoria"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Título", .tagName = "titulo", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Valor da diária", .tagName = "valor_diaria", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Lotação máxima", .tagName = "lotacao", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        NULL
};

Table Produtos = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Produtos disponíveis para consumo dos hóspedes", .tagName = "produto"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome", .tagName = "nome", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Estoque", .tagName = "estoque", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Estoque mínimo", .tagName = "estoque_minimo", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        //&(ColumnMeta) {.displayName = "Preço de custo", .tagName = "preco_custo", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Preço de venda", .tagName = "preco_venda", .type = COL_TYPE_FLOAT, .size = sizeof(float), .flags = COL_FLAG_SYS_GENERATED},
        &(ColumnMeta) {.displayName = "ID do fornecedor", .tagName = "fornecedor_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        NULL
};

Table Fornecedores = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Fornecedor", .tagName = "fornecedor"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome fantasia", .tagName = "nome_fantasia", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Razão social", .tagName = "razao_social", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Inscrição estadual", .tagName = "inscricao_estadual", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "CNPJ", .tagName = "cnpj", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Endereço completo", .tagName = "endereco", .type = COL_TYPE_STRING, .size = 256},
        &(ColumnMeta) {.displayName = "Telefone", .tagName = "telefone", .type = COL_TYPE_STRING, .size = 24},
        &(ColumnMeta) {.displayName = "E-mail", .tagName = "email", .type = COL_TYPE_STRING, .size = 256},
        NULL
};

Table Operadores = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Operador do sistema", .tagName = "operador"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Nome", .tagName = "nome", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "Usuário", .tagName = "usuario", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Senha", .tagName = "senha", .type = COL_TYPE_STRING, .size = 20},
        &(ColumnMeta) {.displayName = "Função", .tagName = "funcao", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        NULL
};

Table Reservas = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Reserva", .tagName = "reserva"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Data inicial", .tagName = "data_inicial", .type = COL_TYPE_DATE, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Data final", .tagName = "data_final", .type = COL_TYPE_DATE, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Período", .tagName = "periodo", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Check-in", .tagName = "check_in", .type = COL_TYPE_BOOL, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        &(ColumnMeta) {.displayName = "Check-out", .tagName = "check_out", .type = COL_TYPE_BOOL, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        &(ColumnMeta) {.displayName = "Pago", .tagName = "pago", .type = COL_TYPE_BOOL, .size = sizeof(unsigned int), .flags = COL_FLAG_SYS_GENERATED},
        &(ColumnMeta) {.displayName = "ID da acomodação", .tagName = "acomodacao_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hóspede", .tagName = "hospede_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

Table Vendas = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Venda", .tagName = "venda"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "Total", .tagName = "total", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Método de pagamento", .tagName = "metodo_pagamento", .type = COL_TYPE_STRING, .size = 64},
        &(ColumnMeta) {.displayName = "ID do hóspede", .tagName = "hospede_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

Table ItensVenda = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Itens da venda", .tagName = "itensVenda"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do produto", .tagName = "produto_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID da venda", .tagName = "venda_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Preço", .tagName = "preco", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Quantidade", .tagName = "quantidade", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

Table Comandas = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Comanda", .tagName = "comanda"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do produto", .tagName = "produto_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hóspede", .tagName = "hospede_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Preço", .tagName = "preco", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Quantidade", .tagName = "quantidade", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

Table Entradas = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Entrada", .tagName = "entrada"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do fornecedor", .tagName = "fornecedor_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Frete", .tagName = "frete", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Imposto", .tagName = "imposto", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        NULL
};

Table ItensEntrada = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Item de entrada", .tagName = "itemEntrada"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do produto", .tagName = "produto_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID da entrada", .tagName = "entrada_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Preço", .tagName = "preco", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Quantidade", .tagName = "quantidade", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        NULL
};

Table ContasPagar = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Contas a pagar", .tagName = "contaPagar"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do fornecedor", .tagName = "fornecedor_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Valor da parcela", .tagName = "valor_parcela", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Número da parcela", .tagName = "num_parcela", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Data de vencimento", .tagName = "data_vencimento", .type = COL_TYPE_DATE, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Pago", .tagName = "pago", .type = COL_TYPE_BOOL, .size = sizeof(unsigned int)},
        NULL
};

Table ContasReceber = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Contas a receber", .tagName = "contaReceber"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do hospede", .tagName = "hospede_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Valor da parcela", .tagName = "valor_parcela", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Número da parcela", .tagName = "num_parcela", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Data de recebimento", .tagName = "data_recebimento", .type = COL_TYPE_DATE, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Data de vencimento", .tagName = "data_vencimento", .type = COL_TYPE_DATE, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Pago", .tagName = "pago", .type = COL_TYPE_BOOL, .size = sizeof(unsigned int)},
        NULL
};

Table Caixas = {
        &(TableState) {},
        &(TableInfo) {.displayName = "Caixa", .tagName = "caixa"},
        &(ColumnMeta) {.displayName = "ID", .tagName = "id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int), .flags =
        COL_FLAG_PRIMARY_KEY | COL_FLAG_AUTO_INCREMENT},
        &(ColumnMeta) {.displayName = "ID do hotel", .tagName = "hotel_id", .type = COL_TYPE_UINT, .size = sizeof(unsigned int)},
        &(ColumnMeta) {.displayName = "Valor", .tagName = "valor", .type = COL_TYPE_FLOAT, .size = sizeof(float)},
        &(ColumnMeta) {.displayName = "Descrição", .tagName = "descricao", .type = COL_TYPE_STRING, .size = 512},
        &(ColumnMeta) {.displayName = "Natureza", .tagName = "natureza", .type = COL_TYPE_STRING, .size = 16},
        &(ColumnMeta) {.displayName = "Data", .tagName = "data", .type = COL_TYPE_DATE, .size = sizeof(unsigned int)},
        NULL
};