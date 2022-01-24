#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include "../view/rotas.h"

int relatorio_caixas(char *path) {
    DATABASE->open(Caixas);

    bool porData = false;
    unsigned int dataInicio = 0, dataFim = 0;

    FILE *fp;
    if(strlen(path) != 0) fp = fopen(path, "w");

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
    clrscr();
    
    DATABASE_forEach(struct Caixa, caixa, Caixas) {
        bool obedeceFiltros = true;

        if(porData) obedeceFiltros = caixa.data >= dataInicio && caixa.data < dataFim;

        if(obedeceFiltros) {
            if(strlen(path) != 0) {
                fprintf(fp, "%u;%u;%f;%s;%s;%u \n", caixa.id, caixa.hotel_id, caixa.valor, caixa.descricao, caixa.natureza, caixa.data);
            } else {
                form(1, Caixas, &caixa);
                printf(" \n\n");
            }
        }
    }
    if(strlen(path) != 0) {
        clrscr();
        fclose(fp);
    } 
    alert("Aperte qualquer tecla para continuar... \n");

    DATABASE->close(Caixas);
}
