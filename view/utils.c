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
    if (p == s || ferror(stream)) {
        return NULL;
    }
    *e = '\0';
    return s;
}

/**
 * TODO: Documentar
 * @param stream
 * @param colMeta
 * @param ptr
 * @return O número de caracteres impressos.
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
            return fprintf(stream, "%s", (char *) ptr);
    }
    return 0;
}

/**
 * TODO: Documentar
 * @param stream
 * @param delimiter
 * @param colMeta
 * @param ptr
 * @return 1 se tiver sucesso, 0 caso contrário.
 */
static int readVal(FILE *stream, int delimiter, const ColumnMeta *colMeta, void *ptr) {
    memset(ptr, 0, colMeta->size); // Limpa o campo
    if (colMeta->type == COL_TYPE_STRING) {
        return fgetstr(ptr, colMeta->size, delimiter, stream) != NULL;
    }
    char buf[48];
    if (fgetstr(buf, 48, delimiter, stream) == NULL) {
        return 0;
    }
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
    return 0;
}

// Inserir = 0, Visualizar = 1, Editar = 2.
int form(int mode, const Table table, void *ptr) {
    int x, y, i = 0;
    wherexy(&x, &y);
    TableState *tableState = *table++;
    const TableInfo *tableInfo = *table++;
    for (ColumnMeta *colMeta; (colMeta = *table++) != NULL; ptr += colMeta->size) {
        if (!(colMeta->flags & COL_FLAG_SYS_GENERATED) || mode == 1) { // Visualizar = 1, pode ver campos do sistema.
            gotoxy(x, y + i++);
            printf($r $a "%s: " $r, colMeta->displayName); // Imprime o label do input

            int iX, iY; // Coordenadas do input
            if (mode != 1) {
                wherexy(&iX, &iY);
            }

            if (mode != 0) { // Inserir = 0, não tem valores predefinidos
                printVal(stdout, colMeta, ptr);
            }

            if (mode == 2) { // Editar = 2, pergunta se quer editar
                gotoxy(x + 2, iY + 1);
                int edit = menu($f, 2, "Próximo", "Editar");
                gotoxy(x + 2, iY + 1);
                clrtobot();
                if (!edit) continue;
            }

            if (mode != 1) { // Visualizar = 1, não permite inserir valores.
                gotoxy(iX, iY);
                clrtoeol();
                readVal(stdin, '\n', colMeta, ptr);

                // Mostra como o valor foi lido
                gotoxy(iX, iY);
                clrtoeol();
                printVal(stdout, colMeta, ptr);
            }
        }
    }
    return 1;
}

int menu(const char *prefix, int nitems, ...) {
    va_list items;
    int x, y, opt = 0;
    wherexy(&x, &y);
    fputs("\033[?25l", stdout); // Esconde o cursor

    printMenu:
    va_start(items, nitems);
    for (int i = 0; i < nitems; ++i) {
        gotoxy(x, y + i);
        if (i == opt % nitems) {
            printf($r "%s" $i "%s", prefix, va_arg(items, char *)); // Destaca a opção selecionada
        } else {
            printf($r "%s" "%s", prefix, va_arg(items, char *));
        }
    }

    while (1) {
        switch (getch()) {
            case '\t': // Pressionou TAB
                opt++;
                goto printMenu;
            case '\n': // Pressionou ENTER
                fputs("\033[?25h" $r, stdout); // Mostra o cursor e reseta o estilo
                va_end(items);
                return opt % nitems;
        }
    }
}