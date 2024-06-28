#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "telag.h"
#include "arvore.h"
#include <unistd.h>
/*
 * Para compilar com essa main alternativa utiliza-se o comando:
 * gcc -Wall -o jogo mainAlternativa.c telag.c arvore.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro
 *
*/


// Definições da minha tela e desenho da árvore
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define RAIO_NO 20
#define ESPACO_VERTICAL 50
#define COR_TEXTO rosa

// Função para desenhar a árvore binária
void desenharArvore(No *raiz, float x, float y, float espacamento) {
    int cinza_escuro = 11; // ID da cor personalizada
    tela_altera_cor(cinza_escuro, 0.2, 0.2, 0.2, 0); // Define a cor cinza escuro (valores de RGB iguais)

    if (raiz == NULL) return;

    // Desenha o nó atual
    tela_texto(x, y, 15, COR_TEXTO, raiz->dado);

    // Calcula as posições dos filhos
    float xEsquerda = x - espacamento / 2;
    float xDireita = x + espacamento / 2;
    float yFilho = y + ESPACO_VERTICAL;

    // Desenha linha para o filho esquerdo
    if (raiz->esquerda != NULL) {
        tela_linha(x, y, xEsquerda, yFilho, 2, cinza_escuro);
        desenharArvore(raiz->esquerda, xEsquerda, yFilho, espacamento / 2);
    }

    // Desenha linha para o filho direito
    if (raiz->direita != NULL) {
        tela_linha(x, y, xDireita, yFilho, 2, cinza_escuro);
        desenharArvore(raiz->direita, xDireita, yFilho, espacamento / 2);
    }
}

int main() {
    tela_inicio(LARGURA_TELA, ALTURA_TELA, "Desenho da árvore");
    inicializaTime();

    Arvore arvore;
    arvore.raiz = NULL;

    do {
        // Gera palavras aleatórias e insere na árvore
        char *palavraAleatoria = gerarPalavraAleatoria(10);
        inserirNaArvore(palavraAleatoria, &arvore);
        free(palavraAleatoria);

        // Desenha a árvore na tela
        tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 1, preto, preto);
        desenharArvore(arvore.raiz, LARGURA_TELA / 2, 30, LARGURA_TELA / 2);

        // Atualiza a tela
        tela_atualiza();
        sleep(3);

        // Captura a palavra para remover da árvore
        char palavra[100];
        printf("Digite uma palavra para remover da árvore: ");
        scanf("%s", palavra);

        // Verifica se a palavra está na árvore e remove se existir
        if (contemNaArvore(arvore.raiz, palavra)) {
            removerDaArvore(palavra, &arvore);

            // Limpa a tela e redesenha a árvore após a remoção
            tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 1, preto, preto);
            desenharArvore(arvore.raiz, LARGURA_TELA / 2, 30, LARGURA_TELA / 2);
            tela_atualiza();
            sleep(3); // Apenas para visualizar a árvore após a remoção
        } else {
            printf("A palavra '%s' não foi encontrada na árvore.\n", palavra);
        }

    } while (verificarBalanceamento(arvore.raiz));

    tela_fim();
    return 0;
}
