#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "arvore.h"
#include "unistd.h"

int main() {
    Arvore arv;
    arv.raiz = NULL;
    inicializaTime();

    char* palavraParaRemover = malloc(256 * sizeof(char));  // Aloca memória para a palavra a ser removida
    if (!palavraParaRemover) {
        printf("Erro ao alocar memória para palavraParaRemover\n");
        exit(1);
    }

    time_t startTime = time(NULL);
    while (difftime(time(NULL), startTime) < 15) {
        char* palavraGerada = gerarPalavraAleatoria(10);
        inserirNaArvore(palavraGerada, &arv);
        imprimirArvore(arv.raiz);
        printf("\n");
        sleep(2);
        printf("Digite a palavra a ser removida: \n");
        scanf("%255s", palavraParaRemover);  // Note que estamos usando o espaço de memória alocado
        if(contemNaArvore(arv.raiz, palavraParaRemover)) {
            removerDaArvore(palavraParaRemover, &arv);
        } else {
            printf("Palavra nao contem na arvore tente novamente\n");
        }
    }

    printf("\n");
    printf("Arvore fincou assim no final\n");
    imprimirArvore(arv.raiz);

    free(palavraParaRemover);  // Libera a memória alocada
    return 0;
}
