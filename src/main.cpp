//g++ -o main.exe main.cpp draw.cpp -I include -L lib -lraylib -lgdi32 -lwinmm

#include <iostream>

#include "world.h"
#include "draw.h"
#include "raylib.h"
#include "ranking.h"

using namespace std;

// ranking.h
struct ranking {
    std::string nome;
    int pontuacao;
};

ranking get(){
    return {"j",323};
}

const int screenWidth = 700;
const int screenHeight = 700;

Rectangle botaoStart = {screenWidth/2-80,screenHeight/2-20,160,40};
Rectangle botaoRanking = {screenWidth/2-80,screenHeight/2-20+60,160,40};
Rectangle botaoDificuldade = {screenWidth/2-80,screenHeight/2-20+120,160,40};

Rectangle botoes[] = {botaoStart,botaoRanking,botaoDificuldade};

int fase = 0; // 0 = menu, 1 = ranking, 2 = dificuldade, 3 = fase_1, 4 = fase_2, 5 = fase 3
int dificuldade = 0; // 0, 1, 2

float tempo;
int pontuacao;

// int main

void salvarPontuacao(bool venceu,int pontuacao) {
    Jogador novoJogador;
    novoJogador.nome = "Jogador";
    novoJogador.data = getDataAtual();
    novoJogador.tempo = tempo;
    novoJogador.pontuacao = pontuacao;
    novoJogador.venceu = venceu;
    
    salvarDados(novoJogador);
    
    // Debug
    cout << "Pontuação salva: " << novoJogador.pontuacao << " pontos (" 
         << (venceu ? "VITORIA" : "DERROTA") << ")" << endl;
}

int main(){

    /*Texture2D background = LoadTexture("../assets/background-green.png");
    Texture2D paddleSm = LoadTexture("../assets/paddle-sm.png");
    Texture2D paddleLg = LoadTexture("../assets/paddle-lg.png");
    Texture2D paddleMd = LoadTexture("../assets/paddle-md.png");*/
    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes");

    SetExitKey(KEY_NULL);

    d_load(screenWidth,screenHeight);
    w_load(screenWidth,screenHeight);
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        

        switch (fase)
        {
        case 0:
            if (IsMouseButtonPressed(0)){
            int joy = -1;
            for (int i = 0; i<3; i++){
                if (CheckCollisionPointRec(GetMousePosition(),botoes[i])){
                    joy = i;
                    break;
                }
            }
            switch (joy)
            {
            case 0:
                start(dificuldade);
                fase = 3;
                tempo = 0.0f;
                pontuacao = 0;
                break;
            case 1:
                fase = 1;
                break;
            case 2:
                fase = 2;
                break;
            default:
                break;
            }
        }
            break;
        case 1:
            if (IsKeyPressed(KEY_ESCAPE)){
                fase = 0;
            }
            break;
        case 2:
            if (IsMouseButtonPressed(0)){
                for (int i = 0; i<3; i++){
                    if (CheckCollisionPointRec(GetMousePosition(),botoes[i])){
                        dificuldade = i;
                        fase = 0;
                        break;
                    }
                }
            }
            break;
        case 3:
        case 4:
        case 5:{
            float dt = GetFrameTime();
            tempo += dt;

            resultado result = w_update(dt);
            
            if (!result.nulo){
                pontuacao += (result.blocosDestruidos*10) * (dificuldade+1);
                if (result.ganhou) {
                    if (fase == 5){
                        salvarPontuacao(true,pontuacao * (int)(1000.0f - tempo));
                        fase = 0;
                    } else {
                        fase ++;
                        start(dificuldade,pontuacao);
                    }
                } else {
                    fase = 0;
                    salvarPontuacao(false,pontuacao * (int)(1000.0f - tempo));
                }
            }

            break;}
        default:
            break;
        }

        draw(fase,botoes,tempo);
    }

    CloseWindow();

    return 0;
}