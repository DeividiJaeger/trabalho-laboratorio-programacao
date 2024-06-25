#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "telag.h"
#include <time.h>
#include "arvore.h"
#include "unistd.h"

// Definições da minha tela e desenho da arvore;
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
    tela_inicio(800, 600, "Desenho da árvore");
    inicializaTime();

    Arvore arvore;
    arvore.raiz = NULL;

    // Mensagem a ser exibida no canto inferior esquerdo
    char frase[] = "Digite aqui a palavra a ser removida: ";
    int tamanhoTexto = 15; // Tamanho do texto em pontos

    // Calcula as coordenadas X e Y para posicionar o texto no canto inferior esquerdo
    float margemEsquerda = 300; // Margem esquerda
    float margemInferior = 20; // Margem inferior
    float posicaoX = margemEsquerda;
    float posicaoY = ALTURA_TELA - tamanhoTexto - margemInferior;

    char palavra[100];
    int index = 0;
    bool jogoAtivo = true;

    // Laço para inserir palavras aleatórias e desenhar a árvore
    do {
        char* palavraAleatoria = gerarPalavraAleatoria(10);
        inserirNaArvore(palavraAleatoria, &arvore);
        free(palavraAleatoria);

        // Desenha a árvore na tela
        tela_retangulo(0, 0, 800, 600, 1, preto, preto); // Limpa a tela
        desenharArvore(arvore.raiz, 400, 30, 400);

        // Desenha a frase no centro da parte inferior da tela
        tela_texto_esq(posicaoX, posicaoY, tamanhoTexto, COR_TEXTO, frase);

        // Processa as teclas pressionadas
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

                        // Redesenhar a árvore após a remoção
                        tela_retangulo(0, 0, 800, 600, 1, preto, preto); // Limpa a tela
                        desenharArvore(arvore.raiz, 400, 30, 400);
                        break; // Encerra a entrada ao pressionar Enter
                    }
                } else if (tecla == '\b') {
                    // Backspace: remover o último caractere da palavra se houver
                    if (index > 0) {
                        index--;
                        palavra[index] = '\0';
                    }
                } else {
                    // Adiciona o caractere na palavra sendo digitada
                    palavra[index++] = tecla;
                    palavra[index] = '\0';
                }
                tela_atualiza();
            } else {
                break; // Se não há tecla pressionada, sai do loop interno
            }
        }

        // Atualiza a tela
        tela_atualiza();
        sleep(3);
    } while (jogoAtivo && verificarBalanceamento(arvore.raiz));

    tela_fim();
    return 0;
}
