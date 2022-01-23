#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"

int realizar_entrada() {
    DATABASE->open(Entradas);
    DATABASE->open(Fornecedores);
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

    //Seleciona os produtos da entrada
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
                    printf($a "Preço: ");
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
            } else break;
        }
        if(!count) {
            feedback("Nenhum produto cadastrado. Certifique-se de criar ao menos um produto para dar entrada \n");
            break;
        } else if(!itemSelecionado) {
            feedback("Nenhum produto selecionado. Certifique-se de incluir ao menos um para dar entrada \n");
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

    DATABASE->close(Entradas);
    DATABASE->close(Fornecedores);
    DATABASE->close(ItensEntrada);
}