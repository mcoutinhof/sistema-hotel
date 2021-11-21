#pragma once

// Limpa a tela e coloca o cursor no início.
void clrscr();

// Limpa do cursor ao final da tela.
void clrtobot();

// Limpa do cursor ao final da linha.
void clrtoeol();

// Lê um caractere sem necessidade de apertar ENTER, mas não o escreve na tela.
int getch();

// Move o cursor para a coluna x e linha y.
void gotoxy(int x, int y);

// Guarda o número da coluna em x e o número da linha em y.
void wherexy(int *x, int *y);

#define $0  "\033[30m"  // Letra preta
#define $1  "\033[34m"  // Letra azul-escura
#define $2  "\033[32m"  // Letra verde-escura
#define $3  "\033[36m"  // Letra ciano-escura
#define $4  "\033[31m"  // Letra vermelho-escura
#define $5  "\033[35m"  // Letra magenta-escura
#define $6  "\033[33m"  // Letra amarelo-escura
#define $7  "\033[37m"  // Letra cinza-clara
#define $8  "\033[90m"  // Letra cinza-escura
#define $9  "\033[94m"  // Letra azul-clara
#define $a  "\033[92m"  // Letra verde-clara
#define $b  "\033[96m"  // Letra ciano-clara
#define $c  "\033[91m"  // Letra vermelho-clara
#define $d  "\033[95m"  // Letra magenta-clara
#define $e  "\033[93m"  // Letra amarelo-clara
#define $f  "\033[97m"  // Letra branca
#define $0b "\033[40m"  // Fundo preto
#define $1b "\033[44m"  // Fundo azul-escuro
#define $2b "\033[42m"  // Fundo verde-escuro
#define $3b "\033[46m"  // Fundo ciano-escuro
#define $4b "\033[41m"  // Fundo vermelho-escuro
#define $5b "\033[45m"  // Fundo magenta-escuro
#define $6b "\033[43m"  // Fundo amarelo-escuro
#define $7b "\033[47m"  // Fundo cinza-claro
#define $8b "\033[100m" // Fundo cinza-escuro
#define $9b "\033[104m" // Fundo azul-claro
#define $ab "\033[102m" // Fundo verde-claro
#define $bb "\033[106m" // Fundo ciano-claro
#define $cb "\033[101m" // Fundo vermelho-claro
#define $db "\033[105m" // Fundo magenta-claro
#define $eb "\033[103m" // Fundo amarelo-claro
#define $fb "\033[107m" // Fundo branco
#define $i  "\033[7m"   // Invertido
#define $j  "\033[2m"   // Escurecido
#define $k  "\033[5m"   // Piscando
#define $l  "\033[1m"   // Negrito
#define $m  "\033[9m"   // Riscado
#define $n  "\033[4m"   // Sublinhado
#define $nn "\033[21m"  // Sublinhado duplo
#define $o  "\033[3m"   // Itálico
#define $r  "\033[0m"   // Resetar