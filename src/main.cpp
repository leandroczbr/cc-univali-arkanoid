#include <iostream>
#include "raylib.h"
#include "world.h"
#include "draw.h"
#include "ranking.h"

using namespace std;

const int screenWidth  = 700;
const int screenHeight = 700;

Rectangle botaoStart      = {screenWidth/2-80, screenHeight/2-20,     160, 40};
Rectangle botaoRanking    = {screenWidth/2-80, screenHeight/2-20+60,  160, 40};
Rectangle botaoDificuldade= {screenWidth/2-80, screenHeight/2-20+120,160, 40};
Rectangle botoes[] = {botaoStart, botaoRanking, botaoDificuldade};

int fase        = 0;   // 0=menu, 1=ranking, 2=dificuldade, 3-5=jogo
int dificuldade = 0;   // 0=fácil, 1=médio, 2=difícil
float tempo     = 0.0f;
int pontuacao   = 0;

void salvarPontuacao(bool venceu, int pontos) {
    Jogador novo;
    novo.nome      = "Jogador";
    novo.data      = getDataAtual();
    novo.tempo     = tempo;
    novo.pontuacao = pontos;
    novo.venceu    = venceu;

    salvarDados(novo);

    cout << "Pontuação salva: " << pontos << " pontos (" 
         << (venceu ? "VITÓRIA" : "DERROTA") << ")" << endl;
}

int main() {
    InitWindow(screenWidth, screenHeight, "Breakout - Raylib");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    d_load(screenWidth, screenHeight);
    w_load(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        // Lógica de mudança de fase (menu, ranking, jogo...)
        
        switch (fase) {
            case 0: // MENU PRINCIPAL
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    for (int i = 0; i < 3; i++) {
                        if (CheckCollisionPointRec(GetMousePosition(), botoes[i])) {
                            switch (i) {
                                case 0: // Iniciar Jogo
                                    start(dificuldade);
                                    fase = 3;
                                    tempo = 0.0f;
                                    pontuacao = 0;
                                    break;
                                case 1: fase = 1; break; // Ranking
                                case 2: fase = 2; break; // Dificuldade
                            }
                            break;
                        }
                    }
                }
                break;

            case 1: // TELA DE RANKING
                if (IsKeyPressed(KEY_ESCAPE)) fase = 0;
                break;

            case 2: // SELEÇÃO DE DIFICULDADE
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    for (int i = 0; i < 3; i++) {
                        if (CheckCollisionPointRec(GetMousePosition(), botoes[i])) {
                            dificuldade = i;
                            fase = 0;
                            break;
                        }
                    }
                }
                break;

            case 3: case 4: case 5: { // FASES DO JOGO
                float dt = GetFrameTime();
                tempo += dt;

                resultado res = w_update(dt);

                if (!res.nulo) {
                    pontuacao += res.blocosDestruidos * 10 * (dificuldade + 1);

                    if (res.ganhou) {
                        if (fase == 5) {                    // Terminou todas as fases
                            salvarPontuacao(true, pontuacao * (int)(1000.0f - tempo));
                            fase = 0;
                        } else {                            // Próxima fase
                            fase++;
                            start(dificuldade);
                        }
                    } else {                                // Perdeu
                        salvarPontuacao(false, pontuacao * (int)(1000.0f - tempo));
                        fase = 0;
                    }
                }
                break;
            }
        }

        // render
        draw(fase, botoes, tempo);
    }

    CloseWindow();
    return 0;
}