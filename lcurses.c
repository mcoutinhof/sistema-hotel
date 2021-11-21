#include "lcurses.h"
#include <stdio.h>
#include <termios.h>
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

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void wherexy(int *x, int *y) {
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg);
    struct termios new_cfg = old_cfg;
    new_cfg.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_cfg);
    fputs("\033[6n", stdout);
    scanf("%*c%*c%d%*c%d%*c", y, x);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_cfg);
}