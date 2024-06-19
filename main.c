#include <stdio.h>
#include "arvore.h"
#include <stdbool.h>
#include <time.h>
#include "unistd.h"

int main() {
    Arvore arv;
    arv.raiz = NULL;
    inicializaTime();

    time_t startTime = time(NULL);
    while (difftime(time(NULL), startTime) < 15) {
        char* palavraGerada = gerarPalavraAleatoria(10);
        inserirNaArvore(palavraGerada, &arv);
        imprimirArvore(arv.raiz);
        sleep(2);
        printf("\n");
    }
    return 0;
}
