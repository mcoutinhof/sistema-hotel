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
    int itemSelecionado = false, achouFornecedor = false;

    clrscr();

    //Seleciona o fornecedor da entrada
    while(!achouFornecedor) {
        char nome[64] = {0};
        int count = 0;

        printf($a "\nNome fantasia do fornecedor: ");
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &nome);

        DATABASE_forEach(struct Fornecedor, forn, Fornecedores) {
            if (strcasecmp(forn.nome_fantasia, nome) != 0) continue;

            count++;
            clrscr();
            form(1, Fornecedores, &forn);
            gotoxy(3, wherey() + 2);
            if(menu($f, 2, "Selecionar", "Próximo") == 0) {
                achouFornecedor = true;
                fornecedor_id = forn.id;
                break;
            };
        }
        if(!count) {
            printf($a "Não foram encontrados fornecedores de nome: %s. Por favor, tente novamente! \n", nome);
        } else if(!achouFornecedor) {
            printf($a "Para prosseguir é necessário selecionar um fornecedor. Por favor, tente novamente! \n");
        }
    }
    clrscr();
    printf($a "Frete: ");
    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &entrada.frete);

    printf($a "Imposto: ");
    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &entrada.imposto);

    entrada.fornecedor_id = fornecedor_id;
    DATABASE->insert(Entradas, &entrada);

    clrscr();
    feedback("Na próxima etapa, será necessário selecionar os produtos referentes a esta entrada\n");

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
                    printf($a "Preço de custo unitário: ");
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
    DATABASE_forEach(struct ItemEntrada, item2, ItensEntrada) {
        if(item2.entrada_id != entrada.id) continue;

        struct Produto prod2 = {};
        if(!DATABASE_findBy("id", &item2.produto_id, Produtos, &prod2)) continue;

        prod2.estoque += item2.quantidade;

        prod2.preco_venda = (fretePorProduto + impostoPorProduto + item2.preco) * 1.05f;
        DATABASE->update(Produtos, &prod2);
    }
    realizar_pagamento_entrada(precoTotal, fornecedor_id);

    DATABASE->close(Entradas);
    DATABASE->close(Produtos);
    DATABASE->close(Fornecedores);
    DATABASE->close(ItensEntrada);
}
int ver_entrada() {
    DATABASE->open(Entradas);

    DATABASE_forEach(struct Entrada, entrada, Entradas) {
        clrscr();
        form(1, Entradas, &entrada);
        gotoxy(3, wherey() + 2);
        if (menu($f, 2, "Próximo", "Sair") == 1) break;
    }
    DATABASE->close(Entradas);
}
int realizar_pagamento_entrada(float total, unsigned int fornecedor_id) {
    DATABASE->open(Caixas);
    DATABASE->open(ContasPagar);

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    int day = tm.tm_mday, month = (tm.tm_mon + 1), year = (tm.tm_year + 1900);

    struct Caixa caixa = {};
    caixa.hotel_id = 1;
    strcpy(caixa.natureza, "Débito");
    caixa.data = year * 10000 + month * 100 + day;

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
        valorParcela = (total - entradaPagamento) / numParcelas;

        for(int i = 0; i < numParcelas; i++) {
            month++;
            if(month > 12) {
                year++;
                month = 1;
            }
            struct ContaPagar conta = {};
            conta.fornecedor_id = fornecedor_id;
            conta.hotel_id = 1;
            conta.valor_parcela = valorParcela;
            conta.num_parcela = i + 1;
            conta.pago = 0;
            conta.data_vencimento = year * 10000 + month * 100 + day;
            DATABASE->insert(ContasPagar, &conta);
        }
    } else  {
        caixa.valor = total;
        strcpy(caixa.descricao, "Entrada de produtos de consumo com pagamento a vista");
        DATABASE->insert(Caixas, &caixa);
    }

    feedback("Entrada de produtos de consumo realizada com sucesso");

    DATABASE->close(Caixas);
    DATABASE->close(ContasPagar);
}
int baixar_nota_entrada() {
    DATABASE->open(ContasPagar);
    DATABASE->open(Caixas);

    DATABASE_forEach(struct ContaPagar, conta, ContasPagar) {
        clrscr();
        form(1, ContasPagar, &conta);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 3, "Próximo", "Dar baixa", "Sair");
        if (option == 1) {
            time_t mytime;
            mytime = time(NULL);
            struct tm tm = *localtime(&mytime);
            int day = tm.tm_mday, month = (tm.tm_mon + 1), year = (tm.tm_year + 1900);

            //Atualiza a situação da parcela
            conta.pago = 1;
            DATABASE->update(ContasPagar, &conta);

            //Gera uma movimentação de débito no caixa do hotel
            struct Caixa caixa = {};
            caixa.hotel_id = 1;
            caixa.valor = conta.valor_parcela;
            strcpy(caixa.descricao, "Baixa de nota");
            strcpy(caixa.natureza, "Débito");
            caixa.data = year * 10000 + month * 100 + day;
            DATABASE->insert(Caixas, &caixa);
            
        } else if (option == 2) break;
    }

    DATABASE->close(ContasPagar);
    DATABASE->close(Caixas);
}