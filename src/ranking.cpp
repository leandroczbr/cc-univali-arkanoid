#include "ranking.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include "raylib.h"

using namespace std;

bool compararPontuacao(const Jogador &a, const Jogador &b) {
    return a.pontuacao > b.pontuacao;
}

void salvarDados(const Jogador &jogador) {
    ofstream arquivo("ranking.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << jogador.nome << "," 
                << jogador.data << "," 
                << jogador.tempo << "," 
                << jogador.pontuacao << ","
                << (jogador.venceu ? "VITORIA" : "DERROTA") << endl;
        arquivo.close();
    }
}

vector<Jogador> carregarRanking() {
    ifstream arquivo("ranking.txt");
    vector<Jogador> jogadores;
    
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            Jogador j;
            size_t pos = 0;
            string token;
            
            pos = linha.find(",");
            j.nome = linha.substr(0, pos);
            linha.erase(0, pos + 1);
            
            pos = linha.find(",");
            j.data = linha.substr(0, pos);
            linha.erase(0, pos + 1);
            
            pos = linha.find(",");
            j.tempo = stoi(linha.substr(0, pos));
            linha.erase(0, pos + 1);
            
            pos = linha.find(",");
            j.pontuacao = stoi(linha.substr(0, pos));
            
            jogadores.push_back(j);
        }
        arquivo.close();
        
        sort(jogadores.begin(), jogadores.end(), compararPontuacao);
    }
    
    return jogadores;
}

void exibirRanking() {
    vector<Jogador> jogadores = carregarRanking();
    
    DrawText("RANKING - TOP 10", 200, 30, 30, YELLOW);
    
    if (jogadores.empty()) {
        DrawText("Nenhum ranking encontrado", 200, 150, 20, YELLOW);
    } else {
        // Cabeçalho
        DrawText("Pos", 50, 80, 20, YELLOW);
        DrawText("Jogador", 100, 80, 20, YELLOW);
        DrawText("Pontos", 300, 80, 20, YELLOW);
        DrawText("Tempo", 400, 80, 20, YELLOW);
        DrawText("Data", 500, 80, 20, YELLOW);
        
        for (size_t i = 0; i < jogadores.size() && i < 10; i++) {
            int y = 110 + i * 40;
            Color cor = jogadores[i].pontuacao > 2000 ? GREEN : RED;
            
            // Posição
            DrawText(TextFormat("%d", (int)i+1), 50, y, 20, cor);
            
            // Nome
            DrawText(jogadores[i].nome.c_str(), 100, y, 20, cor);
            
            // Pontuação
            DrawText(TextFormat("%d", jogadores[i].pontuacao), 300, y, 20, cor);
            
            // Tempo
            DrawText(TextFormat("%.3fs", jogadores[i].tempo), 400, y, 20, cor);
            
            // Data
            DrawText(jogadores[i].data.c_str(), 500, y, 15, cor);
            
            // Status
            const char* status = jogadores[i].pontuacao > 2000 ? "VITORIA" : "DERROTA";
            DrawText(status, 600, y, 15, cor);
        }
    }
    
    DrawText("Pressione ESC para voltar", 200, 550, 20, YELLOW);
}

string getDataAtual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + 
           to_string(1 + ltm->tm_mon) + "/" + 
           to_string(1900 + ltm->tm_year);
}