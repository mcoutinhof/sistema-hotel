#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"
#include <string.h>

int cadastrar_produto() {
    clrscr();
    struct Produto prod = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Produtos, &prod); // Modo 0 = Inserir
    DATABASE->open(Produtos);
    DATABASE->insert(Produtos, &prod);
    DATABASE->close(Produtos);
    return EXIT_SUCCESS;
}

int ver_produto() {
    DATABASE->open(Produtos);
    DATABASE_forEach(struct Produto, prod, Produtos) {
        clrscr();
        form(1, Produtos, &prod);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Produtos, &prod);
                DATABASE->update(Produtos, &prod);
                break;
            case 2:
                DATABASE->delete(Produtos);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Produtos);
}

int relatorio_produtos(char *path) {
    DATABASE->open(Produtos);

    bool porCodigo = false, porEstoqueMinimo = false;
    unsigned int codInicio = 0, codFim = 0;

    FILE *fp;
    if (strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 3, "Filtrar por faixa de código", "Filtrar por produtos em estoque mínimo",
                          "Gerar relatório >>");

        switch (option) {
            case 0:
                clrscr();
                porCodigo = true;
                printf($a "Código inicial: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &codInicio);
                printf($a "Código final: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &codFim);
                break;
            case 1:
                porEstoqueMinimo = true;
        }
        if (option == 2) break;
    }
    clrscr();

    DATABASE_forEach(struct Produto, prod, Produtos) {
        bool obedeceFiltros = true;
        //Verifica se o código do produto está entre o intervalo informado
        if (porCodigo) obedeceFiltros = prod.id >= codInicio && prod.id < codFim;

        //Verifica se a quantidade do produto em estoque atingiu a reserva
        if (obedeceFiltros && porEstoqueMinimo) obedeceFiltros = prod.estoque <= prod.estoque_minimo;

        //Exibe os dados do produto
        if (obedeceFiltros) {
            if (strlen(path) != 0) {
                fprintf(fp, "%u;%s;%s;%u;%u;%f;%u;%u \n", prod.id, prod.nome, prod.descricao, prod.estoque,
                        prod.estoque_minimo, prod.preco_venda, prod.fornecedor_id, prod.hotel_id);
            } else {
                clrscr();
                form(1, Produtos, &prod);
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

    DATABASE->close(Produtos);
}
