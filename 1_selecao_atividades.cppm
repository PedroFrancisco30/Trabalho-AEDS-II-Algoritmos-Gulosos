module;
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

export module selecao_atividades;

export struct Atividade {
    std::string nome;
    int inicio;
    int fim;
};

export void executarSelecaoAtividades() {
    std::vector<Atividade> atividades = {
        {"Palestra A", 1, 4},  {"Palestra B", 3, 5},  {"Palestra C", 0, 6},
        {"Palestra D", 5, 7},  {"Palestra E", 3, 9},  {"Palestra F", 5, 9},
        {"Palestra G", 6, 10}, {"Palestra H", 8, 11}, {"Palestra I", 8, 12},
        {"Palestra J", 2, 14}, {"Palestra K", 12, 16}
    };

    // Escolha Gulosa: Ordenar pelo menor tempo de término usando Projections (C++20)
    std::ranges::sort(atividades, {}, &Atividade::fim);

    std::cout << "\n=== 1. SELECAO DE ATIVIDADES ===\n";
    int ultimoFim = -1;
    int total = 0;

    for (const auto& [nome, inicio, fim] : atividades) {
        if (inicio >= ultimoFim) {
            std::cout << "  [Escolhida] " << nome << " (" << inicio << "h as " << fim << "h)\n";
            ultimoFim = fim;
            total++;
        }
    }
    std::cout << "Total maximo de atividades: " << total << "\n";
}
