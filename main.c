#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "arvore.h"
#include "unistd.h"

int main() {
    inicializaTime();

    char* palavraParaRemover = malloc(256 * sizeof(char));  // Aloca memória para a palavra a ser removida
    if (!palavraParaRemover) {
        printf("Erro ao alocar memória para palavraParaRemover\n");
        exit(1);
    }

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

    free(palavraParaRemover);  // Libera a memória alocada
    return 0;
}
