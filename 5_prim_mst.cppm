module;
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

export module prim;

export void executarPrim() {
    int V = 6;
    // Lista de adjacência: par {destino, peso}
    std::vector<std::vector<std::pair<int, int>>> grafo(V);
    auto add = [&](int u, int v, int p) {
        grafo[u].emplace_back(v, p);
        grafo[v].emplace_back(u, p);
    };

    add(0, 1, 4); add(0, 2, 4); add(1, 2, 2); add(2, 3, 3);
    add(2, 4, 2); add(2, 5, 4); add(3, 5, 3); add(4, 5, 3);

    // Min-Heap guardando tuplas: {peso, vertice_atual, vertice_pai}
    using Tupla = std::tuple<int, int, int>;
    std::priority_queue<Tupla, std::vector<Tupla>, std::greater<>> pq;
    std::vector<bool> visitado(V, false);

    pq.emplace(0, 0, -1); // Começa no vértice A (0)
    int custoTotal = 0;

    std::cout << "\n=== 5. ALGORITMO DE PRIM (MST) ===\n";
    while (!pq.empty()) {
        auto [peso, u, pai] = pq.top();
        pq.pop();

        if (visitado[u]) continue;
        visitado[u] = true;
        custoTotal += peso;

        if (pai != -1) {
            std::cout << "  [Vertice conectado] " << char('A' + pai) << " -> "
                      << char('A' + u) << " (peso " << peso << ")\n";
        }

        // Escolha Gulosa: adiciona vizinhos na Min-Heap para expandir pelo mais barato
        for (auto [v, pesoViz] : grafo[u]) {
            if (!visitado[v]) {
                pq.emplace(pesoViz, v, u);
            }
        }
    }
    std::cout << "Custo Total da MST: " << custoTotal << "\n";
}
