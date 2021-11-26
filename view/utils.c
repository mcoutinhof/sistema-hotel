/**
 * @author Mateus Coutinho
 */

#include "utils.h"
#include "../lcurses.h"
#include "../model/database_local.h"
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/**
 * Lê STREAM até encontrar DELIMITER ou EOF e armazena os primeiros N menos 1 caracteres em S.
 * Ignora os espaços no começo e no final da string.
 * @return S se tiver sucesso, NULL se ocorrer um erro ou se não conseguir ler nenhum caractere.
 */
static char *fgetstr(char *s, int n, int delimiter, FILE *stream) {
    if (stream == NULL || n < 1 || ferror(stream)) {
        return NULL;
    }
    register char *p = s; // Ponteiro para a posição seguinte ao último caractere escrito.
    register char *e = s; // Ponteiro para a posição seguinte ao último caractere não-espaço escrito.
    register int c;
    while ((c = getc(stream)) != EOF && c != delimiter) {
        if (!(p == s && isspace(c)) && (--n > 0) && !isspace(*p++ = c)) {
            e = p;
        }
    }
    *e = '\0';
    return (p == s || ferror(stream)) ? NULL : s;
}

/**
 * Escreve um valor de acordo com os metadados da coluna a qual ele pertence.
 * @param stream Stream onde o valor será escrito.
 * @param colMeta Metadados da coluna a qual tal valor pertence.
 * @param ptr Ponteiro para a variável de onde o valor será lido.
 * @return a quantidade de caracteres impressos.
 */
static int printVal(FILE *stream, const ColumnMeta *colMeta, const void *ptr) {
    switch (colMeta->type) {
        case COL_TYPE_BOOL:
            return fprintf(stream, "%s", (*(bool *) ptr) ? "SIM" : "NÃO");
        case COL_TYPE_CHAR:
            return fprintf(stream, "%c", *(char *) ptr);
        case COL_TYPE_INT:
            return fprintf(stream, "%d", *(int *) ptr);
        case COL_TYPE_UINT:
            return fprintf(stream, "%u", *(unsigned int *) ptr);
        case COL_TYPE_FLOAT:
            return fprintf(stream, "%f", *(float *) ptr);
        case COL_TYPE_DOUBLE:
            return fprintf(stream, "%lf", *(double *) ptr);
        case COL_TYPE_STRING:
            return fprintf(stream, "%.*s", (int) colMeta->size, (char *) ptr);
    }
    return 0;
}

/**
 * Lê um valor de acordo com os metadados da coluna a qual ele pertence.
 * @param stream Stream de onde o valor será escrito.
 * @param delimiter Caractere que delimita até quando ler a stream.
 * @param colMeta Metadados da coluna a qual tal valor pertence.
 * @param ptr Ponteiro para a variável onde o valor será armazenado.
 * @return 1 se conseguir ler um valor válido, 0 caso contrário.
 */
static int readVal(FILE *stream, int delimiter, const ColumnMeta *colMeta, void *ptr) {
    if (colMeta->type == COL_TYPE_STRING) {
        return fgetstr(ptr, colMeta->size, delimiter, stream) != NULL;
    }
    char buf[48];
    memset(ptr, 0, colMeta->size);
    if (fgetstr(buf, 48, delimiter, stream) != NULL) {
        switch (colMeta->type) {
            case COL_TYPE_BOOL: // Tudo que começa com S, Y, V, T ou 1 é true, o resto é false.
                *(bool *) ptr = (strchr("SYVT1", toupper(*buf)) != NULL);
                return 1;
            case COL_TYPE_CHAR:
                return sscanf(buf, "%c", (char *) ptr);
            case COL_TYPE_INT:
                return sscanf(buf, "%d", (int *) ptr);
            case COL_TYPE_UINT:
                return sscanf(buf, "%u", (unsigned int *) ptr);
            case COL_TYPE_FLOAT:
                return sscanf(buf, "%f", (float *) ptr);
            case COL_TYPE_DOUBLE:
                return sscanf(buf, "%lf", (double *) ptr);
        }
    }
    return 0;
}

// 0 = Inserir, 1 = Visualizar, 2 = Editar.
void form(int mode, const Table table, void *ptr) {
    int i = 0; // Índice do campo atual.
    int x, y; // Coordenada do início do formulário.
    wherexy(&x, &y);
    TableState *tableState = *table++;
    const TableInfo *tableInfo = *table++;
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; ptr += colMeta->size) {
        if (!(colMeta->flags & COL_FLAG_SYS_GENERATED) || mode == 1) { // 1 = Visualizar, pode ver campos do sistema.
            gotoxy(x, y + i++);
            printf($r $a "%s: " $r, colMeta->displayName);

            int iX, iY; // Coordenada do início do campo de entrada.
            if (mode != 1) { // 1 = Visualizar, não é necessário salvar a coordenada.
                wherexy(&iX, &iY);
            }

            if (mode != 0) { // 0 = Inserir, não tem valores predefinidos.
                printVal(stdout, colMeta, ptr);
            }

            if (mode == 2) { // 2 = Editar, pergunta se o usuário quer editar.
                gotoxy(x + 2, iY + 1);
                bool wannaEdit = menu($f, 2, "Próximo", "Editar");
                gotoxy(x + 2, iY + 1);
                clrtobot();
                if (!wannaEdit) continue;
            }

            if (mode != 1) { // 1 = Visualizar, não permite inserir valores.
                gotoxy(iX, iY);
                clrtoeol();
                readVal(stdin, '\n', colMeta, ptr);

                gotoxy(iX, iY);
                clrtoeol();
                printVal(stdout, colMeta, ptr);
            }
        }
    }
}

int menu(const char *prefix, int nitems, ...) {
    va_list items;
    int x, y, opt = 0;
    wherexy(&x, &y);
    fputs("\033[?25l", stdout); // Esconde o cursor

    printMenu: // Se colocar dentro do while vai re-renderizar quando o usuário pressionar uma tecla inválida.
    va_start(items, nitems);
    for (int i = 0; i < nitems; ++i) {
        gotoxy(x, y + i);
        if (i == opt % nitems) {
            printf($r "%s" $i "%s", prefix, va_arg(items, char *)); // Destaca a opção selecionada
        } else {
            printf($r "%s" "" "%s", prefix, va_arg(items, char *));
        }
    }

    while (1) {
        switch (getch()) {
            case '\t': // Pressionou TAB
                opt++;
                goto printMenu;
            case '\n': // Pressionou ENTER
                va_end(items);
                fputs("\033[?25h" $r, stdout); // Mostra o cursor e reseta o estilo
                return opt % nitems;
        }
    }
}

void alert(const char *message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
    getch();
    clrbuf(); // É necessário limpar o buffer, pois algumas teclas podem inserir mais de 1 caractere nele.
}