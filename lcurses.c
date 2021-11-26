/**
 * @author Mateus Coutinho
 * ANSI Escape Codes: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 */

#include "lcurses.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

void clrscr() {
    fputs("\033[2J\033[3J\033[H", stdout);
    gotoxy(3, 2); // Uma pequena margem do topo esquerdo da tela.
}

void clrtobot() {
    fputs("\033[0J", stdout);
}

void clrtoeol() {
    fputs("\033[0K", stdout);
}

int getch() {
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg); // Obtém as configurações atuais do terminal.
    struct termios new_cfg = old_cfg;
    // Desativa as flags ECHO e ICANON, e então os caracteres inseridos não serão exibidos, ...
    new_cfg.c_lflag &= ~(ECHO | ICANON); // ... e estarão disponíveis sem ser necessário pressionar ENTER.
    tcsetattr(STDIN_FILENO, TCSANOW, &new_cfg); // Seta as novas configurações do terminal.
    register int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_cfg); // Volta às configurações anteriores do terminal.
    return ch;
}

int kbhit() {
    int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Obtém as configurações atuais do terminal.
    int new_flags = old_flags | O_NONBLOCK; // Ativa a flag O_NONBLOCK, e então o getch() não esperará por uma entrada.
    fcntl(STDIN_FILENO, F_SETFL, new_flags); // Seta as novas configurações do terminal.
    register int ch = getch();
    fcntl(STDIN_FILENO, F_SETFL, old_flags); // Volta às configurações anteriores do terminal.
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void clrbuf() {
    int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Obtém as configurações atuais da stream.
    int new_flags = old_flags | O_NONBLOCK; // Ativa a flag O_NONBLOCK, e então o getch() não esperará por uma entrada.
    fcntl(STDIN_FILENO, F_SETFL, new_flags); // Seta as novas configurações da stream.
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg); // Obtém as configurações atuais do terminal.
    struct termios new_cfg = old_cfg;
    // Desativa as flags ECHO e ICANON, e então os caracteres inseridos não serão exibidos, ...
    new_cfg.c_lflag &= ~(ECHO | ICANON); // ... e estarão disponíveis sem ser necessário pressionar ENTER.
    tcsetattr(STDIN_FILENO, TCSANOW, &new_cfg); // Seta as novas configurações do terminal.
    while (getchar() != EOF); // Lê as entradas até o final.
    tcsetattr(STDIN_FILENO, TCSANOW, &old_cfg); // Volta às configurações anteriores do terminal.
    fcntl(STDIN_FILENO, F_SETFL, old_flags); // Volta às configurações anteriores da stream.
}

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
    struct termios old_cfg;
    tcgetattr(STDIN_FILENO, &old_cfg); // Obtém as configurações atuais do terminal.
    struct termios new_cfg = old_cfg;
    // Desativa as flags ECHO e ICANON, e então os caracteres inseridos não serão exibidos, ...
    new_cfg.c_lflag &= ~(ECHO | ICANON); // ... e estarão disponíveis sem ser necessário pressionar ENTER.
    tcsetattr(STDIN_FILENO, TCSANOW, &new_cfg); // Seta as novas configurações do terminal.
    fputs("\033[6n", stdout); // Pergunta ao terminal a coordenada do cursor.
    scanf("%*c%*c%d%*c%d%*c", y, x); // Ele responderá como \033[y;xR.
    tcsetattr(STDIN_FILENO, TCSANOW, &old_cfg); // Volta às configurações anteriores do terminal.
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