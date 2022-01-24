#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"

int cadastrar_hospede() {
    clrscr();
    struct Hospede hosp = {}; // Sempre coloque as chaves pra zerar os valores da struct
    form(0, Hospedes, &hosp); // Modo 0 = Inserir
    DATABASE->open(Hospedes);
    DATABASE->insert(Hospedes, &hosp);
    DATABASE->close(Hospedes);
    return EXIT_SUCCESS;
}

int ver_hospede() {
    DATABASE->open(Hospedes);
    DATABASE_forEach(struct Hospede, hosp, Hospedes) {
        clrscr();
        form(1, Hospedes, &hosp);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Próximo", "Editar", "Deletar", "Sair");
        switch (option) {
            case 0:
                continue;
            case 1:
                clrscr();
                form(2, Hospedes, &hosp);
                DATABASE->update(Hospedes, &hosp);
                break;
            case 2:
                DATABASE->delete(Hospedes);
                break;
        }
        if (option == 3)
            break;
    }
    DATABASE->close(Hospedes);
}

int relatorio_hospedes(char *path) {
    DATABASE->open(Hospedes);

    bool porCodigo = false, porSexo = false;
    unsigned int codInicio = 0, codFim = 0;
    char sexo[16];

    FILE *fp;
    if(strlen(path) != 0) fp = fopen(path, "w");

    while (1) {
        clrscr();
        int option = menu($f, 3, "Filtrar por faixa de código", "Filtrar por sexo", "Gerar relatório >>");
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
                clrscr();
                porSexo = true;
                printf($a "Sexo: " $f);
                readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 16}, &sexo);
                break;
        }
        if (option == 2) break;
    }
    clrscr();

    DATABASE_forEach(struct Hospede, hosp, Hospedes) {
        bool obedeceFiltros = true;
        //Verifica se o id do hóspede esta entre o intervalo informado
        if(porCodigo) obedeceFiltros = hosp.id >= codInicio && hosp.id < codFim;
        //Verifica se o sexo do hóspede corresponde ao informado
        if(obedeceFiltros && porSexo) obedeceFiltros = strcasecmp(hosp.sexo, sexo) == 0;
        //Exibe os dados do hóspede 
        if(obedeceFiltros) {
            if(strlen(path) != 0) {
                fprintf(fp, "%u;%s;%s;%s;%s;%s;%s;%s;%s;%u \n", hosp.id, hosp.nome, hosp.endereco, hosp.cpf, hosp.telefone, hosp.email, hosp.sexo, hosp.estado_civil, hosp.nascimento, hosp.hotel_id);
            } else {
                form(1, Hospedes, &hosp);
                printf(" \n\n");
            }
        }
    }
    if(strlen(path) != 0) {
        clrscr();
        fclose(fp);
    } 
    alert("Aperte qualquer tecla para continuar...\n");

    DATABASE->close(Hospedes);
}
