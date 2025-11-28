#pragma once
#include <string>
#include <vector>

using namespace std;

struct Jogador {
    string nome;
    string data;
    float tempo;
    int pontuacao;
    bool venceu;
};

void salvarDados(const Jogador& j);
vector<Jogador> carregarRanking();
void exibirRanking();
string getDataAtual();