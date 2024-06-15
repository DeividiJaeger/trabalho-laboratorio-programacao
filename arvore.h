#ifndef ARVORE_H
#define ARVORE_H

#include <stdbool.h>

typedef struct no {
    int dado;
    short altura;
    struct no* esquerda;
    struct no* direita;
} No;

typedef struct {
    No* raiz;
} Arvore;

No* novoNo(int valor);
short maiorSubArvore(short a, short b);
short alturaDoNo(No* no);

//Fator de balanceamento
short fatorDeBalanceamento(No* no);
No* rotacaoEsquerda(No* y);
No* rotacaoDireita(No* x);
//---------------------------

bool contemNaArvore(No* no, int valor);
void inserirEsquerda(No* no, int valor);
void inserirDireita(No* no, int valor);
void inserirNaArvore(int valor, Arvore* arvore);
void imprimirArvore(No* raiz);

#endif
