#ifndef AVL_H
#define AVL_H

typedef int TIPOCHAVE;
typedef struct aux {
	TIPOCHAVE chave;
	struct aux *esq;
	struct aux *dir;
	int bal; 
} NO, *PONT;

PONT criarNovoNo(TIPOCHAVE ch);
int max(int a, int b);
int altura(PONT p);
void exibirArvoreEmOrdem(PONT raiz);
void exibirArvorePreOrdem(PONT raiz);
void exibirArvorePosOrdem(PONT raiz);
void exibirArvore(PONT raiz);
PONT rotacaoL(PONT p);
PONT rotacaoR(PONT p);
void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou);
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz);
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai);
PONT maiorAEsquerda(PONT p, PONT *ant);
bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou);
void destruirAux(PONT subRaiz);
void destruirArvore(PONT * raiz);
void inicializar(PONT * raiz);

#endif // AVL_H
