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
    bool porData = false, porCategoria = false, porQtdPessoas = false, porFacilidade = false;
    unsigned int dataInicio = 0, dataFim = 0, qtdPessoas = 0;
    char categoria[64], facilidade[512];
    while (1) {
        clrscr();
        int option = menu($f, 5,
                          "Filtrar por data",
                          "Filtrar por categoria de acomodação",
                          "Filtrar por quantidade de pessoas",
                          "Filtrar por tipo de facilidade",
                          "Procurar >>");
        switch (option) {
            case 0:
                clrscr();
                porData = true;
                printf($a "Data inicial: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataInicio);
                printf($a "Data final: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_DATE}, &dataFim);
                break;
            case 1:
                clrscr();
                porCategoria = true;
                printf($a "Categoria: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &categoria);
                break;
            case 2:
                clrscr();
                porQtdPessoas = true;
                printf($a "Quantidade de pessoas: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &qtdPessoas);
                break;
            case 3:
                clrscr();
                porFacilidade = true;
                printf($a "Tipo de facilidade: ");
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 512}, &facilidade);
                break;
        }
        if (option == 4)
            break;
    }
    DATABASE_forEach(struct Acomodacao, acom, Acomodacoes) {
        clrscr();
        bool obedeceFiltros = true;
        if (porCategoria || porQtdPessoas) {
            DATABASE_forEach(struct Categoria, cat, Categorias) {
                if (cat.id == acom.categoria_id) {
                    if (porCategoria && strcasecmp(cat.titulo, categoria) != 0) {
                        obedeceFiltros = false;
                    } else if (porQtdPessoas && qtdPessoas > cat.lotacao) {
                        obedeceFiltros = false;
                    }
                    break;
                }
            }
        }
        if (porFacilidade && obedeceFiltros && strstr(acom.facilidades, facilidade) == NULL) {
            obedeceFiltros = false;
        }
        if (porData && obedeceFiltros) {
            DATABASE_forEach(struct Reserva, res, Reservas) {
                if (res.acomodacao_id == acom.id) {
                    if (dataInicio < res.data_inicial && dataFim > res.data_inicial) {
                        obedeceFiltros = false;
                    } else if (dataFim > res.data_final && dataInicio < res.data_final) {
                        obedeceFiltros = false;
                    } else if (dataInicio >= res.data_inicial && dataFim <= res.data_final) {
                        obedeceFiltros = false;
                    }
                }
            }
        }
        if (obedeceFiltros) {
            form(1, Acomodacoes, &acom);
            gotoxy(3, wherey() + 2);
            int option = menu($f, 3, "Próximo", "Reservar", "Sair");
            if (option == 1) {
                clrscr();
                struct Reserva res = {.acomodacao_id = acom.id};
                if (porData) {
                    res.data_inicial = dataInicio;
                    res.data_final = dataFim;
                }
                form(2, Reservas, &res);
                DATABASE->insert(Reservas, &res);
            } else if (option == 2) break;
        }
    }
    DATABASE->close(Acomodacoes);
    DATABASE->close(Categorias);
    DATABASE->close(Reservas);
}

/*int cadastrar_reserva() {
    clrscr();

    //Recupera os dados da reserva
    struct Reserva reserva = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Reservas, &reserva); // Modo 0 = Inserir

    //Cria a reserva
    DATABASE->open(Reservas);
    DATABASE->insert(Reservas, &reserva);
    DATABASE->close(Reservas);
    return EXIT_SUCCESS;
}*/

int ver_reserva() {
    DATABASE->open(Reservas);
    DATABASE_forEach(struct Reserva, reserva, Reservas) {
        clrscr();
        form(1, Reservas, &reserva);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
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
        if (option == 3)
            break;
    }
    DATABASE->close(Reservas);
}