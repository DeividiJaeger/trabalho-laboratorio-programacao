#ifndef ARVORE_H
#define ARVORE_H

#include <stdbool.h>

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
short maiorSubArvore(short a, short b);
short alturaDoNo(No* no);

// Fator de balanceamento
short fatorDeBalanceamento(No* no);
No* rotacaoEsquerda(No* y);
No* rotacaoDireita(No* x);

//----------FUNÇÕES DE INSERÇAO - IMPRESSAO E CONTEM NA ARVORE-----------------
bool contemNaArvore(No* no, char* valor);
void inserirNaArvore(char* valor, Arvore* arvore);
void imprimirArvore(No* raiz);

// Função para gerar as palavras pausadas aleatoriamente ---------------------
char* gerarPalavraAleatoria(int tamMaximo);
void inicializaTime();

//----------FUNÇÕES DE REMOÇÃO DE UM NÓ DA ARVORE -----------------
void removerDaArvore(char* valor, Arvore* arvore);




#endif
