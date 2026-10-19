module;
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <memory>

export module huffman;

struct No {
    char ch;
    int freq;
    std::shared_ptr<No> esq = nullptr;
    std::shared_ptr<No> dir = nullptr;
};

void gerarCodigos(const std::shared_ptr<No>& raiz, const std::string& codigo,
    std::unordered_map<char, std::string>& tabela) {
        if (!raiz) return;
        if (!raiz->esq && !raiz->dir) {
            tabela[raiz->ch] = codigo.empty() ? "0" : codigo;
            return;
        }
        gerarCodigos(raiz->esq, codigo + "0", tabela);
        gerarCodigos(raiz->dir, codigo + "1", tabela);
}

export void executarHuffman() {
    std::string texto = "ABRACADABRA";
    std::unordered_map<char, int> freq;
    for (char c : texto) freq[c]++;

    auto cmp = [](const std::shared_ptr<No>& a, const std::shared_ptr<No>& b) {
        return a->freq > b->freq; // Min-Heap pela menor frequência
    };
    std::priority_queue<std::shared_ptr<No>, std::vector<std::shared_ptr<No>>, decltype(cmp)> pq(cmp);

    for (auto [ch, f] : freq) {
        pq.push(std::make_shared<No>(No{ch, f}));
    }

    // Escolha Gulosa: Unir sempre os 2 nós de menor frequência
    while (pq.size() > 1) {
        auto esq = pq.top(); pq.pop();
        auto dir = pq.top(); pq.pop();
        pq.push(std::make_shared<No>(No{'\0', esq->freq + dir->freq, esq, dir}));
    }

    std::unordered_map<char, std::string> tabela;
    gerarCodigos(pq.top(), "", tabela);

    std::cout << "\n=== 3. CODIFICACAO DE HUFFMAN (" << texto << ") ===\n";
    for (const auto& [ch, cod] : tabela) {
        std::cout << "  '" << ch << "' (freq " << freq[ch] << ") -> " << cod << "\n";
    }

    std::string comprimido;
    for (char c : texto) comprimido += tabela[c];
    std::cout << "Binario gerado: " << comprimido << " (" << comprimido.size()
              << " bits vs " << texto.size() * 8 << " bits em ASCII)\n";
}
