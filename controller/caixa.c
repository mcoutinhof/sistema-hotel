#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int relatorio_caixas() {
    DATABASE->open(Caixas);

    bool porData = false;
    unsigned int dataInicio = 0, dataFim = 0;

    while (1) {
        clrscr();
        int option = menu($f, 2, "Filtrar por data", "Gerar relatório >>");

        if(option == 0) {
            porData = true;
            clrscr();
            printf($a "Data inicial: " $f);
            readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataInicio);
            printf($a "Data final: " $f);
            readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataFim);
        } else break;
    }
    DATABASE_forEach(struct Caixa, caixa, Caixas) {
        bool obedeceFiltros = true;

        if(porData) obedeceFiltros = caixa.data >= dataInicio && caixa.data < dataFim;

        if(obedeceFiltros) {
            form(1, Caixas, &caixa);
            printf(" \n\n");
        }
    }

    alert("Aperte qualquer tecla para continuar... \n");

    DATABASE->close(Caixas);
}
