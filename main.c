#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "telag.h"
#include "arvore.h"
#include "unistd.h"
/*
 * Para compilar com essa main utiliza-se o comando:
 * gcc -Wall -o jogo main.c telag.c arvore.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro
 *
*/

// Definições da minha tela e desenho da árvore;
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define RAIO_NO 20
#define ESPACO_VERTICAL 50

// IDs das novas cores
#define VERDE_FOLHA 12
#define MARROM_FRACO 13
#define MARROM_FORTE 14

// Função para desenhar a árvore binária
void desenharArvore(No *raiz, float x, float y, float espacamento, No *raizOriginal) {
    if (raiz == NULL) return;

    // Determina a cor do nó: marrom para a raiz, verde folha para as folhas
    int corNo = (raiz == raizOriginal) ? MARROM_FRACO : ((raiz->esquerda == NULL && raiz->direita == NULL) ? VERDE_FOLHA : VERDE_FOLHA);

    // Desenha o nó atual
    tela_texto(x, y, 15, corNo, raiz->dado);

    // Calcula as posições dos filhos
    float xEsquerda = x - espacamento / 2;
    float xDireita = x + espacamento / 2;
    float yFilho = y + ESPACO_VERTICAL;

    // Desenha linha para o filho esquerdo
    if (raiz->esquerda != NULL) {
        tela_linha(x, y, xEsquerda, yFilho, 2, MARROM_FORTE);
        desenharArvore(raiz->esquerda, xEsquerda, yFilho, espacamento / 2, raizOriginal);
    }

    // Desenha linha para o filho direito
    if (raiz->direita != NULL) {
        tela_linha(x, y, xDireita, yFilho, 2, MARROM_FORTE);
        desenharArvore(raiz->direita, xDireita, yFilho, espacamento / 2, raizOriginal);
    }
}

int main() {
    tela_inicio(LARGURA_TELA, ALTURA_TELA, "Desenho da árvore");
    inicializaTime();

    // Define a nova cor verde folha
    tela_altera_cor(VERDE_FOLHA, 0.0156, 0.6117, 0.4588, 1); // #049c75

    // Define a nova cor marrom com transparência de 0.2
    tela_altera_cor(MARROM_FRACO, 0.545, 0.271, 0.075, 1); // Marrom com transparência ajustada

    // Define a nova cor marrom forte sem transparência
    tela_altera_cor(MARROM_FORTE, 0.545, 0.271, 0.075, 0.5); // Marrom forte ajustada para ser mais viva

    Arvore arvore;
    arvore.raiz = NULL;

    // Mensagem a ser exibida no canto inferior esquerdo
    char frase[] = "Digite a palavra a ser removida e pressione enter";
    int tamanhoTexto = 15; // Tamanho do texto em pontos

    // Calcula as coordenadas X e Y para posicionar o texto no centro
    float margemEsquerda = 575; // Margem esquerda
    float margemInferior = 20; // Margem inferior
    float posicaoX = margemEsquerda;
    float posicaoY = ALTURA_TELA - tamanhoTexto - margemInferior;

    char palavra[100];
    int index = 0;
    bool jogoAtivo = true;
    int pontuacao = 0;

    // Laço para inserir palavras aleatórias e desenhar a árvore
    do {
        char* palavraAleatoria = gerarPalavraAleatoria(10);
        inserirNaArvore(palavraAleatoria, &arvore);
        free(palavraAleatoria);

        // Captura a entrada do usuário para remover uma palavra da árvore
        while (true) {
            char tecla = tela_tecla();
            if (tecla != '\0') {
                if (tecla == '\n') {
                    // Remover a palavra digitada da árvore, se existir
                    if (index > 0) {
                        removerDaArvore(palavra, &arvore);
                        // Limpar o texto da palavra digitada
                        index = 0;
                        palavra[index] = '\0';
                        pontuacao += 10;
                    }
                } else if (tecla == '\b') {
                    if (index > 0) {
                        index--;
                        palavra[index] = '\0';
                    }
                } else {
                    // Adiciona o caractere na palavra sendo digitada
                    palavra[index++] = tecla;
                    palavra[index] = '\0';
                }
            } else {
                break; // Se não há tecla pressionada, sai do loop interno
            }
        }

        // Desenha a árvore na tela
        tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 1, preto, preto); // Limpa a tela
        desenharArvore(arvore.raiz, LARGURA_TELA / 2, 30, LARGURA_TELA / 2, arvore.raiz);

        // Desenha a frase no centro da parte inferior da tela
        tela_texto_esq(posicaoX, posicaoY, tamanhoTexto, MARROM_FORTE, frase);

        // Desenha a pontuação no canto superior direito
        char txt[100];
        sprintf(txt, "Pontuacao: %d", pontuacao);
        tela_texto(LARGURA_TELA - 150, 20, 15, MARROM_FORTE, txt);

        // Atualiza a tela
        tela_atualiza();
        sleep(2);
    } while (jogoAtivo && verificarBalanceamento(arvore.raiz));

    tela_fim();
    return 0;
}
