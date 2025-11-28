#include "raylib.h"
#include "world.h"
#include "draw.h"
#include <iostream>
#include "ranking.h"

using namespace std;

Texture2D tfundo;
int sw2, sh2;

void d_load(int sw, int sh){
    sw2 = sw;
    sh2 = sh;
    cout << "debug1" << endl;
    Image fundo = LoadImage("..\\assets\\fundo.png");
    cout << "debug2" << endl;
    ImageResize(&fundo, sw, sh);
    cout << "debug3" << endl;
    tfundo = LoadTextureFromImage(fundo);
    cout << "debug4" << endl;
    UnloadImage(fundo);
}

void draw(int fase, Rectangle botoes[],int Tempo){

    BeginDrawing();

    ClearBackground(BLACK);

    DrawTexture(tfundo, 0, 0, WHITE);  

    cout << fase << endl;
    switch (fase)
    {
    case 0:{  // 0 = menu, 1 = ranking, 2 = dificuldade, 3 = fase_1, 4 = fase_2, 5 = fase 3
        
        for(int i = 0; i < 3; i++){
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(),botoes[i]) ? BLUE : GOLD);
        }
        DrawText("Iniciar jogo", botoes[0].x+20, botoes[0].y+10, 20, DARKGRAY);
        DrawText("Ranking", botoes[1].x+20, botoes[1].y+10, 20, DARKGRAY);
        DrawText("Dificuldade", botoes[2].x+20, botoes[2].y+10, 20, DARKGRAY);
        break;}
    case 1:{
        exibirRanking();
        break;}
    case 2:
        for(int i = 0; i < 3; i++){
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(),botoes[i]) ? BLUE : GOLD);
        }
        DrawText("Fácil", botoes[0].x+20, botoes[0].y+10, 20, DARKGRAY);
        DrawText("Médio", botoes[1].x+20, botoes[1].y+10, 20, DARKGRAY);
        DrawText("Difícil", botoes[2].x+20, botoes[2].y+10, 20, DARKGRAY);
        break;
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;
    default:
        break;
    }

    if (fase > 2){ w_draw(Tempo); }

    EndDrawing();
    return;
};