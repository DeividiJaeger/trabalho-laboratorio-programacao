#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "arvore.h"

// Prototipos das funcoes
No* novoNo(char* dado);
void inicializaTime();
char* gerarPalavraAleatoria(int tamMaximo);
void inserirEsquerda(No *no, char *valor);
void inserirDireita(No *no, char *valor);
void inserirNaArvore(char *valor, Arvore *arvore);
void imprimirArvore(No *raiz);
void removerDaArvore(char* valor, Arvore* arvore);
bool contemNaArvore(No* no, char* valor);
short maiorSubArvore(short a, short b);
short alturaDoNo(No* no);
short fatorDeBalanceamento(No *no);
bool verificarBalanceamento(No *no);

/***********************************************************/

//Essas funções precisaram ser mudadas
No* rotacaoEsquerda(No *r);
No* rotacaoDireita(No *r);

// Função para novo no ---------------
No* novoNo(char* dado) {
    No *novo = malloc(sizeof(No));  // Aloca memória para um nó
    if (novo) {
        novo->dado = strdup(dado);  // Copia a string para garantir a alocação correta
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    } else {
        printf("Erro ao alocar nó em função novoNo");
    }
    return novo;
}

// --- FATOR DE BALANCEAMENTO--------
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
bool arvoreEstaBalanceada(Arvore* arv, No* no) {
    if(arv->raiz == NULL) {
        return true;
    }
    short balanceamento = fatorDeBalanceamento(arv->raiz);

    if(balanceamento < -1 || balanceamento > 1) {
        return false;
    }
    //Recursao para verificar os filhos direitos e esquerdos
    return arvoreEstaBalanceada(arv, no->esquerda) && arvoreEstaBalanceada(arv, no->direita);
}
short maiorSubArvore(short a, short b) {
    return (a > b) ? a : b;
}
short alturaDoNo(No *no) {
    if (no == NULL) return -1;
    return 1 + maiorSubArvore(alturaDoNo(no->esquerda), alturaDoNo(no->direita));
}
short fatorDeBalanceamento(No *no) {
    if (no == NULL) return 0;
    return alturaDoNo(no->esquerda) - alturaDoNo(no->direita);
}
bool verificarBalanceamento(No *no) {
    if (no == NULL) return true;

    short fb = fatorDeBalanceamento(no);
    if (abs(fb) > 1) return false;

    return verificarBalanceamento(no->esquerda) && verificarBalanceamento(no->direita);
}

No* balancearNo(No* no) {
    int fb = fatorDeBalanceamento(no);
    if(fb > 1) {
        if(fatorDeBalanceamento(no->esquerda) < 0) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
        }
        no = rotacaoDireita(no);
    } else if(fb < -1) {
        if(fatorDeBalanceamento(no->direita) > 0) {
            no->direita = rotacaoDireita(no->direita);
        }
        no->direita = rotacaoDireita(no->direita);
    }
    return no;
}
//Funções para geração de palavras aleatórias------------
const char* sequencia [] = {
        "ba", "be", "bi", "bo", "bu",
        "ca", "ce", "ci", "co", "cu",
        "da", "de", "di", "do", "du",
        "fa", "fe", "fi", "fo", "fu",
        "ga", "ge", "gi", "go", "gu",
        "ha", "he", "hi", "ho", "hu",
        "ja", "je", "ji", "jo", "ju",
        "ka", "ke", "ki", "ko", "ku",
        "la", "le", "li", "lo", "lu",
        "ma", "me", "mi", "mo", "mu",
        "na", "ne", "ni", "no", "nu",
        "pa", "pe", "pi", "po", "pu",
        "ra", "re", "ri", "ro", "ru",
        "sa", "se", "si", "so", "su",
        "ta", "te", "ti", "to", "tu",
        "va", "ve", "vi", "vo", "vu",
        "xa", "xe", "xi", "xo", "xu",
        "za", "ze", "zi", "zo", "zu"
};
const int numSequencias = sizeof(sequencia) / sizeof(sequencia[0]);
int intAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}
// Função para gerar a palavra aleatoria e retorna essa palavra gerada
char* gerarPalavraAleatoria(int tamMaximo) {
    int tamanho = intAleatorio(2, tamMaximo);
    char* palavra = malloc((tamanho + 1) * sizeof(char));  // Aloca memória para a palavra
    if (!palavra) {
        printf("Erro ao alocar memória para a palavra\n");
        exit(1);
    }
    palavra[0] = '\0';  // Inicializa a string com o terminador nulo
    for (int i = 0; i < tamanho; i += 2) {
        int indice = intAleatorio(0, numSequencias - 1);
        strcat(palavra, sequencia[indice]);
    }
    palavra[tamanho] = '\0';
    return palavra;
}
/*
 * Função que incializa o tempo para poder ser chamado
 * a função de gerar a palavra pausadamente;
*/
void inicializaTime() {
    srand(time(NULL));
}

