// **_________________________________________________**
//  |*TRABALHO DE ESTRUTURAS DE DADOS II, ARVORES AVL*|
//  |ALUNO: IGOR OLIVEIRA DUARTE                      |
//  |CURSO: CIENCIA DE DADOS E INTELIGENCIA ARTIFICIAL|
//  |TURMA: 2000                                      | 
//  |_________________________________________________| 
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    #define true 1
    #define false 0

    typedef int bool;
    typedef int TIPOCHAVE;

    typedef struct aux {
        TIPOCHAVE chave;
        struct aux *esq;
        struct aux *dir;
        int bal; 
    } NO, *PONT;


    PONT criarNovoNo(TIPOCHAVE ch){
        PONT novoNo = (PONT)malloc(sizeof(NO));
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->chave = ch;
        novoNo->bal = 0;
        return novoNo;
    }


    int max(int a, int b){
        if (a>b) return a;
        return b;
    }

    int altura(PONT p){
        if (!p) return -1;
        else return 1 + max(altura(p->esq),altura(p->dir));
    }



    void exibirArvoreEmOrdem(PONT raiz){
        if (raiz == NULL) return;
        exibirArvoreEmOrdem(raiz->esq);
        printf("(%i) ",raiz->chave);
        exibirArvoreEmOrdem(raiz->dir);
    }


    void exibirArvorePreOrdem(PONT raiz){
        if (raiz == NULL) return;
        printf("%i ",raiz->chave);
        exibirArvorePreOrdem(raiz->esq);
        exibirArvorePreOrdem(raiz->dir);
    }

    void exibirArvorePosOrdem(PONT raiz){
        if (raiz == NULL) return;
        exibirArvorePosOrdem(raiz->esq);
        exibirArvorePosOrdem(raiz->dir);
        printf("%i ",raiz->chave);
    }

    void exibirArvore(PONT raiz){
        if (raiz == NULL) return;
        printf("%i[%i]",raiz->chave,raiz->bal);
        printf("(");     
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");     
    }


    //variável de impressão que mostra de forma hierarquica a AVL junto com o fator de balanceamento. 
    //Raiz
    //   |Raiz[0]
    //  |--Filho[0]
    //  │   |--Neto[0]
    //  │   |__Neto[0]
    //  |--Neto[0]
    // exemplo encontado em https://www.baeldung.com/java-print-binary-tree-diagram
    void imprimirHierarquiaAVL(PONT no, const char* prefixo, int isLeft){
        if(no!=NULL){
            printf("%s", prefixo);
            printf("%s", isLeft ? "|---"  : "|___");

            printf("%d[%d]\n", no->chave, no->bal);
            
            char* novoPrefixo = malloc((strlen(prefixo)+5)* sizeof(char));
            if (novoPrefixo == NULL) {
                fprintf(stderr, "Erro ao alocar memoria para novoPrefixo.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(novoPrefixo, prefixo);
            strcat(novoPrefixo, isLeft ? "|   " : "    ");

            imprimirHierarquiaAVL(no->esq, novoPrefixo, 1);
            imprimirHierarquiaAVL(no->dir, novoPrefixo,0);

            free(novoPrefixo);

        }
    }
    //inicializador de impressão
    void imprimirDesenho(PONT raiz){
        if(raiz ==NULL){
            printf("AVL vazia!\n");
            return;
        }
        printf("Estrutura da AVL:\n");
        printf("(O numero entre colchetes e o fator de balanceamento)\n");
        imprimirHierarquiaAVL(raiz,"",0);
    }
    

    int  contadorNos(PONT raiz)
    {
        if (raiz == NULL) return 0;
        return 1 + contadorNos(raiz->esq) + contadorNos(raiz->dir);
    }

    int contadorFolhas(PONT raiz)
    {
        if (raiz == NULL) return 0;
        if (raiz->esq == NULL && raiz->dir == NULL) return 1;
        return contadorFolhas(raiz->esq) + contadorFolhas(raiz->dir);
    }

    int nivelNo(PONT raiz, int chave, int nivel){
        if(raiz== NULL)return -1;
        if (raiz->chave == chave)return nivel;
        int esq =nivelNo(raiz->esq,chave,  nivel+1);
        if(esq != -1){
            return esq;
        }
        return nivelNo(raiz->dir, chave, nivel+1);
    }
    // A função verifica se todas as folhas da árvore AVL estão no mesmo nível. A função percorre a árvore, verificando o nível de cada folha e comparando com o nível da primeira folha encontrada.
    int verificarNivelFolhas(PONT raiz, int nivelAtual, int* nivelFolha) {
        if (raiz == NULL) return true;
        if (raiz->esq == NULL && raiz->dir == NULL) {
            if (*nivelFolha == -1) {
                *nivelFolha = nivelAtual;
                return true;
            } else {
                return (nivelAtual == *nivelFolha);
            }
        }
        return verificarNivelFolhas(raiz->esq, nivelAtual + 1, nivelFolha) && verificarNivelFolhas(raiz->dir, nivelAtual + 1, nivelFolha);
    }

    // A função totalFolhas calcula o número total de folhas na árvore AVL. Uma folha é um nó que não possui filhos.
    int totalFolhas(PONT raiz) {
        int nivelFolha = -1;
        if (verificarNivelFolhas(raiz, 0, &nivelFolha)){
            return contadorFolhas(raiz);
        }else{
            return 0;
        }
    }

    // A função calcula a altura da árvore AVL. A altura é definida como o número máximo de arestas entre a raiz e uma folha.
    int MostraAltura(PONT raiz) {
        if (raiz == NULL) return -1;
        int altEsq = altura(raiz->esq);
        int altDir = altura(raiz->dir);
        return (altEsq > altDir ? altEsq : altDir) + 1;
    }

    // Verifica se dois nós estão no mesmo nível na árvore AVL. A função percorre a árvore, verificando o nível de cada nó e comparando com os níveis dos nós fornecidos.
    int mesmoNivel(PONT raiz, TIPOCHAVE x, TIPOCHAVE y){
        int nivelX= nivelNo(raiz, x, 0);
        int nivelY = nivelNo(raiz, y, 0);
        return(nivelX != -1&& nivelX==nivelY);
    }
    // Encontra o maior valor na árvore AVL. A função percorre a árvore em busca do nó mais à direita, que contém o maior valor.
    PONT encontraMaior(PONT raiz){
        if(!raiz) return NULL;
        PONT atual = raiz;
        while(atual->dir != NULL){
            atual = atual->dir;
        }
        return atual;
    }
    // Encontra o menor valor na árvore AVL. A função percorre a árvore em busca do nó mais à esquerda, que contém o menor valor.
    // A função retorna o nó correspondente ao menor valor encontrado.
    PONT encontraMenor(PONT raiz){
        if(!raiz) return NULL;
        PONT atual = raiz;
        while(atual->esq != NULL){
            atual = atual->esq;
        }
        return atual;
    }


    // Verifica se todas as folhas estão no mesmo nível. A função percorre a árvore, verificando o nível de cada folha e comparando com o nível da primeira folha encontrada.
    // Se todas as folhas estiverem no mesmo nível, a função retorna 1 (verdadeiro); caso contrário, retorna 0 (falso).
    int todasFolhasMesmoNivel(PONT raiz){
        int nivelFolha = -1;
        return verificarNivelFolhas(raiz, 0, &nivelFolha);
    }
    // Soma de todos os valores da árvore AVL. A função percorre a árvore em pré-ordem, somando os valores de cada nó.
    // A função utiliza recursão para percorrer os nós da árvore e calcular a soma total.
    int somaValor(PONT raiz){
        if(raiz ==NULL){
            return 0;
        }
        return raiz->chave+ somaValor(raiz->esq)+ somaValor(raiz->dir);
        
    }

    PONT rotacaoL(PONT p){
        printf("Rotacao a esquerda, problema no no: %i\n",p->chave);
        PONT u, v;
        u = p->esq;
        if(u->bal == -1) {   // LL
            p->esq = u->dir;
            u->dir = p;
            p->bal = 0;
            u->bal = 0;
            return u;
        } else if (u->bal == 1) {  // LR
            v = u->dir;
            u->dir = v->esq;
            v->esq = u;
            p->esq = v->dir;
            v->dir = p;
            if(v->bal == -1) p->bal = 1;
            else p->bal = 0;
            if(v->bal == 1) u->bal = -1;
            else u->bal = 0;
            v->bal = 0;
            return v;
        }else{   
            p->esq = u->dir;
            u->dir = p;
        
            u->bal = 1;
            return u;
        }
    }


    PONT rotacaoR(PONT p){
        printf("Rotacao a direita, problema no no: %i\n",p->chave);
        PONT u, v;
        u = p->dir;
        if(u->bal == 1) {   // RR
            p->dir = u->esq;
            u->esq = p;
            p->bal = 0;
            u->bal = 0;
            return u;
        } else if (u->bal == -1){  // RL
            v = u->esq;
            u->esq = v->dir;
            v->dir = u;
            p->dir = v->esq;
            v->esq = p;
            if(v->bal == 1) p->bal = -1;
            else p->bal = 0;
            if(v->bal == -1) u->bal = 1;
            else u->bal = 0;
            v->bal = 0;
            return v;
        }else{   
            p->dir = u->esq;
            u->esq = p;
            u->bal = -1;

            return u;	
        }
    }


    void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou){
    
        PONT p = *pp;
        
        
        if(!p){

            *pp = criarNovoNo(ch);
            
            *alterou = true;
        } else {
        
            if(ch == p->chave) 
                *alterou = false;
            
            else if(ch <= p->chave) {
            
                inserirAVL(&(p->esq), ch, alterou);
    
                if(*alterou)
                    switch (p->bal) {
                    
                        case 1:
                            p->bal = 0;      
                            *alterou = false;
                            break;
                    
                        case 0:
                            p->bal = -1;     
                            break;
                    
                        case -1:
                            *pp = rotacaoL(p); 
                            *alterou = false; 
                            break;
                    }
            } else { 
                inserirAVL(&(p->dir), ch, alterou);
                
                if(*alterou)
                    switch (p->bal) {
                    
                        case -1:
                            p->bal = 0;     
                            *alterou = false;
                            break;
                    
                        case 0:
                            p->bal = 1;     
                            break;
                    
                        case 1:
                            *pp = rotacaoR(p); 
                            *alterou = false; 
                            break;
                    }
            }
        }
    }

    // Função auxiliar para encontrar o k-ésimo menor valor na árvore AVL. A função percorre a árvore em ordem, decrementando o valor de k a cada nó visitado até encontrar o k-ésimo menor valor.
    // A função utiliza uma variável auxiliar para contar os nós visitados e retorna o k-ésimo menor valor.

    void kesimoAux(PONT raiz, int* k, int* resultado) {
        if (raiz == NULL || *k <= 0) return; 
        kesimoAux(raiz->esq, k, resultado);
        if (*k == 0) return; // Interrompe se o k-ésimo menor já foi encontrado
        (*k)--;
        if (*k == 0) {
            *resultado = raiz->chave; 
            return;
        }
        kesimoAux(raiz->dir, k, resultado);
    }
    /// Função para encontrar o k-ésimo menor valor na árvore AVL. A função utiliza uma variável auxiliar para contar os nós visitados e retorna o k-ésimo menor valor.
    /// A função percorre a árvore em ordem, decrementando o valor de k a cada nó visitado até encontrar o k-ésimo menor valor.
    int kesimoMenor(PONT raiz, int k) {
        int resultado = -1; 
        kesimoAux(raiz, &k, &resultado);
        return resultado;
    }

    // Busca binária na árvore AVL. A função percorre a árvore comparando a chave procurada com as chaves dos nós, movendo-se para a esquerda ou direita conforme necessário.
    // A função é chamada recursivamente até que o nó correspondente seja encontrado ou a árvore seja percorrida completamente.
    PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
        if (raiz == NULL) return NULL;
        if (raiz->chave == ch) return raiz;
        if (raiz->chave<ch) 
            return buscaBinaria(ch,raiz->dir);
        return buscaBinaria(ch,raiz->esq);
    }  

