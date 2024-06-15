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

No* novoNo(const char* dado);  // Mudança no tipo do parâmetro para char*
short maiorSubArvore(short a, short b);
short alturaDoNo(No* no);

// Fator de balanceamento
short fatorDeBalanceamento(No* no);
No* rotacaoEsquerda(No* y);
No* rotacaoDireita(No* x);
//---------------------------

bool contemNaArvore(No* no, const char* valor);  // Mudança no tipo do parâmetro para char*
void inserirEsquerda(No* no, const char* valor);  // Mudança no tipo do parâmetro para char*
void inserirDireita(No* no, const char* valor);  // Mudança no tipo do parâmetro para char*
void inserirNaArvore(const char* valor, Arvore* arvore);  // Mudança no tipo do parâmetro para char*
void imprimirArvore(No* raiz);

#endif
