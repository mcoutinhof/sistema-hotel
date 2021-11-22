#include "lcurses.h"
#include <stdio.h>
#include <unistd.h>

void clrscr() {
    //fputs("\033[2J\033[3J\033[H", stdout);
    fputs("\033[2J\033[3J\033[2;3H", stdout);
}

void clrtobot() {
    fputs("\033[0J", stdout);
}

void clrtoeol() {
    fputs("\033[0K", stdout);
}

#if defined(linux)

#include <termios.h>
#include <fcntl.h>

int getch() {
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg);
    struct termios new_cfg = old_cfg;
    new_cfg.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_cfg);
    register int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_cfg);
    return ch;
}

int kbhit() {
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg);
    struct termios new_cfg = old_cfg;
    new_cfg.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_cfg);
    int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
    register int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_cfg);
    fcntl(STDIN_FILENO, F_SETFL, old_flags);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int wherex() {
    int x, y;
    wherexy(&x, &y);
    return x;
}

int wherey() {
    int x, y;
    wherexy(&x, &y);
    return y;
}

#elif defined(_WIN32)
#include <conio.h>
#endif

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void gotox(int x) {
    gotoxy(x, wherey());
}

void gotoy(int y) {
    gotoxy(wherex(), y);
}

void wherexy(int *x, int *y) {
    char buf[48];
    register int c, i = 0;
    fputs("\033[6n", stdout);
    while ((i < sizeof(buf) - 1)
           && (c = getch()) != EOF
           && (buf[i++] = c) != 'R');
    buf[i] = '\0';
    sscanf(buf, "%*c%*c%d%*c%d%*c", y, x);
}

void alert(const char *message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
    getch();
    while (kbhit()) getch();
}