//Funções de inserção na árvore----------------
bool contemNaArvore(No* no, char* valor) {
    if (no == NULL) {
        return false;
    } else {
        int cmp = strcmp(valor, no->dado);
        if (cmp == 0) {
            return true;
        } else if (cmp < 0) {
            return contemNaArvore(no->esquerda, valor);
        } else {
            return contemNaArvore(no->direita, valor);
        }
    }
}
void inserirEsquerda(No *no, char *valor) {
    int cmp = strcmp(valor, no->dado);

    if (cmp < 0) {
        if (no->esquerda == NULL) {
            No *novo = novoNo(valor);
            no->esquerda = novo;
        } else {
            inserirEsquerda(no->esquerda, valor);
        }
    } else {
        if (no->direita == NULL) {
            No *novo = novoNo(valor);
            no->direita = novo;
        } else {
            inserirDireita(no->direita, valor);
        }
    }
}
void inserirDireita(No *no, char *valor) {
    int cmp = strcmp(valor, no->dado);

    if (cmp > 0) {
        if (no->direita == NULL) {
            No *novo = novoNo(valor);
            no->direita = novo;
        } else {
            inserirDireita(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            No *novo = novoNo(valor);
            no->esquerda = novo;
        } else {
            inserirEsquerda(no->esquerda, valor);
        }
    }
}
void inserirNaArvore(char *valor, Arvore *arvore) {
    if (arvore->raiz == NULL) {
        arvore->raiz = novoNo(valor);
    } else {
        if (contemNaArvore(arvore->raiz, valor)) {
            printf("Erro: A palavra '%s' já foi inserida, insira uma palavra diferente.\n", valor);
            return;
        }
        int cmp = strcmp(valor, arvore->raiz->dado);
        if (cmp < 0) {
            inserirEsquerda(arvore->raiz, valor);
        } else {
            inserirDireita(arvore->raiz, valor);
        }
    }
}
void imprimirArvore(No *raiz) {
    if (raiz == NULL) return;

    printf("%s -> ", raiz->dado);
    imprimirArvore(raiz->esquerda);
    imprimirArvore(raiz->direita);
}

// Função de remoção da arvore binaria
No* encontrarMinimo(No *no) {
    if(no == NULL) {
        return NULL;
    }
    while (no->esquerda != NULL) {
        no = no->esquerda;
    }
    return no;
}
No* removerNo(No* no, char* valor) {
    if(no == NULL) return NULL;
    int cmp = strcmp(valor, no->dado);

    if(cmp < 0) {
        no->esquerda = removerNo(no->esquerda, valor);
    }else if(cmp > 0) {
        no->direita = removerNo(no->direita, valor);
    }else { // Caso 1 e 2 são no sem filho ou apenas com um filho
        if(no->esquerda == NULL) {
            No* temporario = no->direita;
            free(no->dado);
            free(no);
            return temporario;
        }else if(no->direita == NULL){
            No* temporario = no->esquerda;
            free(no->dado);
            free(no);
            return temporario;
        }

        //Terceiro caso 3º - No com dois filhos
        //Encontra o no minimo da sub arvore direita
        No* temporario = encontrarMinimo(no->direita);

        free(no->dado);
        no->dado = strdup(temporario->dado);
        no->direita = removerNo(no->direita, temporario->dado);
    }
    return no;
}
void removerDaArvore(char* valor, Arvore* arvore) {
    arvore->raiz = removerNo(arvore->raiz, valor);
}

// Funções de balanceamento da minha árvore
