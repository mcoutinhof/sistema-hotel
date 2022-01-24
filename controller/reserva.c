#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"

int cadastrar_reserva() {
    DATABASE->open(Acomodacoes);
    DATABASE->open(Categorias);
    DATABASE->open(Reservas);
    bool porData = true, porCategoria = false, porQtdPessoas = false, porFacilidade = false;
    unsigned int dataInicio = 0, dataFim = 0, qtdPessoas = 0;
    char categoria[64], facilidade[512];
    
    while (1) {
        clrscr();
        int option = menu($f, 4,
                          "Filtrar por categoria de acomodação",
                          "Filtrar por quantidade de pessoas",
                          "Filtrar por tipo de facilidade",
                          "Procurar >>");
        switch (option) {
            case 0:
                clrscr();
                porCategoria = true;
                printf($a "Categoria: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &categoria);
                break;
            case 1:
                clrscr();
                porQtdPessoas = true;
                printf($a "Quantidade de pessoas: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &qtdPessoas);
                break;
            case 2:
                clrscr();
                porFacilidade = true;
                printf($a "Tipo de facilidade: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 512}, &facilidade);
                break;
        }
        if (option == 3) break;
    }
    
    clrscr();
    printf($a "Data inicial: " $f);
    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataInicio);
    printf($a "Data final: " $f);
    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataFim);

    int count = 0;
    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        clrscr();
        bool obedeceFiltros = true;
        
        //Filtro de data
        DATABASE_forEach(struct Reserva, res, Reservas) {
            //Percorre todas as reservas da acomodação
            if (res.acomodacao_id != acom.id) continue;

            //Se ao menos um dos casos de colisões de data acontecer, obedeceFiltros recebe false
            obedeceFiltros = !((dataInicio < res.data_inicial && dataFim > res.data_inicial) 
                            || (dataFim > res.data_final && dataInicio < res.data_final) 
                            || (dataInicio >= res.data_inicial && dataFim <= res.data_final));
            
            if(!obedeceFiltros) break;
        }
        //Filtro de categoria e lotação
        if (obedeceFiltros && (porCategoria || porQtdPessoas)) {
            DATABASE_forEach(struct Categoria, cat, Categorias) {
                //Seleciona a categoria da acomodação
                if (cat.id != acom.categoria_id) continue;

                //Verifica se o nome da categoria corresponde ao informado
                if(porCategoria) obedeceFiltros = strcasecmp(cat.titulo, categoria) == 0;
                //Verifica se a categoria suporta a lotação informada
                if(obedeceFiltros && porQtdPessoas) obedeceFiltros = qtdPessoas <= cat.lotacao;
                break;
            }
        }
        //Filtro de facilidades
        if (obedeceFiltros && porFacilidade) obedeceFiltros = strstr(acom.facilidades, facilidade) != NULL;

        //Decide o que fazer com a acomodação que satisfaz os requesitos de busca
        if (obedeceFiltros) {
            count++;
            form(1, Acomodacoes, &acom);
            gotoxy(3, wherey() + 2);
            int option = menu($f, 3, "Próximo", "Reservar", "Sair");
            if (option == 1) {
                clrscr();
                struct Reserva res = {.acomodacao_id = acom.id};
                res.data_inicial = dataInicio;
                res.data_final = dataFim;
                form(2, Reservas, &res);
                DATABASE->insert(Reservas, &res);
                break;
            } else if (option == 2) break;
        }
    }
    if(!count) feedback("Nenhuma acomodação disponível para os critérios de busca informados! Por favor, tente novamente");
    
    DATABASE->close(Acomodacoes);
    DATABASE->close(Categorias);
    DATABASE->close(Reservas);
}

int ver_reserva() {
    unsigned int date = current_date();

    DATABASE->open(Reservas);
    DATABASE_forEach(struct Reserva, reserva, Reservas) {
        //Seleciona apenas as reservas ativas
        if(reserva.data_final < date) continue;

        clrscr();
        form(1, Reservas, &reserva);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Cancelar reserva", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Reservas, &reserva);
                DATABASE->update(Reservas, &reserva);
                break;
            case 2:
                DATABASE->delete(Reservas);
                break;
        }
        if (option == 3) break;
    }
    DATABASE->close(Reservas);
}

int relatorio_reservas(char *path) {
    DATABASE->open(Reservas);
    DATABASE->open(Acomodacoes);
    DATABASE->open(Hospedes);

    bool filtroHospede[64] = {};
    bool filtroAcomodacao[64] = {};
    struct Hospede tempHosp = {};
    struct Acomodacao tempAcom = {};
    bool porHospede = false, porAcomodacao = false, porData = false;
    unsigned int dataInicio = 0, dataFim = 0;

    FILE *fp;
    if(strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 4, 
                            "Filtrar por dados do hóspede", 
                            "Filtrar por dados da acomodação", 
                            "Filtrar por período reservado",
                            "Gerar relatório >>");

        switch (option) {
            case 0:
                porHospede = true;
                clrscr();
                memcpy(filtroHospede, form(0, Hospedes, &tempHosp), 64 * sizeof(bool));
                break;
            case 1:
                porAcomodacao = true;
                clrscr();
                memcpy(filtroAcomodacao, form(0, Acomodacoes, &tempAcom), 64 * sizeof(bool));
                break;
            case 2:
                porData = true;
                clrscr();
                printf($a "Data inicial: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataInicio);
                printf($a "Data final: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataFim);
                break;
        }
        if (option == 3) break;
    }
    clrscr();

    DATABASE_forEach(struct Reserva, res, Reservas) {
        bool obedeceFiltros = true;

        //Verifica se o periodo da reserva está entre o período informado
        if(porData) obedeceFiltros = res.data_inicial >= dataInicio && res.data_final < dataFim;

        if(obedeceFiltros && porAcomodacao)  {
            struct Acomodacao acom = {};
            if(!DATABASE_findBy("id", &res.acomodacao_id, Acomodacoes, &acom)) continue;
            obedeceFiltros = compareFields(Acomodacoes, &acom, &tempAcom, filtroAcomodacao);
        }
        if(obedeceFiltros && porHospede)  {
            struct Hospede hosp = {};
            if(!DATABASE_findBy("id", &res.hospede_id, Hospedes, &hosp)) continue;
            obedeceFiltros = compareFields(Hospedes, &hosp, &tempHosp, filtroHospede);
        }
        if(obedeceFiltros) {
            if(strlen(path) != 0) {
                fprintf(fp, "%u;%u;%u;%u;%hhu;%hhu;%u;%u \n", res.id, res.data_inicial, res.data_final, res.periodo, res.check_in, res.check_out, res.acomodacao_id, res.hospede_id);
            } else {
                form(1, Reservas, &res);
                printf(" \n\n");
            }
        }
    }
    if(strlen(path) != 0) {
        clrscr();
        fclose(fp);
    } 
    alert("Aperte qualquer tecla para continuar...\n");

    DATABASE->close(Reservas);
    DATABASE->close(Acomodacoes);
    DATABASE->close(Hospedes);
}
