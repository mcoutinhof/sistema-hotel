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

int relatorio_acomodacoes() {
    DATABASE->open(Acomodacoes);
    DATABASE->open(Reservas);
    DATABASE->open(Categorias);

    bool porCodigo = false, porCategoria = false, porData = false;
    unsigned int codInicio = 0, codFim = 0, dataInicio = 0, dataFim = 0;
    char categoria[64];

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
            bool achouCategoria = false;
            DATABASE_forEach(struct Categoria, cat, Categorias) {
                //Seleciona a categoria da acomodação
                if (cat.id != acom.categoria_id) continue;

                achouCategoria = true;

                //Verifica se o nome da categoria corresponde ao informado
                obedeceFiltros = strcasecmp(categoria, cat.titulo) == 0;
                break;
            }
            if (!achouCategoria) obedeceFiltros = false;
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
            form(1, Acomodacoes, &acom);
            printf(" \n\n");
        }
    }

    alert("Aperte qualquer tecla para continuar...\n");

    DATABASE->close(Acomodacoes);
    DATABASE->close(Reservas);
    DATABASE->close(Categorias);
}
