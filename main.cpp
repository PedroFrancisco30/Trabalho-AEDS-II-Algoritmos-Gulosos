#include <iostream>

import selecao_atividades;
import mochila_fracionaria;
import huffman;
import kruskal;
import prim;

int main() {
    int opcao = -1;

    while (opcao != 0) {
        std::cout << "\n=== SEMINARIO: ALGORITMOS GULOSOS (C++20 MODULES) ===\n"
                  << "  [1] Selecao de Atividades\n"
                  << "  [2] Mochila Fracionaria\n"
                  << "  [3] Codificacao de Huffman\n"
                  << "  [4] Algoritmo de Kruskal (MST)\n"
                  << "  [5] Algoritmo de Prim (MST)\n"
                  << "  [6] Executar TODOS\n"
                  << "  [0] Sair\n"
                  << "Opcao: ";

        if (!(std::cin >> opcao)) break;

        switch (opcao) {
            case 1: executarSelecaoAtividades(); break;
            case 2: executarMochilaFracionaria(); break;
            case 3: executarHuffman(); break;
            case 4: executarKruskal(); break;
            case 5: executarPrim(); break;
            case 6:
                executarSelecaoAtividades();
                executarMochilaFracionaria();
                executarHuffman();
                executarKruskal();
                executarPrim();
                break;
            case 0: std::cout << "Encerrando...\n"; break;
            default: std::cout << "Opcao invalida!\n"; break;
        }
    }
    return 0;
}
