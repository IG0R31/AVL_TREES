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
        printf("%s", isLeft ? "├──" : "└──");

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
void imprimirDesenho(PONT raiz){
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


int totalFolhas(PONT raiz) {
    int nivelFolha = -1;
    if (verificarNivelFolhas(raiz, 0, &nivelFolha)){
        return contadorFolhas(raiz);
    }else{
        return 0;
     }
}


int MostraAltura(PONT raiz) {
    if (raiz == NULL) return -1;
    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}


int mesmoNivel(PONT raiz, TIPOCHAVE x, TIPOCHAVE y){
    int nivelX= nivelNo(raiz, x, 0);
    int nivelY = nivelNo(raiz, y, 0);
    return(nivelX != -1&& nivelX==nivelY);
}

int todasFolhasMesmoNivel(PONT raiz){
    int nivelFolha = -1;
    return verificarNivelFolhas(raiz, 0, &nivelFolha);
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
                imprimirDesenho(raiz);
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
                    printf("O %d-ésimo menor valor da AVL é: %d\n", chave, raiz->chave); 
                } else {
                    printf("Valor de K inválido!\n");
                }
                break;
            case 8:
                printf("Verifica se está no mesmo nível: \n");

                 // Implementar lógica para verificar se dois nós estão no mesmo nível
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

