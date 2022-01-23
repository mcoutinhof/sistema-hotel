#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"
#include <time.h>

int realizar_entrada() {
    DATABASE->open(Entradas);
    DATABASE->open(Fornecedores);
    DATABASE->open(Produtos);
    DATABASE->open(ItensEntrada);

    unsigned int fornecedor_id = 0;
    float precoTotal, quantidadeTotal;
    struct Entrada entrada = {};
    bool itemSelecionado = false;

    //Seleciona o fornecedor da entrada
    while(!fornecedor_id) {
        char nome[64] = {0};
        int count = 0;

        printf($a "Nome fantasia do fornecedor: ");
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &nome);

        DATABASE_forEach(struct Fornecedor, forn, Fornecedores) {
            if (strcasecmp(forn.nome_fantasia, nome) != 0) continue;

            count++;
            clrscr();
            form(1, Fornecedores, &forn);
            gotoxy(3, wherey() + 2);
            if(menu($f, 2, "Selecionar", "Próximo") == 0) {
                fornecedor_id = forn.id;
                break;
            };
        }
        if(!count) {
            printf($a "Não foram encontrados fornecedores de nome: %s. Por favor, tente novamente! \n", nome);
        } else if(!fornecedor_id) {
            printf($a "Para prosseguir é necessário selecionar um fornecedor. Por favor, tente novamente! \n");
        }
    }
    clrscr();
    printf($a "Frete: ");
    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &entrada.frete);

    clrscr();
    printf($a "Imposto: ");
    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &entrada.imposto);

    entrada.fornecedor_id = fornecedor_id;
    DATABASE->insert(Entradas, &entrada);

    feedback("Na próxima etapa, será necessário selecionar os produtos referentes a esta entrada");

    while(!itemSelecionado) {
        unsigned int count = 0;

        DATABASE_forEach(struct Produto, prod, Produtos) {
            count++;
            clrscr();
            form(1, Produtos, &prod);
            gotoxy(3, wherey() + 2);
            int option = menu($f, 3, "Incluir", "Próximo", "Finalizar entrada");
            if (option == 0) {
                unsigned int quantidade = 0;
                float preco = 0;
                clrscr();

                while(!quantidade) {
                    printf($a "Quantidade: ");
                    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &quantidade);

                    if(!quantidade) printf($a "A quantidade deve ser maior que 0. Por favor, tente novamente! \n");
                }
                while(preco <= 0) {
                    printf($a "Preço de custo: ");
                    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &preco);

                    if(preco <= 0) printf($a "O preço deve ser maior que 0. Por favor, tente novamente! \n");
                }
                struct ItemEntrada item = {};
                item.produto_id = prod.id;
                item.entrada_id = entrada.id;
                item.preco = preco;
                item.quantidade = quantidade;
                DATABASE->insert(ItensEntrada, &item);

                quantidadeTotal += item.quantidade;
                precoTotal += item.quantidade * item.preco;
                    
                itemSelecionado = true;
            } else if(option == 2) break;
        }
        if(!count) {
            DATABASE->delete(Entradas);
            feedback("Nenhum produto cadastrado. Certifique-se de criar ao menos um produto para dar entrada \n");
            return 1;
        } else if(!itemSelecionado) {
            feedback("Nenhum produto selecionado. Certifique-se de incluir ao menos um produto para dar entrada \n");
        }
    }
    float fretePorProduto = entrada.frete / quantidadeTotal, 
          impostoPorProduto = entrada.imposto / quantidadeTotal;

    //Percorre os produtos selecionados atualizando o preço de venda
    DATABASE_forEach(struct ItemEntrada, item, ItensEntrada) {
        if(item.entrada_id != entrada.id) continue;

        struct Produto prod = {};
        if(!DATABASE_findBy("id", &item.produto_id, Produtos, &prod)) continue;

        prod.estoque += item.quantidade;
        prod.preco_venda = (fretePorProduto + impostoPorProduto + item.preco) * 1.05; 
        DATABASE->update(Produtos, &prod);
    }
    realizar_pagamento_entrada(precoTotal, fornecedor_id);

    DATABASE->close(Entradas);
    DATABASE->close(Produtos);
    DATABASE->close(Fornecedores);
    DATABASE->close(ItensEntrada);
}
int realizar_pagamento_entrada(float total, unsigned int fornecedor_id) {
    DATABASE->open(Caixas);
    DATABASE->open(ContasPagar);

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    struct Caixa caixa = {};
    caixa.hotel_id = 1;
    strcpy(caixa.natureza, "Débito");
    caixa.data = (tm.tm_year + 1900) * 4 + (tm.tm_mon + 1) * 2 + tm.tm_mday;

    clrscr();
    printf($a "Como deseja realizar o pagamento?  \n");
    int payment = menu($f, 2, "A vista", "Parcelado");

    if(payment == 1) {
        unsigned int numParcelas = 0;
        float entradaPagamento = 0, valorParcela = 0;

        clrscr();
        printf($a "Número de parcelas: ");
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &numParcelas);

        while(entradaPagamento <= 0 || entradaPagamento > total) {
            printf($a "Valor de entrada: ");
            readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &entradaPagamento);

            if(entradaPagamento < 0) 
                printf($a "O valor de entrada deve ser maior ou igual a zero \n");
            else if(entradaPagamento > total)
                printf($a "O valor de entrada deve ser menor ou igual a: %f \n", total);
        }

        if(entradaPagamento > 0) {
            caixa.valor = entradaPagamento;
            strcpy(caixa.descricao, "Valor de entrada de pagamento parcelado no reestoque de produtos de consumo");
            DATABASE->insert(Caixas, &caixa);
        }
        float valorParcela = (total - entradaPagamento) / numParcelas;

        for(int i = 0; i < numParcelas; i++) {
            struct ContaPagar conta = {};
            conta.fornecedor_id = fornecedor_id;
            conta.hotel_id = 1;
            conta.valor_parcela = valorParcela;
            conta.num_parcela = i + 1;
            DATABASE->insert(ContasPagar, &conta);
        }
    } else  {
        caixa.valor = total;
        strcpy(caixa.descricao, "Entrada de produtos de consumo com pagamento a vista");
        DATABASE->insert(Caixas, &caixa);
    }

    DATABASE->close(Caixas);
    DATABASE->close(ContasPagar);
}