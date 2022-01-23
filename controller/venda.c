#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"

int realizar_venda() {
    DATABASE->open(Produtos);
    DATABASE->open(Vendas);
    DATABASE->open(ItensVenda);
    DATABASE->open(Hospedes);
    DATABASE->open(Comandas);

    bool itemSelecionado = false;
    unsigned int hospede_id = 0;
    struct Venda venda = {};

    //Seleciona o hospede da venda
    while(!hospede_id) {
        char nome[64] = {0};
        int count = 0;

        printf($a "Nome do hóspede: ");
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &nome);

        DATABASE_forEach(struct Hospede, hosp, Hospedes) {
            if (strcasecmp(hosp.nome, nome) != 0) continue;

            count++;
            clrscr();
            form(1, Hospedes, &hosp);
            gotoxy(3, wherey() + 2);
            if(menu($f, 2, "Selecionar", "Próximo") == 0) {
                hospede_id = hosp.id;
                break;
            };
        }
        
        if(!count) {
            printf($a "Não foram encontrados hóspedes de nome: %s. Por favor, tente novamente! \n", nome);
        } else if(!hospede_id) {
            printf($a "Para prosseguir é necessário selecionar um hóspede. Por favor, tente novamente! \n");
        }
    }
    //Define o método de pagamento
    clrscr();
    printf($a "Método de pagamento: \n");
    int method = menu($f, 2, "A vista", "Anotar");

    //Se o cliente optar por pagar a vista, é gerada uma venda
    if(method == 0) {
        clrscr();
        printf($a "Como deseja realizar o pagamento?  \n");
        int payment = menu($f, 2, "Dinheiro", "Cartão");

        venda.hospede_id = hospede_id;
        strcpy(venda.metodo_pagamento, payment ? "Dinheiro" : "Cartão");
        DATABASE->insert(Vendas, &venda);
    }
    float total = 0;
    
    //Seleciona os produtos da venda
    while(!itemSelecionado) {
        unsigned int count = 0;

        DATABASE_forEach(struct Produto, prod, Produtos) {
            //Verifica se o produto possui estoque
            if(!prod.estoque) continue;

            count++;
            clrscr();
            form(1, Produtos, &prod);
            gotoxy(3, wherey() + 2);
            int option = menu($f, 3, "Incluir", "Próximo", "Finalizar venda");
            if (option == 0) {
                unsigned int quantidade = 0;
                clrscr();
                while(!quantidade) {
                    printf($a "Quantidade: ");
                    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &quantidade);
                    if(!quantidade) {
                        printf($a "A quantidade deve ser maior ou igual a 1 \n");
                    } else if(quantidade <= prod.estoque) {
                        if(method == 0) {
                            struct ItemVenda item = {};
                            item.produto_id = prod.id;
                            item.venda_id = venda.id;
                            item.quantidade = quantidade;
                            item.preco = prod.preco_venda;
                            total += item.quantidade * item.preco;
                            DATABASE->insert(ItensVenda, &item);
                        } else {
                            struct Comanda com = {};
                            com.produto_id = prod.id;
                            com.hospede_id = hospede_id;
                            com.quantidade = quantidade;
                            com.preco = prod.preco_venda;
                            total += com.quantidade * com.preco;
                            DATABASE->insert(Comandas, &com);
                        }
                        prod.estoque -= quantidade;
                        DATABASE->update(Produtos, &prod);
                    } else {
                        quantidade = 0;
                        printf($a "Estoque insuficiente! A quantidade deve ser menor ou igual a: %u \n", prod.estoque);
                    }
                }
                itemSelecionado = true;
            } else if(option == 2 && (method == 0 && itemSelecionado || method == 1)) break;
        }
        if(!count) {
            if(method == 0) DATABASE->delete(Vendas);
            feedback("Nenhum produto disponível para venda. Por favor, dê entrada nos produtos desejados antes de finalizar a venda \n");
            return 1;
        } else if(method == 0 && !itemSelecionado) {
            feedback("Para vendas a vista, é necessário incluir ao menos um produto antes de finalizar. Por favor, tente novamente! \n");
        }
    }
    //Atualiza os dados da venda
    if(method == 0)  {
        venda.total = total;
        DATABASE->update(Vendas, &venda);
    }

    printf("Total a ser pago: %f", total);
    alert("Pressione qualquer tecla para continuar...");

    DATABASE->close(Produtos);
    DATABASE->close(Vendas);
    DATABASE->close(ItensVenda);
    DATABASE->close(Hospedes);
    DATABASE->close(Comandas);
}
int relatorio_vendas() {
    DATABASE->open(Vendas);

    bool porMetodo = false;
    int payment = 0;

    while (1) {
        clrscr();
        int option = menu($f, 2, "Filtrar por forma de pagamento", "Gerar relatório >>");
        if(option == 0) {
            porMetodo = true;
            clrscr();
            printf($a "Forma de pagamento: ");
            payment = menu($f, 2, "Dinheiro", "Cartão");
        } else break;
    }
    DATABASE_forEach(struct Venda, venda, Vendas) {
        bool obedeceFiltros = true;

        if(porMetodo) obedeceFiltros = strcasecmp(venda.metodo_pagamento, payment == 0 ? "Dinheiro" : "Cartão") == 0;

        if(obedeceFiltros) {
            form(1, Vendas, &venda);
            printf(" \n\n");
        }
    }
    alert("Aperte qualquer tecla para continuar...\n");

    DATABASE->close(Vendas);
}