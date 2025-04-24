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
	printf("%i ",raiz->chave);
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
	exibirArvorePreOrdem(raiz->esq);
	exibirArvorePreOrdem(raiz->dir);
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
//convertendo meu número em String
char* Transforma_string(int num){
    char* str = malloc(20 * sizeof(char));
    sprintf(str, "%d", num);
    return str;
}

//variável de impressão que mostra de forma hierarquica a AVL junto com o fator de balanceamento. 
//Raiz
//   Raiz[0]
//  ├──Filho[0]
//  │   ├──Neto[0]
//  │   └──Neto[0]
//  └──Neto[0]
// exemplo encontado em https://www.baeldung.com/java-print-binary-tree-diagram
void imprimirHierarquiaAVL(PONT no, const char* prefixo, int isLeft){
    if(no!=NULL){
        printf("%s", prefixo);
        printf("%s", isLeft);

        printf("%d[%d]\n", no->chave, no->bal);
        
        char* novoPrefixo = malloc((strlen(prefixo)+5)* sizeof(char));
        strcpy(novoPrefixo, prefixo);
        strcat(novoPrefixo, isLeft ? "│   " : "    ");

        imprimirHierarquiaAVL(no->esq, novoPrefixo, 1);
        imprimirHierarquiaAVL(no->dir, novoPrefixo,0);

        free(novoPrefixo);

    }
}
//inicializador de impressão
void imprimirDesenho(PONT raiz, int espaco){
    if(raiz ==NULL){
        printf("AVL vazia!\n");
        return;
    }
    printf("Estrutura da AVL:\n");
    printf("(O número entre colchetes é o fator de balanceamento)\n");
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

int MostraAltura(PONT raiz) {
    if (raiz == NULL) return -1;
    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}


int mesmoNivel(PONT raiz, int x, int y){
    int nivelX= nivelNo(raiz, x, 0);
    int nivelY = nivelNo(raiz, y, 0);
    return(nivelX != -1&& nivelX==nivelY);
}
 
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
    // p aponta para o nó atual da subárvore
    PONT p = *pp;
    
    // Se o nó atual é NULL, então chegamos à posição de inserção
    if(!p){
        // Cria um novo nó com a chave ch e o coloca na posição de *pp
        *pp = criarNovoNo(ch);
        // Indica que houve alteração (a altura aumentou)
        *alterou = true;
    } else {
        // Se a chave já existe no nó atual, não há alteração (não permite duplicatas)
        if(ch == p->chave) 
            *alterou = false;
        // Se a chave a inserir é menor ou igual à chave do nó atual, vamos para a subárvore esquerda
        else if(ch <= p->chave) {
            // Chamada recursiva para inserir na subárvore esquerda
            inserirAVL(&(p->esq), ch, alterou);
            // Se a subárvore esquerda foi alterada, precisamos atualizar o fator de balanceamento
            if(*alterou)
                switch (p->bal) {
                    // Caso 1: p->bal era 1 (a subárvore direita era mais alta)
                    // Agora, com a inserção na esquerda, os dois lados ficam equilibrados
                    case 1:
                        p->bal = 0;      // O nó fica balanceado
                        *alterou = false; // Não há mais alteração para propagar
                        break;
                    // Caso 2: p->bal era 0 (a árvore estava balanceada)
                    // A inserção na esquerda faz com que o lado esquerdo fique mais alto
                    case 0:
                        p->bal = -1;     // Aumenta a altura do lado esquerdo
                        break;
                    // Caso 3: p->bal era -1 (a subárvore esquerda já era mais alta)
                    // Com a nova inserção, o fator de balanceamento fica em -2 e é necessário rebalancear
                    case -1:
                        *pp = rotacaoL(p); // Realiza a rotação à esquerda para rebalancear
                        *alterou = false;  // O rebalanceamento corrige a altura, não há mais alteração a propagar
                        break;
                }
        } else { // Caso a chave seja maior que a chave do nó atual: inserir na subárvore direita
            // Chamada recursiva para inserir na subárvore direita
            inserirAVL(&(p->dir), ch, alterou);
            // Se a subárvore direita foi alterada, atualizar o fator de balanceamento
            if(*alterou)
                switch (p->bal) {
                    // Caso 1: p->bal era -1 (a subárvore esquerda era mais alta)
                    // Agora, com a inserção na direita, ambos os lados ficam equilibrados
                    case -1:
                        p->bal = 0;      // O nó fica balanceado
                        *alterou = false; // Não há mais alteração para propagar
                        break;
                    // Caso 2: p->bal era 0 (a árvore estava balanceada)
                    // A inserção na direita faz com que o lado direito fique mais alto
                    case 0:
                        p->bal = 1;      // Aumenta a altura do lado direito
                        break;
                    // Caso 3: p->bal era 1 (a subárvore direita já era mais alta)
                    // Com a nova inserção, o fator de balanceamento fica em +2 e é necessário rebalancear
                    case 1:
                        *pp = rotacaoR(p); // Realiza a rotação à direita para rebalancear
                        *alterou = false;  // O rebalanceamento corrige a altura, não há mais alteração a propagar
                        break;
                }
        }
    }
}


PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
	if (raiz == NULL) return NULL;
	if (raiz->chave == ch) return raiz;
	if (raiz->chave<ch) 
		return buscaBinaria(ch,raiz->dir);
	return buscaBinaria(ch,raiz->esq);
}  


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
    // Pega o nó atual apontado por *raiz
    PONT atual = *raiz;

    // Se o nó atual for NULL, a chave não foi encontrada; não há alteração
    if (!atual) {
        *alterou = false;
        return false;
    }

    // Se a chave do nó atual é a que desejamos excluir...
    if (atual->chave == ch) {
        PONT substituto, pai_substituto;
        // Se o nó atual tem zero ou um filho
        if (!atual->esq || !atual->dir) {
            // Escolhe o filho existente (ou NULL, se nenhum existir)
            if (atual->esq)
                substituto = atual->esq;
            else
                substituto = atual->dir;
            // Atualiza o ponteiro para o nó atual, removendo-o da árvore
            *raiz = substituto;
            // Libera a memória do nó excluído
            free(atual);
            // Indica que a altura da subárvore foi alterada
            *alterou = true;
            return true;
        }
        else {
            // Se o nó tem dois filhos, encontra o maior nó da subárvore esquerda
            substituto = maiorAEsquerda(atual, &pai_substituto);
            // Copia a chave do substituto para o nó atual
            atual->chave = substituto->chave;
            // Atualiza ch para continuar a exclusão do nó que continha a chave duplicada
            ch = substituto->chave; // continua o código excluindo o substituto
        }
    }
    
    bool res;
    // Se a chave a ser excluída é maior que a chave do nó atual,
    // a exclusão deve ocorrer na subárvore direita
    if (ch > atual->chave) {
        res = excluirAVL(&(atual->dir), ch, alterou);
        // Imprime mensagem para depuração (opcional) informando a exclusão na direita
        printf("Excluir recursivo a direita: %i(%i)\n", atual->chave, atual->bal); 
        // Se houve alteração na altura da subárvore direita, atualiza o fator de balanceamento do nó atual
        if (*alterou) {
            switch (atual->bal) {
                // Caso 1: se o fator era 1 (direita mais alta), a exclusão equilibrou o nó
                case 1:
                    atual->bal = 0;
                    return true;
                // Caso 2: se o fator era 0, a exclusão faz com que o lado esquerdo fique mais alto (-1)
                case 0:
                    atual->bal = -1;
                    *alterou = false; // a altura do nó atual não diminuiu, não há propagação da alteração
                    return true;
                // Caso 3: se o fator era -1, a exclusão gera desbalanceamento (-2) e é necessária uma rotação à esquerda
                case -1:
                    *raiz = rotacaoL(atual);
                    // Se, após a rotação, o fator de balanceamento não zerar, a alteração não se propaga
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }
    else {
        // Se a chave a ser excluída é menor ou igual à chave do nó atual,
        // a exclusão deve ocorrer na subárvore esquerda
        res = excluirAVL(&(atual->esq), ch, alterou);
        // Imprime mensagem para depuração (opcional) informando a exclusão na esquerda
        printf("Excluir recursivo a esquerda: %i(%i)\n", atual->chave, atual->bal); 
        // Se houve alteração na altura da subárvore esquerda, atualiza o fator de balanceamento
        if (*alterou) {
            switch (atual->bal) {
                // Caso 1: se o fator era -1 (esquerda mais alta), a exclusão equilibrou o nó
                case -1:
                    atual->bal = 0;
                    return true;
                // Caso 2: se o fator era 0, a exclusão faz com que o lado direito fique mais alto (1)
                case 0:
                    atual->bal = 1;
                    *alterou = false; // a altura não diminuiu, não há propagação da alteração
                    return true;
                // Caso 3: se o fator era 1, a exclusão gera desbalanceamento (fator 2) e é necessária uma rotação à direita
                case 1:
                    *raiz = rotacaoR(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }
    // Retorna o resultado da operação (a variável res contém o valor retornado pela chamada recursiva)
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
        printf("Escolha uma das opções:\n");
        printf("---MENU ARVORE DE BUSCA  BALANCEADA--\n1.Inserir Chave\n 2.Exibir AVL em Ordem\n 3.Buscar Chave\n 4.Excluir Chave\n 5.Exibir Desenho\n 6.Maior e Menor Valor AVL\n 7.K-esimo Menor Valor AVL\n 8.Verifica se está no mesmo nível\n 9.Soma de valores\n 10.Total de folhas que AVL possui\n 11.Desenho Hieraquico da AVL\n 0.Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if(opcao<=0 || opcao>6){
            printf("Por favor escolha um das opções abaixo");
            continue;;  
        }
        switch(opcao){
            case 1:    
                printf("Digite o valor da chave: ");
                scanf("%d", &chave);
                alterou = false;
                inserirAVL(&raiz, chave, &alterou);
                printf("Chave %d inserida! ", chave);
                break;
            
            case 2:
                printf("AVL em Ordem: ");
                exibirArvoreEmOrdem(raiz);
                printf("\n");
                break;
            
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
                
            
                case 4: 
                    printf("Digite a chave para ser excluída: ");
                    scanf("%d", &chave);
                    alterou = false;
                    if (excluirAVL(&raiz, chave, &alterou)) {
                        printf("Chave %d foi excluída!!\n", chave);
                    } else {
                        printf("Chave %d não encontrada!\n", chave);
                    }
                    break;
                
            case 5:
                printf("Esta é a representação em desenho da AVL: \n\n");
                imprimirDesenho(raiz,0);
                printf("\n");
                break;

            case 6:
                printf("Maior valor da AVL: %d\n", maiorAEsquerda(raiz, &raiz)->chave);
                printf("Menor valor da AVL: %d\n", raiz->chave);
                break;
            
            case 7: 
                printf("Digite o valor de K: ");
                scanf("%d", &chave);
                if (chave > 0 && chave <= altura(raiz) + 1) {
                    printf("O %d-ésimo menor valor da AVL é: %d\n", chave, raiz->chave); // Implementar lógica para encontrar o K-ésimo menor valor
                } else {
                    printf("Valor de K inválido!\n");
                }
                break;
            case 8:
                printf("Verifica se está no mesmo nível: \n"); // Implementar lógica para verificar se dois nós estão no mesmo nível
                break;
            case 9:
                printf("Soma de valores: \n"); // Implementar lógica para calcular a soma dos valores da AVL
                break;
            case 10:
                printf("Total de folhas que AVL possui: \n"); // Implementar lógica para contar o total de folhas da AVL
                break;
            case 11:
                printf("Aqui está o Desenho Hierárquico da AVL que você construiu: \n\n");
                imprimirDesenho(raiz);
                printf("\n");
                break;

            case 0:
                printf("Ok, finalizando o programa...");
                printf("Obrigado :)");
                break;
        }
    }while (opcao != 6);

    destruirArvore(&raiz);
    return 0;
}

