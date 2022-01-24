#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"
#include <string.h>

int cadastrar_acomodacao() {
    clrscr();
    struct Acomodacao acom = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Acomodacoes, &acom); // Modo 0 = Inserir
    DATABASE->open(Acomodacoes);
    DATABASE->insert(Acomodacoes, &acom);
    DATABASE->close(Acomodacoes);
    return EXIT_SUCCESS;
}

int ver_acomodacao() {
    DATABASE->open(Acomodacoes);
    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        clrscr();
        form(1, Acomodacoes, &acom);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Acomodacoes, &acom);
                DATABASE->update(Acomodacoes, &acom);
                break;
            case 2:
                DATABASE->delete(Acomodacoes);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Acomodacoes);
}

int relatorio_acomodacoes(char *path) {
    DATABASE->open(Acomodacoes);
    DATABASE->open(Reservas);
    DATABASE->open(Categorias);

    bool porCodigo = false, porCategoria = false, porData = false;
    unsigned int codInicio = 0, codFim = 0, dataInicio = 0, dataFim = 0;
    char categoria[64];

    FILE *fp;
    if(strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 4, "Filtrar faixa de código", "Filtrar por categoria", "Filtrar por data de reserva", "Gerar relatório >>");
        switch (option) {
            case 0:
                porCodigo = true;
                clrscr();
                printf($a "Código inicial: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &codInicio);
                printf($a "Código final: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &codFim);
                break;
            case 1:
                porCategoria = true;
                clrscr();
                printf($a "Categoria: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &categoria);
                break;
            case 2: 
                porData = true;
                clrscr();
                printf($a "Data inicial: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataInicio);
                printf($a "Data final: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataFim);
        }
        if (option == 3) break;
    }

    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        bool obedeceFiltros = true;

         //Verifica se o id da acomodação esta entre o intervalo informado
        if(porCodigo) obedeceFiltros = acom.id >= codInicio && acom.id < codFim;

        if(obedeceFiltros && porCategoria) {
            struct Categoria cat = {};
            if(!DATABASE_findBy("id", &acom.categoria_id, Categorias, &cat)) continue;
            obedeceFiltros = strcasecmp(categoria, cat.titulo) == 0;
        }
        if(obedeceFiltros && porData) {
            DATABASE_forEach(struct Reserva, res, Reservas) {
                //Seleciona as reservas da acomodação
                if (res.acomodacao_id != acom.id) continue;

                //Verifica se não há sobreposição de datas do periodo da reserva com a data disponível informada
                obedeceFiltros =  !((dataInicio < res.data_inicial && dataFim > res.data_inicial) 
                                 || (dataInicio < res.data_inicial && dataFim > res.data_inicial)
                                 || (dataInicio >= res.data_inicial && dataFim <= res.data_final));
                
                //Somente sai do loop se encontrar uma reserva que sobreponha a data disponível ou após verificar todas as reservas
                if(!obedeceFiltros) break;
            }
        }
        if(obedeceFiltros) {
            if(strlen(path) != 0) {
                fprintf(fp, "%u;%s;%s;%s;%u;%u \n", acom.id, acom.titulo, acom.descricao, acom.facilidades, acom.categoria_id, acom.hotel_id);
            } else {
                form(1, Acomodacoes, &acom);
                printf(" \n\n");
            }
        }
    }
    if(strlen(path) != 0) {
        clrscr();
        fclose(fp);
    } 
    alert("Aperte qualquer tecla para continuar...\n");

    DATABASE->close(Acomodacoes);
    DATABASE->close(Reservas);
    DATABASE->close(Categorias);
}
int relatorio_movimentacao_acomodacoes(char *path) {
    DATABASE->open(Acomodacoes);
    DATABASE->open(Categorias);
    DATABASE->open(Reservas);

    bool porAcomodacao = false, porDiarias = false, porRendimento = false;

    bool filtroAcomodacao[64] = {};
    struct Acomodacao tempAcom = {};
    unsigned int rendimento = 0, diarias = 0;
    int pesquisaDiarias = 0, pesquisaRendimento = 0;

    FILE *fp;
    if(strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 4, "Filtrar por dados da acomodação", 
                                 "Filtrar pelo número de diárias ocupadas", 
                                 "Filtrar pelo rendimento em hospedagem", 
                                 "Gerar relatório >>");
        switch (option) {
            case 0:
                porAcomodacao = true;
                clrscr();
                memcpy(filtroAcomodacao, form(0, Acomodacoes, &tempAcom), 64 * sizeof(bool));
                break;
            case 1:
                porDiarias = true;
                clrscr();
                printf($a "Número de diárias: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &diarias);
                printf($a "Forma de busca: \n");
                pesquisaDiarias = menu($f, 3, "Igual ao valor informado", "Número de diárias superior", "Número de diárias inferior");
                break;
            case 2: 
                porRendimento = true;
                clrscr();
                printf($a "Rendimento em hospedagem: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &rendimento);
                printf($a "Forma de busca: \n");
                pesquisaRendimento = menu($f, 3, "Igual ao valor informado", "Rendimento superior", "Rendimento inferior");
        }
        if (option == 3) break;
    }

    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        bool obedeceFiltros = true;

        int countDiarias = 0, valorDiaria = 0;
        float total = 0;

        //Calcula a quantidade de diárias reservadas da acomodação
        DATABASE_forEach(struct Reserva, res, Reservas) {
            if(res.acomodacao_id != acom.id) continue;
            countDiarias+=res.periodo;
        }
        //Recupera o valor da diária da acomodação
        struct Categoria cat = {};
        if(!DATABASE_findBy("id", &acom.categoria_id, Categorias, &cat)) continue;
        valorDiaria = cat.valor_diaria;

        //Calcula o rendimento em hospedagem
        total = valorDiaria * countDiarias;

        if(porAcomodacao) obedeceFiltros = compareFields(Acomodacoes, &acom, &tempAcom, filtroAcomodacao);

        if(obedeceFiltros && (porDiarias || porRendimento)) {
            if(porDiarias) {
                switch(pesquisaDiarias) {
                    case 0:
                        obedeceFiltros = countDiarias == diarias;
                        break;
                    case 1: 
                        obedeceFiltros = countDiarias >= diarias;
                        break;
                    case 2: 
                        obedeceFiltros = countDiarias <= diarias;
                        break;
                }
            } 
            if(obedeceFiltros && porRendimento) {
                switch(pesquisaRendimento) {
                    case 0:
                        obedeceFiltros = total == rendimento;
                        break;
                    case 1: 
                        obedeceFiltros = total >= rendimento;
                        break;
                    case 2: 
                        obedeceFiltros = total <= rendimento;
                        break;
                }
            }
        }
        if(obedeceFiltros) {
            if(strlen(path) != 0) {
                fprintf(fp, "%u;%s;%s;%s;%u;%u;%f;%u \n", acom.id, acom.titulo, acom.descricao, acom.facilidades, acom.categoria_id, acom.hotel_id, total, countDiarias);
            } else {
                form(1, Acomodacoes, &acom);
                printf($a "Rendimento em hospedagem: ");
                printVal(stdout, &(ColumnMeta) {.type = COL_TYPE_FLOAT}, &total);
                printf($a "\n Quantidade de diárias ocupadas: ");
                printVal(stdout, &(ColumnMeta) {.type = COL_TYPE_UINT}, &countDiarias);
                printf(" \n\n");
            }
        }
    }
    if(strlen(path) != 0) {
        clrscr();
        fclose(fp);
    } 
    alert("Aperte qualquer tecla para continuar...\n");

    DATABASE->close(Acomodacoes);
    DATABASE->close(Categorias);
    DATABASE->close(Reservas);
}
