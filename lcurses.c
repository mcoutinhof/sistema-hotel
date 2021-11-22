#include "lcurses.h"
#include <stdio.h>
#include <unistd.h>

void clrscr() {
    fputs("\033[2J\033[3J\033[H", stdout);
}

void clrtobot() {
    fputs("\033[0J", stdout);
}

void clrtoeol() {
    fputs("\033[0K", stdout);
}

#if defined(linux)

#include <termios.h>

int getch() {
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg);
    struct termios new_cfg = old_cfg;
    new_cfg.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_cfg);
    register int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_cfg);
    return ch;
}

#elif defined(_WIN32)
#include <conio.h>
#endif

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void wherexy(int *x, int *y) {
    fputs("\033[6n", stdout);
    char buf[48], i = 0;
    while ((i < sizeof(buf) - 1) && (buf[i] = getch()) != EOF && (buf[i++]) != 'R');
    buf[i] = '\0';
    sscanf(buf, "%*c%*c%d%*c%d%*c", y, x);
}