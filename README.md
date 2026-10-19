# Trabalho AEDS II — Algoritmos Gulosos em C++ Moderno (C++20 Modules)

Implementação didática, enxuta e moderna de **5 problemas clássicos de Algoritmos Gulosos (*Greedy Algorithms*)** desenvolvida para a disciplina de **Algoritmos e Estruturas de Dados II (AEDS II)**.

O projeto adota **C++20** com **Módulos Nativos (`.cppm`)**, dispensando o modelo tradicional de arquivos de cabeçalho (`.h` / `.hpp`) e pré-processador (`#include` entre arquivos do projeto), além de explorar recursos modernos da linguagem como *Ranges*, *Projections*, *Structured Bindings* e *Smart Pointers*.

---

## Sumário

1. [Visão Geral do Paradigma Guloso](#visão-geral-do-paradigma-guloso)
2. [Arquitetura e Estrutura do Projeto](#arquitetura-e-estrutura-do-projeto)
3. [Recursos de C++20 Utilizados](#recursos-de-c20-utilizados)
4. [Análise Detalhada dos Algoritmos](#análise-detalhada-dos-algoritmos)
   - [1. Seleção de Atividades](#1-seleção-de-atividades-1_selecao_atividadescppm)
   - [2. Problema da Mochila Fracionária](#2-problema-da-mochila-fracionária-2_mochila_fracionariacppm)
   - [3. Codificação de Huffman](#3-codificação-de-huffman-3_huffmancppm)
   - [4. Algoritmo de Kruskal (MST)](#4-algoritmo-de-kruskal--árvore-geradora-mínima-4_kruskal_mstcppm)
   - [5. Algoritmo de Prim (MST)](#5-algoritmo-de-prim--árvore-geradora-mínima-5_prim_mstcppm)
5. [ Quadro Comparativo de Complexidade](#-quadro-comparativo-de-complexidade)
6. [Pré-requisitos e Compilação](#pré-requisitos-e-compilação)
7. [Exemplo de Saída](#exemplo-de-saída)

---

## Visão Geral do Paradigma Guloso

Um **Algoritmo Guloso** constrói uma solução passo a passo tomando, em cada iteração, a **decisão localmente ótima** na esperança de que essa sequência de escolhas leve a uma **solução globalmente ótima**.

Para que um problema admita solução ótima via estratégia gulosa, ele deve satisfazer duas propriedades fundamentais:
1. **Propriedade da Escolha Gulosa:** Uma solução globalmente ótima pode ser alcançada fazendo escolhas localmente ótimas (sem necessidade de reconsiderar decisões passadas ou explorar múltiplos subproblemas como na Programação Dinâmica).
2. **Subestrutura Ótima:** Uma solução ótima para o problema contém dentro dela soluções ótimas para os subproblemas resultantes após a escolha gulosa.

---

## Arquitetura e Estrutura do Projeto

O sistema é modularizado em 5 unidades de tradução de módulos C++20 independentes (`.cppm`), consumidas por um menu interativo em `main.cpp`:

```text
Trabalho-AEDS-II-Algoritmos-Gulosos/
├── CMakeLists.txt               # Configuração de build CMake 3.28+ (FILE_SET CXX_MODULES)
├── main.cpp                     # Ponto de entrada e menu interativo (importa os 5 módulos)
├── 1_selecao_atividades.cppm    # Módulo: export module selecao_atividades;
├── 2_mochila_fracionaria.cppm   # Módulo: export module mochila_fracionaria;
├── 3_huffman.cppm               # Módulo: export module huffman;
├── 4_kruskal_mst.cppm           # Módulo: export module kruskal;
└── 5_prim_mst.cppm              # Módulo: export module prim;
```

---

## Recursos de C++20 Utilizados

| Recurso | Onde é aplicado | Benefício no Projeto |
| :--- | :--- | :--- |
| **C++20 Modules (`export module` / `import`)** | Todos os `.cppm` e `main.cpp` | Isolamento de escopo (funções e structs auxiliares privadas como `No`, `Aresta` e `UnionFind` não vazam para `main.cpp`), compilação limpa e eliminação de `#pragma once`/`#ifndef`. |
| **`std::ranges::sort` com *Projections*** | Seleção de Atividades, Mochila e Kruskal | Permite ordenar coleções diretamente por um membro ou método da struct (`&Atividade::fim`, `&Item::densidade`, `&Aresta::peso`) sem escrever *lambdas* verbosas. |
| ***Structured Bindings* (`auto [a, b, c]`)** | Todos os módulos | Desestruturação direta de `struct`, `std::pair` e `std::tuple` em laços `for`, aumentando a legibilidade do código. |
| ** Ponteiros Inteligentes (`std::shared_ptr`)** | Codificação de Huffman | Gerenciamento automático de memória (RAII) na construção da árvore binária de prefixos, evitando vazamentos de memória (*memory leaks*) sem necessidade de `delete`. |
| **Dedução de Tipo em Lambdas (`decltype(cmp)`)** | Codificação de Huffman | Definição enxuta de comparadores customizados para `std::priority_queue`. |

---

## Análise Detalhada dos Algoritmos

### 1. Seleção de Atividades (`1_selecao_atividades.cppm`)
- **Módulo:** `selecao_atividades` | **Função exportada:** `executarSelecaoAtividades()`
- **Problema:** Dado um conjunto de $n$ atividades com horários de início e término $[s_i, f_i)$, selecionar o número máximo de atividades compatíveis (sem sobreposição de horário) para uma única sala.
- **Escolha Gulosa:** Ordenar as atividades em ordem crescente de **tempo de término** (`std::ranges::sort(atividades, {}, &Atividade::fim)`) e selecionar iterativamente a próxima atividade cujo início seja maior ou igual ao término da última atividade escolhida ($s_i \ge f_{\text{último}}$), liberando o recurso o mais cedo possível.
- **Caso de Teste:** 11 palestras (`Palestra A` a `Palestra K`), resultando no conjunto máximo de **4 atividades compatíveis** (`Palestra A [1h-4h]`, `Palestra D [5h-7h]`, `Palestra H [8h-11h]`, `Palestra K [12h-16h]`).

---

### 2. Problema da Mochila Fracionária (`2_mochila_fracionaria.cppm`)
- **Módulo:** `mochila_fracionaria` | **Função exportada:** `executarMochilaFracionaria()`
- **Problema:** Dada uma mochila de capacidade máxima $W$ e um conjunto de itens com peso $w_i$ e valor $v_i$, maximizar o valor total transportado podendo levar **frações** de itens.
- **Escolha Gulosa:** Calcular a densidade de valor de cada item ($d_i = v_i / w_i$) e ordenar em ordem decrescente de densidade (`std::ranges::sort(itens, std::greater{}, &Item::densidade)`). Em seguida, coletar o máximo possível do item de maior custo-benefício por quilo até esgotar a capacidade.
- **Caso de Teste:** Mochila de `50kg` com Ouro (`R$ 60 / 10kg` $\rightarrow d=6$), Prata (`R$ 100 / 20kg` $\rightarrow d=5$) e Bronze (`R$ 120 / 30kg` $\rightarrow d=4$). Leva 100% do Ouro (`10kg`), 100% da Prata (`20kg`) e 66.67% do Bronze (`20kg`), atingindo o lucro ótimo de **`R$ 240.00`**.

---

### 3. Codificação de Huffman (`3_huffman.cppm`)
- **Módulo:** `huffman` | **Função exportada:** `executarHuffman()`
- **Problema:** Comprimir uma sequência de caracteres sem perda de dados utilizando códigos binários de tamanho variável livres de prefixo (*prefix-free codes*).
- **Escolha Gulosa:** Contabilizar a frequência de cada caractere e inserir os nós folha em uma *Min-Heap* (`std::priority_queue`). Enquanto houver mais de um nó na fila, extrair os **dois nós de menor frequência**, combiná-los em um novo nó interno cuja frequência é a soma dos dois filhos e reinseri-lo na fila. Caracteres mais frequentes ficam mais próximos da raiz (menos bits).
- **Caso de Teste:** Palavra `"ABRACADABRA"` (11 caracteres = `88 bits` em ASCII padrão). A árvore reduz o tamanho para **`23 bits`** (~73,8% de compressão).

---

### 4. Algoritmo de Kruskal — Árvore Geradora Mínima (`4_kruskal_mst.cppm`)
- **Módulo:** `kruskal` | **Função exportada:** `executarKruskal()`
- **Problema:** Encontrar uma Árvore Geradora Mínima (*Minimum Spanning Tree* — MST) que conecte todos os $V$ vértices de um grafo conexo, não-direcionado e ponderado com o menor custo total de arestas.
- **Escolha Gulosa (Baseada em Arestas):** Ordenar todas as arestas em ordem crescente de peso (`std::ranges::sort(arestas, {}, &Aresta::peso)`) e adicionar a aresta de menor peso à árvore caso ela não forme ciclo.
- **Estrutura Auxiliar:** Implementa a estrutura de Conjuntos Disjuntos (**Union-Find / DSU**) com **compressão de caminho** (*path compression*) no método `buscar()`, garantindo verificação de ciclos em tempo quase constante $O(\alpha(V))$.
- **Caso de Teste:** Grafo com $V = 6$ vértices (`A` a `F`) e $E = 8$ arestas, obtendo uma MST com custo total **`14`**.

---

### 5. Algoritmo de Prim — Árvore Geradora Mínima (`5_prim_mst.cppm`)
- **Módulo:** `prim` | **Função exportada:** `executarPrim()`
- **Problema:** Encontrar a Árvore Geradora Mínima (MST) do mesmo grafo de $V = 6$ vértices expandindo uma única componente conexa a partir de um vértice inicial.
- **Escolha Gulosa (Baseada em Vértices/Corte):** Iniciar pelo vértice `A` (`0`) e utilizar uma *Min-Heap* de tuplas `(peso, vertice_atual, vertice_pai)` para sempre expandir a árvore através da aresta mais leve que cruza a fronteira entre os vértices já visitados e os não visitados.
- **Caso de Teste:** Mesmo grafo de 6 vértices e 8 arestas utilizado no módulo de Kruskal, confirmando o custo total ótimo igual a **`14`**.

---

## Quadro Comparativo de Complexidade

| Algoritmo | Estrutura de Dados Principal | Complexidade de Tempo | Complexidade de Espaço |
| :--- | :--- | :---: | :---: |
| **1. Seleção de Atividades** | `std::vector` + Ordenação | $O(n \log n)$ | $O(1)$ auxiliar |
| **2. Mochila Fracionária** | `std::vector` + Ordenação | $O(n \log n)$ | $O(1)$ auxiliar |
| **3. Codificação de Huffman** | *Min-Heap* (`std::priority_queue`) + Árvore Binária + Hash Map | $O(n + k \log k)$* | $O(k)$ |
| **4. Kruskal (MST)** | Lista de Arestas + *Union-Find* (DSU) | $O(E \log E)$ ou $O(E \log V)$ | $O(V)$ |
| **5. Prim (MST)** | Lista de Adjacência + *Min-Heap* (`std::priority_queue`) | $O((V + E) \log V)$ | $O(V + E)$ |

*\*Onde $n$ é o tamanho do texto e $k$ é o número de caracteres distintos no alfabeto ($k \le n$).*

---

## Pré-requisitos e Compilação

Para compilar módulos nativos do C++20 (`.cppm`), certifique-se de possuir:
- **Compilador C++20:** `GCC 11+` (recomendado `GCC 14+`), `Clang 16+` ou `MSVC 19.28+`
- **Sistema de Build (Opcional):** `CMake 3.28+` e `Ninja 1.11+` (necessários para suporte nativo a `FILE_SET CXX_MODULES`)

### Opção 1: Via CMake + Ninja (Recomendado / IDEs como CLion e VS Code)

```bash
cmake -B build -G Ninja
cmake --build build
./build/seminario
```

### Opção 2: Direto via `g++` (Linha de Comando)

A ordem dos arquivos `.cppm` antes do `main.cpp` garante que as interfaces de módulo (`.gcm`) sejam geradas antes de serem importadas:

```bash
g++ -std=c++20 -fmodules-ts *.cppm main.cpp -o seminario
./seminario
```

---

## Exemplo de Saída

Ao escolher a opção `[6] Executar TODOS` no menu interativo:

```text
=== SEMINARIO: ALGORITMOS GULOSOS (C++20 MODULES) ===
  [1] Selecao de Atividades
  [2] Mochila Fracionaria
  [3] Codificacao de Huffman
  [4] Algoritmo de Kruskal (MST)
  [5] Algoritmo de Prim (MST)
  [6] Executar TODOS
  [0] Sair
Opcao: 6

=== 1. SELECAO DE ATIVIDADES ===
  [Escolhida] Palestra A (1h as 4h)
  [Escolhida] Palestra D (5h as 7h)
  [Escolhida] Palestra H (8h as 11h)
  [Escolhida] Palestra K (12h as 16h)
Total maximo de atividades: 4

=== 2. MOCHILA FRACIONARIA (Capacidade: 50kg) ===
  [Pegou 100%] Ouro (10kg) -> +R$ 60
  [Pegou 100%] Prata (20kg) -> +R$ 100
  [Pegou 66.6667%] Bronze (20kg) -> +R$ 80
Lucro maximo obtido: R$ 240

=== 3. CODIFICACAO DE HUFFMAN (ABRACADABRA) ===
  'A' (freq 5) -> 0
  'B' (freq 2) -> 10
  'R' (freq 2) -> 111
  'C' (freq 1) -> 1100
  'D' (freq 1) -> 1101
Binario gerado: 01011101100011010101110 (23 bits vs 88 bits em ASCII)

=== 4. ALGORITMO DE KRUSKAL (MST) ===
  [Aresta aceita] B - C (peso 2)
  [Aresta aceita] C - E (peso 2)
  [Aresta aceita] C - D (peso 3)
  [Aresta aceita] D - F (peso 3)
  [Aresta aceita] A - B (peso 4)
Custo Total da MST: 14

=== 5. ALGORITMO DE PRIM (MST) ===
  [Vertice conectado] A -> B (peso 4)
  [Vertice conectado] B -> C (peso 2)
  [Vertice conectado] C -> E (peso 2)
  [Vertice conectado] C -> D (peso 3)
  [Vertice conectado] D -> F (peso 3)
Custo Total da MST: 14
```
