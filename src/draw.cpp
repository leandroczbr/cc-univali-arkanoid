#include "raylib.h"
#include "draw.h"
#include "ranking.h"
#include "world.h"

Texture2D fundo;
int sw, sh;

void d_load(int largura, int altura) {
    sw = largura; sh = altura;
    Image img = LoadImage("../assets/fundo.png");
    ImageResizeNN(&img, sw, sh);
    fundo = LoadTextureFromImage(img);
    UnloadImage(img);
}

void draw(int fase, Rectangle botoes[], float tempo) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(fundo, 0, 0, WHITE);

    switch (fase) {
        case 0: // MENU
            DrawText("ARKANOID",  250, 200, 40, GOLD);
            for (int i = 0; i < 3; i++) {
                DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? BLUE : GOLD);
            }
            DrawText("Iniciar Jogo",     (int)botoes[0].x + 15, (int)botoes[0].y + 10, 20, DARKGRAY);
            DrawText("Ranking",         (int)botoes[1].x + 35, (int)botoes[1].y + 10, 20, DARKGRAY);
            DrawText("Dificuldade",     (int)botoes[2].x + 15, (int)botoes[2].y + 10, 20, DARKGRAY);
            break;

        case 1: // RANKING
            exibirRanking();
            break;

        case 2: // SELEÇÃO DE DIFICULDADE
            for (int i = 0; i < 3; i++) {
                DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? BLUE : GOLD);
            }
            DrawText("Fácil",   (int)botoes[0].x + 45, (int)botoes[0].y + 10, 20, DARKGRAY);
            DrawText("Médio",   (int)botoes[1].x + 45, (int)botoes[1].y + 10, 20, DARKGRAY);
            DrawText("Difícil", (int)botoes[2].x + 45, (int)botoes[2].y + 10, 20, DARKGRAY);
            break;
    }

    if (fase >= 3) w_draw(tempo);   // Desenha o jogo

    EndDrawing();
}