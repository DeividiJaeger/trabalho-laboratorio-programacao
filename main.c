#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "arvore.h"
#include "unistd.h"

int main() {
    inicializaTime();

    Arvore arvore;
    arvore.raiz = NULL;

    // Inserir algumas palavras na árvore
    inserirNaArvore("segogucora", &arvore);
    inserirNaArvore("botusarili", &arvore);
    inserirNaArvore("cip", &arvore);

    // Verificar se a árvore está balanceada
    if (verificarBalanceamento(arvore.raiz)) {
        printf("A árvore está balanceada.\n");
    } else {
        printf("A árvore está desequilibrada.\n");
    }

    // Remover uma palavra da árvore
    removerDaArvore("botusarili", &arvore);

    // Verificar se a árvore está balanceada após a remoção
    if (verificarBalanceamento(arvore.raiz)) {
        printf("A árvore está balanceada após a remoção.\n");
    } else {
        printf("A árvore está desequilibrada após a remoção.\n");
    }

    return 0;
}
