#include <stdio.h>
#include "arvore.h"
#include <stdbool.h>

int main() {
    int valor, opcao;
    Arvore arv;
    arv.raiz = NULL;

    do {
        printf("\nEscolha uma opção:\n"
               "1 - Inserir na árvore binária\n"
               "2 - Imprimir árvore binária\n"
               "3 - Buscar na árvore binária\n"
               "0 - Sair do programa\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Para inserir, digite um valor:\n");
            scanf("%d", &valor);
            inserirNaArvore(valor, &arv);  // Corrigido aqui
            break;
            case 2:
                imprimirArvore(arv.raiz);
            printf("\n");
            break;
            case 3:
                if (arv.raiz == NULL) {
                    printf("Não há elementos para buscar, insira dados na árvore primeiramente!\n");
                } else {
                    printf("Digite o elemento para verificar se contém:\n");
                    scanf("%d", &valor);
                    if (contemNaArvore(arv.raiz, valor)) {
                        printf("Dado encontrado na árvore\n");
                    } else {
                        printf("Dado não encontrado na árvore\n");
                    }
                }
            break;
            case 0:
                printf("Saindo do programa...\n");
            break;
            default:
                printf("Digite um número válido\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
