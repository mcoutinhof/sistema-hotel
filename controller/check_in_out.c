#include "../lcurses.h"
#include "../model/tables.h"
#include "../view/utils.h"
#include <stdlib.h>
#include <string.h>
#include "../view/rotas.h"
#include <time.h>

int check_in_out(int operation) {
    DATABASE->open(Reservas);
    DATABASE->open(Hospedes);
    DATABASE->open(Acomodacoes);
    DATABASE->open(Categorias);
    DATABASE->open(Caixas);
    DATABASE->open(ContasReceber);
    DATABASE->open(Comandas);

    unsigned int hospede_id = 0;
    bool achouHospede = false, pagarDiarias = false;

    while(!achouHospede) {
        char nome[64] = {0};
        int count = 0;

        printf($a "Nome do hóspede: ");
        readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_STRING, .size = 64}, &nome);

        DATABASE_forEach(struct Hospede, hosp, Hospedes) {
            if (strcasecmp(hosp.nome, nome) != 0) continue;

            count++;
            clrscr();
            form(1, Hospedes, &hosp);
            gotoxy(3, wherey() + 2);
            if(menu($f, 2, "Selecionar", "Próximo") == 0) {
                hospede_id = hosp.id;
                break;
            };
            achouHospede = true;
        }
        if(!count) {
            printf($a "Não foram encontrados hóspedes de nome: %s. Por favor, tente novamente! \n", nome);
        } else if(!achouHospede) {
            printf($a "Para prosseguir é necessário selecionar um hóspede. Por favor, tente novamente! \n");
        }
    }

    DATABASE_forEach(struct Reserva, res, Reservas) {
        if(res.hospede_id != hospede_id) continue;

        clrscr();
        form(1, Reservas, &res);
        gotoxy(3, wherey() + 2);
        int option = menu($f, 4, "Selecionar", "Próximo", "Sair");
        if(option == 0) {
            float total = 0;
            clrscr();

            if(operation == 0) {
                res.check_in = 1;
                printf($a "Deseja realizar o pagamento das diárias? \n");
                bool pagarDiarias = menu($f, 2, "Sim", "Não");
            } else {
                res.check_out = 1;
                DATABASE_forEach(struct Comanda, com, Comandas) {
                    if(res.hospede_id != com.hospede_id) continue;
                    total += com.preco * com.quantidade;
                }
            }
            if(operation == 0 && pagarDiarias || operation == 1 && !res.pago) {
                struct Acomodacao acom = {};
                if(!DATABASE_findBy("id", &res.acomodacao_id, Acomodacoes, &acom)) return 0;

                struct Categoria cat = {};
                if(!DATABASE_findBy("id", &acom.categoria_id, Categorias, &cat)) return 0;

                total += res.periodo * cat.valor_diaria;
                res.pago = 1;
            }
            printf($a "Valor total a ser pago %f", total);
            alert("Pressione qualquer tecla para continuar...");
            clrscr();

            if(total > 0) {
                time_t mytime;
                mytime = time(NULL);
                struct tm tm = *localtime(&mytime);
                int day = tm.tm_mday, month = (tm.tm_mon + 1), year = (tm.tm_year + 1900);

                printf($a "Método de pagamento: \n");
                if(menu($f, 3, "Dinheiro", "Cartão") == 1) {
                    unsigned int numParcelas = 0, diaVencimento = 0;

                    printf($a "Número de parcelas: " $f);
                    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &numParcelas);

                    printf($a "Dia de vencimento do cartão: " $f);
                    readVal(stdin, '\n', &(ColumnMeta) {.type = COL_TYPE_UINT}, &diaVencimento);

                    for(int i = 0; i < numParcelas; i++) {
                        month++;
                        if(month > 12) {
                            year++;
                            month = 1;
                        }
                        struct ContaReceber conta = {};
                        conta.hospede_id = res.hospede_id;
                        conta.hotel_id = 1;
                        conta.valor_parcela = total / numParcelas;
                        conta.num_parcela = i + 1;
                        conta.pago = 0;
                        conta.data_vencimento = year * 10000 + month * 100 + diaVencimento;
                        DATABASE->insert(ContasReceber, &conta);
                    }
                } else  {
                    struct Caixa caixa = {};
                    caixa.hotel_id = 1;
                    strcpy(caixa.natureza, "Crédito");
                    caixa.data = year * 10000 + month * 100 + day;
                    caixa.valor = total;
                    strcpy(caixa.descricao, "Pagamento das diárias");
                    DATABASE->insert(Caixas, &caixa);
                }
            }

            DATABASE->update(Reservas, &res);
            break;
        } else if(option == 2) break;
    }
    clrscr();
    if(operation == 0) 
        feedback("Check-in realizado com sucesso");
    else 
        feedback("Check-out realizado com sucesso");

    DATABASE->close(Reservas);
    DATABASE->close(Acomodacoes);
    DATABASE->close(Hospedes);
    DATABASE->close(Categorias);
    DATABASE->close(Caixas);
    DATABASE->close(ContasReceber);
    DATABASE->close(Comandas);
}