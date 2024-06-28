#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "telag.h"   
#include "arvore.h"  
#include <time.h>
/*
Para compilar o programa use esse comando: 
gcc -Wall -o jogo main.c telag.c arvore.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro_image -lallegro
*/
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define RAIO_NO 20
#define ESPACO_VERTICAL 50  

// IDs das novas cores
#define VERDE_FOLHA 12
#define MARROM_FRACO 13
#define MARROM_FORTE 14
#define PRETO_FRACO 15


/* Funções auxiliares para meu código */
// Função para finalizar o Allegro
void finalizarAllegro() {
    al_shutdown_image_addon();
    al_uninstall_system();
}

// Função para configurar o background usando Allegro
bool configurarBackground(const char *caminhoImagem) {
    ALLEGRO_BITMAP *imagem = al_load_bitmap(caminhoImagem);
    if (!imagem) {
        fprintf(stderr, "Erro ao carregar a imagem de fundo: %s\n", caminhoImagem);
        return false;
    }

    al_draw_scaled_bitmap(imagem, 0, 0, al_get_bitmap_width(imagem), al_get_bitmap_height(imagem),
                          0, 0, LARGURA_TELA, ALTURA_TELA, 0);

    al_destroy_bitmap(imagem);

    return true;
}

// Função para capturar e processar a entrada do usuário
void capturarEntradaUsuario(char palavra[], int *index, int *pontuacao, Arvore *arvore) {
    while (true) {
        char tecla = tela_tecla();
        if (tecla != '\0') {
            if (tecla == '\n') {
                // Remover a palavra digitada da árvore, se existir
                if (*index > 0) {
                    removerDaArvore(palavra, arvore);
                    // Limpar o texto da palavra digitada
                    *index = 0;
                    palavra[*index] = '\0';
                    *pontuacao += 10;
                }
            } else if (tecla == '\b') {
                if (*index > 0) {
                    (*index)--;
                    palavra[*index] = '\0';
                }
            } else {
                // Adiciona o caractere na palavra sendo digitada
                palavra[(*index)++] = tecla;
                palavra[*index] = '\0';
            }
        } else {
            break; // Se não há tecla pressionada, sai do loop interno
        }
    }
}

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

// Função para desenhar a frase e a pontuação na tela
void desenharFraseEPontuacao(float posicaoX, float posicaoY, int tamanhoTexto, int pontuacao, const char *frase) {
    // Desenha a frase no canto inferior esquerdo da tela
    tela_texto_esq(posicaoX, posicaoY, tamanhoTexto, MARROM_FORTE, frase);

    // Formata o texto da pontuação
    char txt[100];
    sprintf(txt, "Pontuacao: %d", pontuacao);

    // Desenha a pontuação no canto superior direito da tela
    tela_texto(LARGURA_TELA - 150, 20, 15, MARROM_FORTE, txt);
}

int main() {
    tela_inicio(LARGURA_TELA, ALTURA_TELA, "Jogo Árvore de Palavras Abençoadas");
    inicializaTime();

    // Inicialização do Allegro e definição das cores
    al_init();
    tela_altera_cor(VERDE_FOLHA, 0.0156, 0.6117, 0.4588, 1);
    tela_altera_cor(MARROM_FRACO, 0.545, 0.271, 0.075, 1);
    tela_altera_cor(MARROM_FORTE, 0.545, 0.271, 0.075, 0.5);
    tela_altera_cor(PRETO_FRACO, 0.0, 0.0, 0.0, 0.9); 

    Arvore arvore;
    arvore.raiz = NULL;

    // Configuração do texto e da pontuação inicial
    char frase[] = "Digite a palavra a ser removida e pressione enter";
    int tamanhoTexto = 15;
    float margemEsquerda = 575;
    float margemInferior = 20;
    float posicaoX = margemEsquerda;
    float posicaoY = ALTURA_TELA - tamanhoTexto - margemInferior;

    char palavra[100];
    int index = 0;
    int pontuacao = 0;
    bool jogoAtivo = true;

    do {
        // Inicialização do add-on para imagens e configuração do background
        if (!al_init_image_addon()) {
            fprintf(stderr, "Erro ao inicializar o add-on de imagens do Allegro.\n");
            return -1;
        }
        const char *caminhoImagem = "jesus-background.jpg";
        if (!configurarBackground(caminhoImagem)) {
            fprintf(stderr, "Falha ao configurar o background da tela!\n");
        }

        // Inserção de uma palavra aleatória na árvore
        char* palavraAleatoria = gerarPalavraAleatoria(10);
        inserirNaArvore(palavraAleatoria, &arvore);
        free(palavraAleatoria);

        // Captura e processa a entrada do usuário
        capturarEntradaUsuario(palavra, &index, &pontuacao, &arvore);

        // Desenha a árvore na tela
        tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 1, PRETO_FRACO, PRETO_FRACO);
        desenharArvore(arvore.raiz, LARGURA_TELA / 2, 30, LARGURA_TELA / 2, arvore.raiz);

       // Desenha a frase e a pontuação na tela
        desenharFraseEPontuacao(posicaoX, posicaoY, tamanhoTexto, pontuacao, frase);

        // Atualiza a tela e aguarda por 3 segundos
        tela_atualiza();
        sleep(2);
    } while (jogoAtivo && verificarBalanceamento(arvore.raiz));

    tela_fim();
    finalizarAllegro();

    return 0;
}