// Busca na árvore AVL e retorna o nó correspondente à chave procurada. A função percorre a árvore comparando a chave procurada com as chaves dos nós, movendo-se para a esquerda ou direita conforme necessário.
    PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
        PONT atual = raiz;
        *pai = NULL;
        while (atual) {
            if(atual->chave == ch)
                return(atual);
            *pai = atual;
            if(ch < atual->chave) atual = atual->esq;
            else atual = atual->dir;
        }
        return(NULL);
    }
    
    // Listar valores dentro de um intervalo [a, b]. A função é chamada recursivamente para os nós à esquerda e à direita da árvore.
    void listarIntervalo(PONT raiz, int c, int d) {
        if (raiz == NULL) return;
        if (raiz->chave > c) listarIntervalo(raiz->esq, c, d);
        if (raiz->chave >= c && raiz->chave <= d) {
            printf("%d ", raiz->chave);
        }
        if (raiz->chave < d) listarIntervalo(raiz->dir, c, d);
    }


    PONT maiorAEsquerda(PONT p, PONT *ant){
    *ant = p;
    p = p->esq;
    while (p->dir) {
        *ant = p;
        p = p->dir;
    }
    return(p);
    }



    bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou) {
    
        PONT atual = *raiz;

    
        if (!atual) {
            *alterou = false;
            return false;
        }

    
        if (atual->chave == ch) {
            PONT substituto, pai_substituto;
        
            if (!atual->esq || !atual->dir) {
            
                if (atual->esq)
                    substituto = atual->esq;
                else
                    substituto = atual->dir;
            
                *raiz = substituto;
            
                free(atual);
            
                *alterou = true;
                return true;
            }
            else {
            
                substituto = maiorAEsquerda(atual, &pai_substituto);
            
                atual->chave = substituto->chave;
            
                ch = substituto->chave;
            }
        }
        
        bool res;
        
        if (ch > atual->chave) {
            res = excluirAVL(&(atual->dir), ch, alterou);
            
            printf("Excluir recursivo a direita: %i(%i)\n", atual->chave, atual->bal); 
        
            if (*alterou) {
                switch (atual->bal) {
                
                    case 1:
                        atual->bal = 0;
                        return true;
                
                    case 0:
                        atual->bal = -1;
                        *alterou = false;
                        return true;
                
                    case -1:
                        *raiz = rotacaoL(atual);
                    
                        if (atual->bal != 0)
                            *alterou = false;
                        return true;
                }
            }
        }
        else {
        
            res = excluirAVL(&(atual->esq), ch, alterou);
        
            printf("Excluir recursivo a esquerda: %i(%i)\n", atual->chave, atual->bal); 
            
            if (*alterou) {
                switch (atual->bal) {
                
                    case -1:
                        atual->bal = 0;
                        return true;
            
                    case 0:
                        atual->bal = 1;
                        *alterou = false; 
                        return true;
            
                    case 1:
                        *raiz = rotacaoR(atual);
                        if (atual->bal != 0)
                            *alterou = false;
                        return true;
                }
            }
        }

        return res;
    }

    void destruirAux(PONT subRaiz){
        if (subRaiz){
            destruirAux(subRaiz->esq);
            destruirAux(subRaiz->dir);
            free(subRaiz);
        }
    }


    void destruirArvore(PONT * raiz){
        destruirAux(*raiz);
        *raiz = NULL;
    }

    void inicializar(PONT * raiz){
        *raiz = NULL;
    }



    int main(){
        PONT raiz;
        inicializar(&raiz);
        bool alterou;
        TIPOCHAVE chave;
        int opcao;
    

        do{
            printf("\n");
            printf(" _______________________   ___________________\n");
            printf("|     |     |     |     |  |     |     |     |\n");
            printf("|  M  |  E  |  N  |  U  |  |  A  |  V  |  L  |\n");
            printf("|_____|_____|_____|_____|  |_____|_____|_____|\n");
        
            printf("\n");
            printf("   Selecione uma das opcoes  abaixo \n  1.Inserir Chave\n  2.Exibir AVL em Ordem\n  3.Buscar Chave\n  4.Excluir Chave\n  5.Exibir Desenho\n  6.Maior e Menor Valor AVL\n  7.K-esimo Menor Valor AVL\n  8.Verifica se esta no mesmo nivel\n  9.Soma de valores\n  10.Total de folhas que AVL possui\n  11.Verificar o Intervalo\n  12.Nivel da Arvore\n  0.Sair\n");
            printf(" Escolha uma opcao: ");
            scanf("%d", &opcao);

            if(opcao<=0 || opcao>12){
                printf("Por favor escolha um das opcoes abaixo");
                continue; 
            }
            switch(opcao){
                case 1:
                    printf("Quantos valores deseja inserir? ");
                    int n;
                    scanf("%d", &n);
                    for(int i= 0; i<n; i++){    
                        printf("Digite o valor da chave: ");
                        scanf("%d", &chave);
                        alterou = false;
                        inserirAVL(&raiz, chave, &alterou);
                        printf("Chave %d inserida! ", chave);
                        }
                    break;
                //Caso 2: Exibir a árvore AVL em ordem
                //A árvore AVL é exibida em ordem crescente, mostrando os valores de cada nó.
                case 2:
                    printf("AVL em Ordem: ");
                    exibirArvoreEmOrdem(raiz);
                    printf("\n");
                    break;
                //Caso 3: Buscar Chave
                //O usuário insere uma chave e o programa verifica se ela está presente na árvore AVL.
                case 3: {
                    printf("Digite a chave a ser buscada: ");
                    scanf("%d", &chave);
                    PONT resultado = buscaBinaria(chave,raiz);
                    if(resultado){
                        printf("Chave %d encontrada!\n", chave);
                    } else {
                        printf("Chave %d não encontrada!\n", chave);
                    }
                    break;
                }
                
                //Caso 4: Excluir Chave
                case 4: 
                    printf("Digite a chave para ser excluida: ");
                    scanf("%d", &chave);
                    alterou = false;
                    if (excluirAVL(&raiz, chave, &alterou)) {
                        printf("Chave %d foi excluida!!\n", chave);
                    } else {
                        printf("Chave %d nao encontrada!\n", chave);
                    }
                    break;
                //Caso 5: Exibir a árvore AVL em formato de desenho
                case 5:
                    printf("Esta e a representacao em desenho da AVL: \n\n");
                    imprimirDesenho(raiz);
                    printf("\n");
                    break;
                    //Caso 6: Maior e menor valor da AVL
        
                case 6:
                    printf("Maior valor da AVL: %d\n", encontraMaior(raiz)->chave);
                    printf("Menor valor da AVL: %d\n", encontraMenor(raiz)->chave);
                    break;
                //Caso 7: K-ésimo menor valor

                case 7: 
                    printf("Digite o valor de K: ");
                    scanf("%d", &chave);
                    int totalNos = contadorNos(raiz); 
                    if (chave > 0 && chave <= totalNos) {
                        int resultado = kesimoMenor(raiz, chave);
                        printf("O %d-esimo menor valor da AVL e: %d\n", chave, resultado); 
                    } else {
                        printf("Valor de K inválido! Deve estar entre 1 e %d.\n", totalNos);
                    }
                    break;
                    //Caso 8: Verifica se dois nós estão no mesmo nível
                case 8:
                    printf("Verifica se está no mesmo nível: \n");
                    TIPOCHAVE x, y;
                    printf("Diga o primeiro valor:");
                    scanf("%d", &x);
                    printf("Diga o segundo valor:");
                    scanf("%d", &y);
                    if(mesmoNivel(raiz, x ,y)){
                        printf("OS NOS ESTAO NO MESMO NIVEL\n");
                    }else{
                        printf("OS NOS NAO ESTAO NO MESMO NIVEL\n");
                    }
                    break;

                //Caso 9: Soma de valores
                case 9:
                    printf("Soma de valores e: %i \n", somaValor(raiz));
                    break;

                //Caso 10: Total de folhas
                case 10:
                    printf("Total de folhas que AVL possui: %d\n", contadorFolhas(raiz));
                    break;

                //Caso 11: Listar valores em um intervalo
                case 11:{
                    if(raiz== NULL){
                        printf("A arvore esta vazia!\n");
                        break;
                    }
                        printf("Digite o valor do inicio do intervalo: ");
                        int c, d;
                        scanf("%d", &c);
                        printf("Digite o valor do fim do intervalo: ");
                        scanf("%d", &d);
                        if(c> d){
                            printf("O intervalo e invalido!\n");
                            break;
                        }
                        printf("Valores no intervalo [%d, %d]: ", c, d);
                        listarIntervalo(raiz, c, d); 
                        printf("\n");
                        break;
                }
                //Caso 12: Altura da árvore AVL    
                case 12: {
                    int altura = MostraAltura(raiz);
                    printf("A altura da arvore AVL e: %d\n", altura);
                    break;
                }
                    
                case 0:
                    printf("Ok, finalizando o programa...");
                    printf("Obrigado :)");
                    break;
            }
        }while (opcao != 0);

        destruirArvore(&raiz);
        return 0;
    }

