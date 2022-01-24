#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int relatorio_contas_receber() {
    DATABASE->open(ContasReceber);
    DATABASE->open(Hospedes);

    bool porData = false, porCodigo = false;
    unsigned int codInicio = 0, codFim, dataInicio = 0, dataFim = 0;

    while (1) {
        clrscr();
        int option = menu($f, 3, "Filtrar por data de recebimento", "Filtrar por código do cliente", "Gerar relatório >>");
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
    DATABASE_forEach(struct ContaReceber, conta, ContasReceber) {
        bool obedeceFiltros = true;

        if(porData) obedeceFiltros = conta.data_recebimento >= dataInicio && conta.data_recebimento < dataFim;

        if(obedeceFiltros && porCodigo) {
            struct Hospede hosp = {};
            if(!DATABASE_findBy("id", &conta.hospede_id, Hospedes, &hosp)) continue;
            obedeceFiltros = hosp.id >= codInicio && hosp.id < codFim;
        }
        if(obedeceFiltros) {
            form(1, ContasReceber, &conta);
            printf(" \n\n");
        }
    }
    alert("Aperte qualquer tecla para continuar... \n");

    DATABASE->close(ContasReceber);
    DATABASE->close(Hospedes);
}
