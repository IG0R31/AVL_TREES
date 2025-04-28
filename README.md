# 🌳 Árvore AVL - Funções e Explicações

Este projeto implementa uma Árvore AVL com diversas funcionalidades.

Abaixo estão as funções disponíveis e o que cada uma faz:

---

## ✅ Funcionalidades Implementadas

| Requisito | Função |
|:---------|:------|
| Listar elementos no intervalo [a, b] | `listarIntervalo` |
| Contar número de folhas | `contadorFolhas` |
| Encontrar menor e maior valor | `encontraMenor` / `encontraMaior` |
| Buscar o k-ésimo menor valor | `kesimoMenor` |
| Verificar se dois valores estão no mesmo nível | `mesmoNivel` |
| Calcular a soma de todos os valores | `somaValor` |
| Calcular altura da árvore | `MostraAltura` |

---

## 🔎 Explicação das Funções

### 1. `listarIntervalo(PONT raiz, int c, int d)`
- **Descrição:** Lista todos os valores da árvore dentro do intervalo [c, d], em ordem crescente.
- **Exemplo:**  
  Árvore = [5, 10, 15, 20, 25], intervalo [10, 20] → imprime: `10 15 20`
- **Menu:** Case 11

---

### 2. `contadorFolhas(PONT raiz)`
- **Descrição:** Conta quantos nós são folhas (não possuem filhos).
- **Menu:** Case 10

---

### 3. `encontraMenor(PONT raiz)` e `encontraMaior(PONT raiz)`
- **Descrição:** 
  - `encontraMenor`: Percorre a árvore para a esquerda até encontrar o menor valor.
  - `encontraMaior`: Percorre a árvore para a direita até encontrar o maior valor.
- **Menu:** Case 6

---

### 4. `kesimoMenor(PONT raiz, int k)`
- **Descrição:** Retorna o k-ésimo menor valor da árvore AVL.
- **Nota:** Verifica se `k` é um número válido (1 ≤ k ≤ total de nós).
- **Menu:** Case 7

---

### 5. `mesmoNivel(PONT raiz, TIPOCHAVE x, TIPOCHAVE y)`
- **Descrição:** Verifica se dois valores estão no mesmo nível da árvore.
- **Menu:** Case 8

---

### 6. `somaValor(PONT raiz)`
- **Descrição:** Calcula a soma de todos os valores da árvore.
- **Menu:** Case 9

---

### 7. `MostraAltura(PONT raiz)`
- **Descrição:** Retorna a altura (número máximo de níveis) da árvore AVL.
- **Menu:** Case 12

---

# 🖼️ Impressão Gráfica da Árvore AVL

O projeto também permite visualizar a árvore graficamente (em formato textual) no console.

### Como Funciona:
- A função principal é `imprimirDesenho(raiz)`.
- Se a árvore estiver vazia, imprime "AVL vazia!".
- Impressão hierárquica:
  - Nós à esquerda usam o símbolo `|---`.
  - Nós à direita usam `|___`.
- Cada nó mostra seu valor e o fator de balanceamento no formato `valor[bal]`.  
  Exemplo: `10[1]`

### Exemplo de saída:
    //   |Raiz[0]
        //  |--Filho[0]
        //  │   |--Neto[0]
        //  │   |__Neto[0]
        //  |--Neto[0]

### Fonte de Inspiração:
> [Baeldung - Binary Tree Print](https://www.baeldung.com/java-print-binary-tree-diagram)
---
