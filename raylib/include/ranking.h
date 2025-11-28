#pragma once

#include <string>
#include <vector>

struct Jogador {
    std::string nome;
    std::string data;
    float tempo;
    int pontuacao;
    bool venceu;
};

bool compararPontuacao(const Jogador &a, const Jogador &b);
void salvarDados(const Jogador &jogador);
std::vector<Jogador> carregarRanking();
void exibirRanking();
std::string getDataAtual();