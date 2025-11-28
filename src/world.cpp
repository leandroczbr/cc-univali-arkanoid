#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include "world.h"
#include <math.h>

using namespace std;

struct Bloco {
    int colorBase;
    int state = 0;        // 0 = destruído, 1-3 = vidas restantes
};

int screenW, screenH;
int sizex = 3, sizey = 3;                 // Quantidade de blocos (grade)
float tileSx, tileSy;                     // Tamanho de cada bloco

int blocosDestruidos = 0;
int totalBlocos = 0;

Texture2D tijoloTex[3];                   // Texturas para 1, 2 e 3 vidas

float pvcX;                            // Posição horizontal do pvc
const int pvcSize = 200;
const int pvcY = 650;                  // Fixo próximo da base

float ballX, ballY;
float ballVelX, ballVelY;
bool perdeu = false;

int gridX = 0, gridY = 0;                 // Posição atual da bola na grade
int dificuldadeLocal;

vector<vector<Bloco>> blocos;

// reset fase
void start(int df) {
    dificuldadeLocal = df;
    srand(time(0));

    sizex = 3; sizey = 3;
    tileSx = (float)screenW / sizex;
    tileSy = (float)screenH / sizey / 2.0f;

    pvcX = screenW / 2.0f;

    blocosDestruidos = 0;
    totalBlocos = sizex * sizey;
    perdeu = false;

    // Posição inicial da bola
    ballX = pvcX;
    ballY = pvcY - 30;
    float velocidadeBase = 400.0f * (1.0f + dificuldadeLocal * 0.25f);
    ballVelX = velocidadeBase * 0.3f;
    ballVelY = -velocidadeBase;

    // Cria grade de blocos
    blocos.resize(sizex, vector<Bloco>(sizey));
    for (int x = 0; x < sizex; x++)
        for (int y = 0; y < sizey; y++) {
            blocos[x][y].colorBase = rand() % 206 + 50;
            blocos[x][y].state = rand() % 3 + 1;
        }
}

// física
int verificaColisao(float dt) {
    float nx = ballX + ballVelX * dt;
    float ny = ballY + ballVelY * dt;

    // Perdeu?
    if (ny > screenH) return 1;

    // Colisão com pvc
    if (ny > pvcY - 10 && ny < pvcY + 20 && !perdeu) {
        if (nx > pvcX - pvcSize/2 && nx < pvcX + pvcSize/2) {
            ballVelY = -abs(ballVelY);                     // sempre para cima
            float offset = (nx - pvcX) / (pvcSize / 2.0f);
            ballVelX = 400.0f * (1.0f + dificuldadeLocal * 0.25f) * offset;
        } else {
            perdeu = true;
        }
    }

    // sistema de coordenadas
    int newGridX = (int)(nx / tileSx);
    int newGridY = (int)(ny / tileSy);

    // borda
    if (nx < 0 || nx > screenW) { ballVelX = -ballVelX; nx = ballX; }
    if (ny < 0) { ballVelY = -ballVelY; ny = ballY; }

    // horizontal
    if (newGridX != gridX && newGridX >= 0 && newGridX < sizex &&
        newGridY >= 0 && newGridY < sizey && blocos[newGridX][newGridY].state > 0) {
        ballVelX = -ballVelX;
        blocos[newGridX][newGridY].state--;
        if (blocos[newGridX][newGridY].state <= 0) blocosDestruidos++;
    } else {
        gridX = newGridX;
        ballX = nx;
    }

    // vertical
    if (newGridY != gridY && newGridX >= 0 && newGridX < sizex &&
        newGridY >= 0 && newGridY < sizey && blocos[newGridX][newGridY].state > 0) {
        ballVelY = -ballVelY;
        blocos[newGridX][newGridY].state--;
        if (blocos[newGridX][newGridY].state <= 0) blocosDestruidos++;
    } else {
        gridY = newGridY;
        ballY = ny;
    }

    if (blocosDestruidos >= totalBlocos) return 2;   // Vitória
    return 0;
}

resultado w_update(float dt) {
    
    float mov = (IsKeyDown(KEY_D) ? 1.0f : 0.0f) - (IsKeyDown(KEY_A) ? 1.0f : 0.0f);
    pvcX = min(max(pvcX + mov * dt * 800.0f, pvcSize/2.0f),screenW - pvcSize/2.0f);

    int status = verificaColisao(dt);

    if (status == 1)      return {false, blocosDestruidos, false};  // Derrota
    else if (status == 2) return {false, blocosDestruidos, true};   // Vitória
    else                  return resultado();                       // Continua
}

// Carrega texturas dos tijolos
void w_load(int sw, int sh) {
    screenW = sw; screenH = sh;
}

// Renderiza Mundo
void w_draw(float tempo) {
    // Blocos
    for (int x = 0; x < sizex; x++) {
        for (int y = 0; y < sizey; y++) {
            if (blocos[x][y].state > 0) {

                int corBase = blocos[x][y].colorBase;

                Color c = {
                    (unsigned char)(blocos[x][y].state == 1 ? corBase : 0),
                    (unsigned char)(blocos[x][y].state == 2 ? corBase : 0),
                    (unsigned char)(blocos[x][y].state == 3 ? corBase : 0), 255};

                DrawRectangle(x * tileSx, y * tileSy, ceil(tileSx), ceil(tileSy), c);
            }
        }
    }

    // pvc e bola
    DrawRectangle((int)(pvcX - pvcSize/2), pvcY, pvcSize, 20, GOLD);
    DrawCircle((int)ballX, (int)ballY, 3, WHITE);

    // HUD
    DrawText(TextFormat("Blocos: %d/%d", blocosDestruidos, totalBlocos), 10, 10, 20, YELLOW);
    DrawText(TextFormat("Tempo: %.2f", tempo), 10, 35, 20, YELLOW);
}