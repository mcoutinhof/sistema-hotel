/**
 * @author Mateus Coutinho
 * ANSI Escape Codes: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 */

#include "lcurses.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static struct termios shellAttr, programAttr, savedAttr;
static int shellFlags, programFlags, savedFlags;

/**
 * Salva o estado atual do terminal, a ser restaurado por resetty().
 * @return OK se tiver sucesso e ERR caso falhar.
 */
static int savetty(void) {
    savedAttr = programAttr;
    savedFlags = programFlags;
    return OK;
}

/**
 * Restaura o estado anterior do terminal, salvo por savetty().
 * @return OK se tiver sucesso e ERR caso falhar.
 */
static int resetty(void) {
    programAttr = savedAttr;
    programFlags = savedFlags;
    return fcntl(STDIN_FILENO, F_SETFL, programFlags)
           | tcsetattr(STDIN_FILENO, TCSANOW, &programAttr);
}

int initscr(void) {
    printf("\x1b[?1049h"); // Entra na tela alternativa
    tcgetattr(STDIN_FILENO, &shellAttr);
    shellFlags = fcntl(STDIN_FILENO, F_GETFL);
    programFlags = shellFlags;
    programAttr = shellAttr;
    return OK;
}

int endwin(void) {
    return (printf("\x1b[?1049l") < 0 ? ERR : OK) // Sai da tela alternativa
           | fcntl(STDIN_FILENO, F_SETFL, shellFlags)
           | tcsetattr(STDIN_FILENO, TCSANOW, &shellAttr);
}

int echo(void) {
    programAttr.c_lflag |= ECHO;
    return tcsetattr(STDIN_FILENO, TCSANOW, &programAttr);
}

int noecho(void) {
    programAttr.c_lflag &= ~ECHO;
    return tcsetattr(STDIN_FILENO, TCSANOW, &programAttr);
}

int cbreak(void) {
    programAttr.c_lflag &= ~ICANON;
    return tcsetattr(STDIN_FILENO, TCSANOW, &programAttr);
}

int nocbreak(void) {
    programAttr.c_lflag |= ICANON;
    return tcsetattr(STDIN_FILENO, TCSANOW, &programAttr);
}

int timeout(int delay) {
    if (delay) {
        programFlags &= ~O_NONBLOCK;
    } else {
        programFlags |= O_NONBLOCK;
    }
    return fcntl(STDIN_FILENO, F_SETFL, programFlags);
}

int clrscr(void) {
    return printf("\x1b[2J\x1b[3J\x1b[H") < 0 ? ERR : OK;
}

int clrtobot(void) {
    return printf("\x1b[0J") < 0 ? ERR : OK;
}

int clrtoeol(void) {
    return printf("\x1b[0K") < 0 ? ERR : OK;
}

int getch(void) {
    savetty();
    noecho();
    cbreak();
    int ch = getchar();
    resetty();
    return ch;
}

int getche(void) {
    savetty();
    echo();
    cbreak();
    int ch = getchar();
    resetty();
    return ch;
}

int kbhit(void) {
    savetty();
    noecho();
    cbreak();
    timeout(0);
    int ch = getchar();
    resetty();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    } else {
        return 0;
    }
}

int clrbuf(void) {
    savetty();
    noecho();
    cbreak();
    timeout(0);
    while (getchar() != EOF) { /* Lê até o fim. */ }
    resetty();
    return OK;
}

int gotoxy(int x, int y) {
    return printf("\x1b[%d;%dH", y, x) < 0 ? ERR : OK;
}

int gotox(int x) {
    return printf("\x1b[%dG", x) < 0 ? ERR : OK;
}

int gotoy(int y) {
    return gotoxy(wherex(), y);
}

int wherexy(int *x, int *y) {
    savetty();
    noecho();
    cbreak();
    printf("\x1b[6n"); // Pergunta ao terminal a coordenada do cursor.
    scanf("%*c%*c%d%*c%d%*c", y, x); // Ele responderá como \x1b[y;xR.
    resetty();
    return OK;
}

int wherex() {
    int y, x = ERR;
    wherexy(&x, &y);
    return x;
}

int wherey() {
    int x, y = ERR;
    wherexy(&x, &y);
    return y;
}