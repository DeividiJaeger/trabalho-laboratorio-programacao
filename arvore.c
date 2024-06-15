#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arvore.h"

// Função para novo no ---------------
No* novoNo(char* dado) {
    No *novo = malloc(sizeof(No));  // Aloca memória para um nó
    if (novo) {
        novo->dado = dado;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    } else {
        printf("Erro ao alocar nó em função novoNo");
    }
    return novo;
}

// --- FATOR DE BALANCEAMENTO --------
short maiorSubArvore(short a, short b) {
    return (a > b) ? a : b;
}
short alturaDoNo(No *no) {
    return (no == NULL) ? -1 : no->altura;
}
short fatorDeBalanceamento(No *no) {
    if (no) {
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita));
    } else {
        return 0;
    }
}
No* rotacaoEsquerda(No *r) {
    No *y, *f;

    y = r->direita;
    f = y->esquerda; // Ponteiro auxiliar para armazenar o possível filho do R -> direita

    y->esquerda = r;
    r->direita = f;

    // Recalcular a altura
    r->altura = maiorSubArvore(alturaDoNo(r->esquerda), alturaDoNo(r->direita) + 1);
    y->altura = maiorSubArvore(alturaDoNo(y->esquerda), alturaDoNo(y->direita) + 1);

    return y;
}
No* rotacaoDireita(No *r) {
    No *y, *f;

    y = r->esquerda;
    f = y->direita; // Ponteiro auxiliar para armazenar o possível filho do R -> direita

    y->direita = r;
    r->esquerda = f;

    // Recalcular a altura
    r->altura = maiorSubArvore(alturaDoNo(r->esquerda), alturaDoNo(r->direita) + 1);
    y->altura = maiorSubArvore(alturaDoNo(y->esquerda), alturaDoNo(y->direita) + 1);

    return y;
}
// -----------------------------------

//Funções de inserção ----------------

//Esse função precisa ser mudada
bool contemNaArvore(No* no, const char* valor) {
    if (no == NULL) {
        return false;
    } else {
        int cmp = strcmp(valor, no->dado);
        if (cmp == 0) {
            return true;
        } else if (cmp < 0) {
            return contemNaArvore(no->esquerda, valor);
        } else {
            return contemNaArvore(no->direita, valor);
        }
    }
}


void inserirEsquerda(No *no, const char *valor) {
    int cmp = strcmp(valor, no->dado);

    if (cmp < 0) {
        if (no->esquerda == NULL) {
            No *novo = novoNo(valor);
            no->esquerda = novo;
        } else {
            inserirEsquerda(no->esquerda, valor);
        }
    } else {
        if (no->direita == NULL) {
            No *novo = novoNo(valor);
            no->direita = novo;
        } else {
            inserirDireita(no->direita, valor);
        }
    }
}

void inserirDireita(No *no, const char *valor) {
    int cmp = strcmp(valor, no->dado);

    if (cmp > 0) {
        if (no->direita == NULL) {
            No *novo = novoNo(valor);
            no->direita = novo;
        } else {
            inserirDireita(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            No *novo = novoNo(valor);
            no->esquerda = novo;
        } else {
            inserirEsquerda(no->esquerda, valor);
        }
    }
}

void inserirNaArvore(const char *valor, Arvore *arvore) {
    if (arvore->raiz == NULL) {
        arvore->raiz = novoNo(valor);
    } else {
        if (contemNaArvore(arvore->raiz, valor)) {
            printf("Erro: A palavra '%s' já foi inserida, insira uma palavra diferente.\n", valor);
            return;
        }
        int cmp = strcmp(valor, arvore->raiz->dado);
        if (cmp < 0) {
            inserirEsquerda(arvore->raiz, valor);
        } else {
            inserirDireita(arvore->raiz, valor);
        }
    }
}

void imprimirArvore(No *raiz) {
    if (raiz == NULL) return;

    printf("%d -> ", raiz->dado);
    imprimirArvore(raiz->esquerda);
    imprimirArvore(raiz->direita);
}

//Funções para geração de palavras aleatórias
