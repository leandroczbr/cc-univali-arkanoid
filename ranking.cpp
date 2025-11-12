#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Jogador {
    string nome;
    string data;
    int tempo;
    int pontuacao;
};

bool compararPontuacao(const Jogador &a, const Jogador &b) {
    return a.pontuacao > b.pontuacao;
}

void salvarDados(const Jogador &jogador) {
    ofstream arquivo("ranking.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << jogador.nome << "," 
                << jogador.data << "," 
                << jogador.tempo << "," 
                << jogador.pontuacao << endl;
        arquivo.close();
        cout << "Dados salvos\n";
    } else {
        cout << "Nao deu para abrir o arquivo\n";
    }
}

void exibirRanking() {
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
            
            j.pontuacao = stoi(linha);
            
            jogadores.push_back(j);
        }
        arquivo.close();
        
        sort(jogadores.begin(), jogadores.end(), compararPontuacao);
        
        cout << "\nRANKING\n";
        for (size_t i = 0; i < jogadores.size(); i++) {
            cout << i+1 << ". " << jogadores[i].nome 
                 << " - " << jogadores[i].pontuacao << " pontos"
                 << " (Tempo: " << jogadores[i].tempo << "s, Data: " 
                 << jogadores[i].data << ")\n";
        }
    } else {
        cout << "Nenhum ranking encontrado\n";
    }
}

string getDataAtual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + 
           to_string(1 + ltm->tm_mon) + "/" + 
           to_string(1900 + ltm->tm_year);
}

int main() {
    int opcao;
    
    do {
        cout << "\nSistema de RANKINGS\n";
        cout << "1. Registrar nova pontuação\n";
        cout << "2. Exibir ranking\n";
        cout << "3. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;
        
        switch(opcao) {
            case 1: {
                Jogador novo;
                cout << "Nome: ";
                cin >> novo.nome;
                novo.data = getDataAtual();
                cout << "Tempo: ";
                cin >> novo.tempo;
                cout << "Pontuação: ";
                cin >> novo.pontuacao;
                
                salvarDados(novo);
                break;
            }
            case 2:
                exibirRanking();
                break;
            case 3:
                cout << "Saindo\n";
                break;
            default:
                cout << "Nao existe essa opçao\n";
        }
    } while(opcao != 3);
    
    return 0;
}
