/**
 * @author Mateus Coutinho
 */

#pragma once

#define OK  (0)
#define ERR (-1)

/**
 * Salva o estado atual do terminal e entra na tela alternativa.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int initscr(void) __attribute__((__constructor__));

/**
 * Restaura o estado inicial do terminal e sai da tela alternativa.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int endwin(void) __attribute__((__destructor__));

/**
 * Ativa o ECHO.
 * Faz com que os caracteres inseridos sejam exibidos.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int echo(void);

/**
 * Desativa o ECHO.
 * Faz com que os caracteres inseridos não sejam exibidos.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int noecho(void);

/**
 * Desativa o CANONICAL MODE.
 * Faz com que os caracteres inseridos estejam disponíveis imediatamente.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int cbreak(void);

/**
 * Ativa o CANONICAL MODE.
 * Faz com que os caracteres inseridos só estejam disponíveis após uma nova linha.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int nocbreak(void);

/**
 * Ativa ou desativa o NONBLOCK MODE.
 * Quando ativado, faz com que funções como getchar() retornem EOF se não tiverem caracteres para ler.
 * @param delay 0 para ativar e -1 para desativar.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int timeout(int delay);

/**
 * Limpa a janela do terminal e move o cursor para o canto superior esquerdo.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int clrscr(void);

/**
 * Limpa do cursor até o final da janela.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int clrtobot(void);

/**
 * Limpa do cursor até o final da linha.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int clrtoeol(void);

/**
 * Lê um caractere inserido sem esperar por uma nova linha e sem o exibir.
 * @return O caractere se tiver sucesso e ERR caso falhar.
 */
int getch(void);

/**
 * Lê um caractere inserido sem esperar por uma nova linha e o exibe.
 * @return O caractere se tiver sucesso e ERR caso falhar.
 */
int getche(void);

/**
 * Checa se algum caractere foi inserido (e ainda não foi lido).
 * @return 1 se algum caractere foi inserido e 0 caso contrário.
 */
int kbhit(void);

/**
 * Limpa o buffer de entradas.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int clrbuf(void);

/**
 * Move o cursor até a coluna X e linha Y.
 * A posição é relativa ao canto superior esquerdo da janela, que é (1,1).
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int gotoxy(int x, int y);

/**
 * Move o cursor até a coluna X.
 * A posição é relativa ao canto superior esquerdo da janela, que é (1,1).
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int gotox(int x);

/**
 * Move o cursor até a linha Y.
 * A posição é relativa ao canto superior esquerdo da janela, que é (1,1).
 * Falha se algum caractere inserido não foi lido e o buffer de entradas não está limpo.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int gotoy(int y);

/**
 * Guarda as coordenadas atuais do cursor em X e Y.
 * A posição é relativa ao canto superior esquerdo da janela, que é (1,1).
 * Falha se algum caractere inserido não foi lido e o buffer de entradas não está limpo.
 * @return OK se tiver sucesso e ERR caso falhar.
 */
int wherexy(int *x, int *y);

/**
 * Obtém a coordenada X atual do cursor.
 * A posição é relativa ao canto superior esquerdo da janela, que é (1,1).
 * Falha se algum caractere inserido não foi lido e o buffer de entradas não está limpo.
 * @return a coordenada X atual do cursor ou ERR caso falhar.
 */
int wherex(void);

/**
 * Obtém a coordenada Y atual do cursor.
 * A posição é relativa ao canto superior esquerdo da janela, que é (1,1).
 * Falha se algum caractere inserido não foi lido e o buffer de entradas não está limpo.
 * @return a coordenada Y atual do cursor ou ERR caso falhar.
 */
int wherey(void);

#define $0  "\x1b[30m"  // Letra preta
#define $1  "\x1b[34m"  // Letra azul-escura
#define $2  "\x1b[32m"  // Letra verde-escura
#define $3  "\x1b[36m"  // Letra ciano-escura
#define $4  "\x1b[31m"  // Letra vermelho-escura
#define $5  "\x1b[35m"  // Letra magenta-escura
#define $6  "\x1b[33m"  // Letra amarelo-escura
#define $7  "\x1b[37m"  // Letra cinza-clara
#define $8  "\x1b[90m"  // Letra cinza-escura
#define $9  "\x1b[94m"  // Letra azul-clara
#define $a  "\x1b[92m"  // Letra verde-clara
#define $b  "\x1b[96m"  // Letra ciano-clara
#define $c  "\x1b[91m"  // Letra vermelho-clara
#define $d  "\x1b[95m"  // Letra magenta-clara
#define $e  "\x1b[93m"  // Letra amarelo-clara
#define $f  "\x1b[97m"  // Letra branca
#define $0b "\x1b[40m"  // Fundo preto
#define $1b "\x1b[44m"  // Fundo azul-escuro
#define $2b "\x1b[42m"  // Fundo verde-escuro
#define $3b "\x1b[46m"  // Fundo ciano-escuro
#define $4b "\x1b[41m"  // Fundo vermelho-escuro
#define $5b "\x1b[45m"  // Fundo magenta-escuro
#define $6b "\x1b[43m"  // Fundo amarelo-escuro
#define $7b "\x1b[47m"  // Fundo cinza-claro
#define $8b "\x1b[100m" // Fundo cinza-escuro
#define $9b "\x1b[104m" // Fundo azul-claro
#define $ab "\x1b[102m" // Fundo verde-claro
#define $bb "\x1b[106m" // Fundo ciano-claro
#define $cb "\x1b[101m" // Fundo vermelho-claro
#define $db "\x1b[105m" // Fundo magenta-claro
#define $eb "\x1b[103m" // Fundo amarelo-claro
#define $fb "\x1b[107m" // Fundo branco
#define $i  "\x1b[7m"   // Invertido
#define $j  "\x1b[2m"   // Escurecido
#define $k  "\x1b[5m"   // Piscando
#define $l  "\x1b[1m"   // Negrito
#define $m  "\x1b[9m"   // Riscado
#define $n  "\x1b[4m"   // Sublinhado
#define $nn "\x1b[21m"  // Sublinhado duplo
#define $o  "\x1b[3m"   // Itálico
#define $r  "\x1b[0m"   // Resetar