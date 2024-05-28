/*
 * TRABALHO T3 BENHUR <-
 * Vai ser um jogo, onde teremos uma string que será nosso dado
 * Cuidar com strings que tenham acentos
 *
 * Insrir e remover sem precisar equililbrar nossa árvore (não é AVL)
 * Podemos usar qualquer um dos filhos para a esquerda e ou direta de acordo com a remoção (tanto faz)
 *
 * Se a árvore desiquilbrar a árvore morre!
 *
 * Inserção automatica e remoção tem uma regra.
 *
 * Temos que ter um fator de equilibrio então cada nó tem seu dado, filho esq e dir e a altura de seu nó
 * Criar função para que (árvore está equilibrada ou não e não mexe na altura)
 *
 * Inserir e Remover recursivas no retorno precisa olhar e mudar recalcular sua altura!
 *
 * Pode ser dentro ou fora da árvore -> ou o dono da string é o nó (alocando memória para string ou desalocando a memória!)
 *
 * ------------------------------------------------------------------
 * O JOGO <-
 *  -> Vai sempre ler a entrada do usuário. <-
 *  -> Backspace: remove a ultima letra dgitada <-
 *  -> Enter: Vai excluir a palavra. <-
 *  -> Laço tem a detecção de equilibrio de árvore. <-
 *  -> Matar as palavras <-
 *  -> O jogo fica cada vez mais rápido <-
 * ------------------------------------------------------------------
 * SORTEIO DE PALAVRAS <-
 *  -> lista de sílabas
 *  -> Cria uma nova palavra e insere essa palavra
 *  -> Usar a função STRCMP para sortear criar ela -> e então ser inserida na árvore.
 * ------------------------------------------------------------------
 * DESENHA ÁRVORE <-
 *  -> Desenha o primeiro nível da árvore e então seus dois filhos
 *  -> Em que cordenadas vai ser impressa cada filho? <-
 *  -> Função que diz o tamanho de árvore e seu numero de caractéres e seu tamanho de largura do nó da sub árvore
 *  esquerda (Função recursiva) Vamos desenhar a árvore da folha.
 *  -> Podemos usar uma struct que o dado não importa para fazer o cálculo <-
 * -------------------------------------------------------------------
 *
 * */
int main(){
    return 0;
}