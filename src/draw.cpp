#include "raylib.h"
#include "world.h"

void draw(int fase, Rectangle botoes[]){

    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (fase > 2){ w_draw(); EndDrawing(); return; }

    switch (fase)
    {
    case 0:
        for(int i = 0; i < 3; i++){
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(),botoes[i]) ? BLUE : GOLD);
        }
        DrawText("Iniciar jogo", botoes[0].x+20, botoes[0].y+10, 20, DARKGRAY);
        DrawText("Ranking", botoes[1].x+20, botoes[1].y+10, 20, DARKGRAY);
        DrawText("Dificuldade", botoes[2].x+20, botoes[2].y+10, 20, DARKGRAY);
        break;
    case 1:
        /* code */
        break;
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

    EndDrawing();
};