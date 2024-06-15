#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"

// Função para novo no ---------------
No* novoNo(int dado) {
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
bool contemNaArvore(No* no, int valor) {
    if (no == NULL) {
        return false;
    } else if (no->dado == valor) {
        return true;
    } else if (no->dado < valor) {
        return contemNaArvore(no->direita, valor);
    } else {
        return contemNaArvore(no->esquerda, valor);
    }
}
void inserirEsquerda(No *no, int valor) {
    if (no->esquerda == NULL) {
        No *novo = novoNo(valor);
        no->esquerda = novo;
    } else {
        if (valor < no->esquerda->dado) {
            inserirEsquerda(no->esquerda, valor);
        } else {
            inserirDireita(no->esquerda, valor);
        }
    }
}
void inserirDireita(No *no, int valor) {
    if (no->direita == NULL) {
        No *novo = novoNo(valor);
        no->direita = novo;
    } else {
        if (valor > no->direita->dado) {
            inserirDireita(no->direita, valor);
        } else {
            inserirEsquerda(no->direita, valor);
        }
    }
}
void inserirNaArvore(int valor, Arvore *arvore) {
    if (arvore->raiz == NULL) {
        arvore->raiz = novoNo(valor);
    } else {
        if (contemNaArvore(arvore->raiz, valor)) {
            printf("Erro: O valor %d já foi inserido, insira um valor diferente.\n", valor);
            return;
        }
        if (valor < arvore->raiz->dado) {
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
