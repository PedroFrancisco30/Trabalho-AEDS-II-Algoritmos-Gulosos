module;
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

export module kruskal;

struct Aresta {
    int u, v, peso;
};

struct UnionFind {
    std::vector<int> pai;
    explicit UnionFind(int n) : pai(n) {
        std::iota(pai.begin(), pai.end(), 0); // Preenche 0, 1, 2, ..., n-1
    }
    int buscar(int i) {
        return pai[i] == i ? i : (pai[i] = buscar(pai[i]));
    }
    bool unir(int x, int y) {
        int rx = buscar(x), ry = buscar(y);
        if (rx == ry) return false;
        pai[rx] = ry;
        return true;
    }
};

export void executarKruskal() {
    int V = 6;
    std::vector<Aresta> arestas = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {2, 3, 3},
        {2, 4, 2}, {2, 5, 4}, {3, 5, 3}, {4, 5, 3}
    };

    // Escolha Gulosa: Ordenar arestas pelo menor peso
    std::ranges::sort(arestas, {}, &Aresta::peso);

    UnionFind dsu(V);
    int custoTotal = 0;

    std::cout << "\n=== 4. ALGORITMO DE KRUSKAL (MST) ===\n";
    for (const auto& [u, v, peso] : arestas) {
        if (dsu.unir(u, v)) {
            custoTotal += peso;
            std::cout << "  [Aresta aceita] " << char('A' + u) << " - "
                      << char('A' + v) << " (peso " << peso << ")\n";
        }
    }
    std::cout << "Custo Total da MST: " << custoTotal << "\n";
}
