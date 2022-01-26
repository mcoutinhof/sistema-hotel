/**
 * @authors Ryan W. Fonseca
 */

#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"
#include <time.h>

int realizar_venda() {
    DATABASE->open(Produtos);
    DATABASE->open(Vendas);
    DATABASE->open(ItensVenda);
    DATABASE->open(Hospedes);
    DATABASE->open(Comandas);

    int itemSelecionado = false, achouHospede = false;
    unsigned int hospede_id = 0;
    struct Venda venda = {};

    clrscr();

    //Seleciona o hospede da venda
    while (!achouHospede) {
        char nome[64] = {0};
        int count = 0;

        printf($a "Nome do hóspede: " $f);
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &nome);

        DATABASE_forEach(struct Hospede, hosp, Hospedes) {
            if (strcasecmp(hosp.nome, nome) != 0) continue;

            count++;
            clrscr();
            form(1, Hospedes, &hosp);
            gotoxy(3, wherey() + 2);
            if (menu($f, 2, "Selecionar", "Próximo") == 0) {
                achouHospede = true;
                hospede_id = hosp.id;
                break;
            };
        }
        if (!count) {
            printf($a "Não foram encontrados hóspedes de nome: %s. Por favor, tente novamente! \n", nome);
        } else if (!achouHospede) {
            printf($a "Para prosseguir é necessário selecionar um hóspede. Por favor, tente novamente! \n");
        }
    }
    //Define o método de pagamento
    clrscr();
    printf($a "Método de pagamento: \n");
    int method = menu($f, 3, "Dinheiro", "Cartão", "Anotar");

    if (method != 2) {
        venda.hospede_id = hospede_id;
        strcpy(venda.metodo_pagamento, method == 0 ? "Dinheiro" : "Cartão");
        DATABASE->insert(Vendas, &venda);
    }
    float total = 0;

    clrscr();
    feedback("Na próxima etapa, será necessário selecionar os produtos referentes a esta venda");
    clrscr();

    //Seleciona os produtos da venda
    while (!itemSelecionado) {
        unsigned int count = 0;

        DATABASE_forEach(struct Produto, prod, Produtos) {
            //Verifica se o produto possui estoque
            if (!prod.estoque) continue;

            count++;
            clrscr();
            form(1, Produtos, &prod);
            gotoxy(3, wherey() + 2);
            int option = menu($f, 3, "Incluir", "Próximo", "Finalizar venda");
            if (option == 0) {
                unsigned int quantidade = 0;
                clrscr();
                while (!quantidade) {
                    printf($a "Quantidade: ");
                    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &quantidade);
                    if (!quantidade) {
                        printf($a "A quantidade deve ser maior ou igual a 1 \n");
                    } else if (quantidade > prod.estoque) {
                        quantidade = 0;
                        printf($a "Estoque insuficiente! A quantidade deve ser menor ou igual a: %u \n", prod.estoque);
                    }
                }
                if (method != 2) {
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
                itemSelecionado = true;
            } else if (option == 2) break;
        }
        if (!count) {
            if (method != 2) DATABASE->delete(Vendas);
            feedback("Nenhum produto disponível para venda. Por favor, dê entrada nos produtos desejados antes de finalizar a venda\n");
            return 1;
        } else if (!itemSelecionado) {
            feedback("É necessário incluir ao menos um produto antes de finalizar. Por favor, tente novamente!\n");
        }
    }
    clrscr();
    printf("Total a ser pago: %f\n", total);
    alert("Pressione qualquer tecla para prosseguir...");

    //Atualiza os dados da venda
    if (method != 2) {
        venda.total = total;
        DATABASE->update(Vendas, &venda);
        realizar_pagamento_venda(total, hospede_id, method);
    } else {
        clrscr();
        feedback("O(s) produto(s) foram adicionados na comanda do hospede.");
    }

    DATABASE->close(Produtos);
    DATABASE->close(Vendas);
    DATABASE->close(ItensVenda);
    DATABASE->close(Hospedes);
    DATABASE->close(Comandas);
}

int ver_venda() {
    DATABASE->open(Vendas);

    DATABASE_forEach(struct Venda, venda, Vendas) {
        clrscr();
        form(1, Vendas, &venda);
        gotoxy(3, wherey() + 2);
        if (menu($f, 2, "Próximo", "Sair") == 1) break;
    }
    DATABASE->close(Vendas);
}

