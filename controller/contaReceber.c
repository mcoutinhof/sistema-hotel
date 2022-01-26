/**
 * @authors Ryan W. Fonseca
 */

#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include "../view/rotas.h"
#include <string.h>

int relatorio_contas_receber(char *path) {
    DATABASE->open(ContasReceber);
    DATABASE->open(Hospedes);

    bool porData = false, porCodigo = false;
    unsigned int codInicio = 0, codFim, dataInicio = 0, dataFim = 0;

    FILE *fp;
    if (strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 3, "Filtrar por data de recebimento", "Filtrar por código do cliente",
                          "Gerar relatório >>");
        switch (option) {
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
        if (option == 2) break;
    }
    DATABASE_forEach(struct ContaReceber, conta, ContasReceber) {
        bool obedeceFiltros = true;

        if (porData) obedeceFiltros = conta.data_recebimento >= dataInicio && conta.data_recebimento < dataFim;

        if (obedeceFiltros && porCodigo) {
            struct Hospede hosp = {};
            if (!DATABASE_findBy("id", &conta.hospede_id, Hospedes, &hosp)) continue;
            obedeceFiltros = hosp.id >= codInicio && hosp.id < codFim;
        }
        if (obedeceFiltros) {
            if (strlen(path) != 0) {
                fprintf(fp, "%u;%u;%u;%f;%u;%u;%u;%u \n", conta.id, conta.hospede_id, conta.hotel_id,
                        conta.valor_parcela, conta.num_parcela, conta.data_recebimento, conta.data_vencimento,
                        conta.pago);
            } else {
                clrscr();
                form(1, ContasReceber, &conta);
                gotoxy(3, wherey() + 2);
                if (menu($f, 2, "Próximo", "Sair") == 1) break;
            }
        }
    }
    if (strlen(path) != 0) {
        clrscr();
        fclose(fp);
    }
    alert("\nAperte qualquer tecla para continuar... \n");

    DATABASE->close(ContasReceber);
    DATABASE->close(Hospedes);
}
