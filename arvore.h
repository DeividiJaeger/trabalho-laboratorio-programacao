#ifndef ARVORE_H
#define ARVORE_H

#include <stdbool.h>

//---------- ESTRUTURA DA ARVORE, SEU NO E SUA ARVORE ------------
typedef struct no {
    char* dado;
    short altura;
    struct no* esquerda;
    struct no* direita;
} No;
typedef struct {
    No* raiz;
} Arvore;
No* novoNo(char* dado);

//----------FUNÇÕES DE INSERÇAO- CONTEM NA ARVORE-----------------
bool contemNaArvore(No* no, char* valor);
void inserirNaArvore(char* valor, Arvore* arvore);

//----------FUNÇÕES DE DESENHO E IMPRESSAO DA ARVORE---------------
void imprimirArvore(No* raiz);

//----------FUNÇÕES QUE GERAM A PALAVRA E INCIALIZA SEU TEMPO-----
char* gerarPalavraAleatoria(int tamMaximo);
void inicializaTime();

//----------FUNÇÕES DE REMOÇÃO DE UM NÓ DA ARVORE -----------------
void removerDaArvore(char* valor, Arvore* arvore);

//---------FUNÇÃO PARA VERIFICAR SE ARVORE ESTA BALANCEADA PARA O JOGO -----------
bool verificarBalanceamento(No *no);

#endif