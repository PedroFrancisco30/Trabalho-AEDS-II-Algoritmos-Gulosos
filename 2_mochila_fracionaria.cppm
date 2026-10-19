module;
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

export module mochila_fracionaria;

export struct Item {
    std::string nome;
    double valor;
    double peso;

    double densidade() const { return valor / peso; }
};

export void executarMochilaFracionaria() {
    double capacidade = 50.0;
    std::vector<Item> itens = {
        {"Ouro",   60.0,  10.0},
        {"Prata",  100.0, 20.0},
        {"Bronze", 120.0, 30.0}
    };

    // Escolha Gulosa: Ordenar decrescente pela densidade (valor/peso) com C++20 ranges
    std::ranges::sort(itens, std::greater{}, &Item::densidade);

    std::cout << "\n=== 2. MOCHILA FRACIONARIA (Capacidade: " << capacidade << "kg) ===\n";
    double valorTotal = 0.0;

    for (const auto& item : itens) {
        if (capacidade <= 0) break;

        double pesoPego = std::min(capacidade, item.peso);
        double fracao = pesoPego / item.peso;

        valorTotal += item.valor * fracao;
        capacidade -= pesoPego;

        std::cout << "  [Pegou " << (fracao * 100) << "%] " << item.nome
                  << " (" << pesoPego << "kg) -> +R$ " << (item.valor * fracao) << "\n";
    }
    std::cout << "Lucro maximo obtido: R$ " << valorTotal << "\n";
}