int realizar_pagamento_venda(float total, unsigned int hospede_id, int payment) {
    DATABASE->open(Caixas);
    DATABASE->open(ContasReceber);

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    int day = tm.tm_mday, month = (tm.tm_mon + 1), year = (tm.tm_year + 1900);

    struct Caixa caixa = {};
    caixa.hotel_id = 1;
    strcpy(caixa.natureza, "Crédito");
    caixa.data = year * 10000 + month * 100 + day;

    clrscr();

    if (payment == 1) {
        unsigned int numParcelas = 0, diaVencimento = 0;
        float valorParcela = 0;

        printf($a "Número de parcelas: " $f);
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &numParcelas);

        printf($a "Dia de vencimento do cartão: " $f);
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &diaVencimento);

        for (int i = 0; i < numParcelas; i++) {
            month++;
            if (month > 12) {
                year++;
                month = 1;
            }
            struct ContaReceber conta = {};
            conta.hospede_id = hospede_id;
            conta.hotel_id = 1;
            conta.valor_parcela = total / numParcelas;
            conta.num_parcela = i + 1;
            conta.pago = 0;
            conta.data_vencimento = year * 10000 + month * 100 + diaVencimento;
            DATABASE->insert(ContasReceber, &conta);
        }
    } else {
        caixa.valor = total;
        strcpy(caixa.descricao, "Venda de produtos de consumo com pagamento a vista");
        DATABASE->insert(Caixas, &caixa);
    }

    feedback("Venda realizada com sucesso\n");

    DATABASE->close(Caixas);
    DATABASE->close(ContasReceber);
}

int baixar_nota_venda() {
    DATABASE->open(ContasReceber);
    DATABASE->open(Caixas);

    DATABASE_forEach(struct ContaReceber, conta, ContasReceber) {
        clrscr();
        form(1, ContasReceber, &conta);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 3, "Próximo", "Dar baixa", "Sair");
        if (option == 1) {
            time_t mytime;
            mytime = time(NULL);
            struct tm tm = *localtime(&mytime);
            int day = tm.tm_mday, month = (tm.tm_mon + 1), year = (tm.tm_year + 1900);
            unsigned int current_date = year * 10000 + month * 100 + day;

            //Atualiza a situação da parcela
            conta.pago = 1;
            conta.data_recebimento = current_date;
            DATABASE->update(ContasReceber, &conta);

            //Gera uma movimentação de débito no caixa do hotel
            struct Caixa caixa = {};
            caixa.hotel_id = 1;
            caixa.valor = conta.valor_parcela;
            strcpy(caixa.descricao, "Baixa de nota");
            strcpy(caixa.natureza, "Crédito");
            caixa.data = current_date;
            DATABASE->insert(Caixas, &caixa);

        } else if (option == 2) break;
    }

    DATABASE->close(ContasReceber);
    DATABASE->close(Caixas);
}

int relatorio_vendas(char *path) {
    DATABASE->open(Vendas);

    bool porMetodo = false;
    int payment = 0;

    FILE *fp;
    if (strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 2, "Filtrar por forma de pagamento", "Gerar relatório >>");
        if (option == 0) {
            porMetodo = true;
            clrscr();
            printf($a "Forma de pagamento: ");
            payment = menu($f, 2, "Dinheiro", "Cartão");
        } else break;
    }
    clrscr();

    DATABASE_forEach(struct Venda, venda, Vendas) {
        bool obedeceFiltros = true;

        if (porMetodo) obedeceFiltros = strcasecmp(venda.metodo_pagamento, payment == 0 ? "Dinheiro" : "Cartão") == 0;

        if (obedeceFiltros) {
            if (strlen(path) != 0) {
                fprintf(fp, "%u;%f;%s;%u \n", venda.id, venda.total, venda.metodo_pagamento, venda.hospede_id);
            } else {
                clrscr();
                form(1, Vendas, &venda);
                gotoxy(3, wherey() + 2);
                if (menu($f, 2, "Próximo", "Sair") == 1) break;
            }
        }
    }
    if (strlen(path) != 0) {
        clrscr();
        fclose(fp);
    }
    alert("\nAperte qualquer tecla para continuar...\n");

    DATABASE->close(Vendas);
}