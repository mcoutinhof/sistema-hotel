#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int relatorio_contas_pagar() {
    DATABASE->open(ContasPagar);
    DATABASE->open(Fornecedores);

    bool porData = false, porCodigo = false;
    unsigned int codInicio = 0, codFim, dataInicio = 0, dataFim = 0;

    while (1) {
        clrscr();
        int option = menu($f, 3, "Filtrar por data de vencimento", "Filtrar por código do fornecedor", "Gerar relatório >>");
        switch(option) {
            case 0: 
                porData = true;
                clrscr();
                printf($a "Data inicial: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &dataInicio);
                printf($a "Data final: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &dataFim);
                break;
            case 1:
                porCodigo = true;
                clrscr();
                printf($a "Código inicial: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &codInicio);
                printf($a "Código final: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &codFim);
                break;
        }
        if(option == 2) break;
    }
    DATABASE_forEach(struct ContaPagar, conta, ContasPagar) {
        bool obedeceFiltros = true;

        if(porData) obedeceFiltros = conta.data_vencimento >= dataInicio && conta.data_vencimento < dataFim;

        if(obedeceFiltros && porCodigo) {
            struct Fornecedor forn = {};
            if(!DATABASE_findBy("id", &conta.fornecedor_id, Fornecedores, &forn)) continue;
            obedeceFiltros = forn.id >= codInicio && forn.id < codFim;
        }
        if(obedeceFiltros) {
            form(1, ContasPagar, &conta);
            printf(" \n\n");
        }
    }

    alert("Aperte qualquer tecla para continuar... \n");

    DATABASE->close(ContasPagar);
    DATABASE->close(Fornecedores);
}
