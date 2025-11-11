#include <iostream>

//#include "world.h"
#include "raylib.h"

using namespace std;

// ranking.h
struct ranking {
    std::string nome;
    int pontuacao;
};

ranking get(){
    return {"j",323};
}

const int screenWidth = 800;
const int screenHeight = 450;

Rectangle botaoStart = {screenWidth/2-80,screenHeight/2-20,160,40};
Rectangle botaoRanking = {screenWidth/2-80,screenHeight/2-20+60,160,40};
Rectangle botaoDificuldade = {screenWidth/2-80,screenHeight/2-20+120,160,40};

Rectangle botoes[] = {botaoStart,botaoRanking,botaoDificuldade};

Rectangle* botaoSelecionado = nullptr;

void add(){}

// world.h

void start(){}

// draw.h

void draw(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangleRec(botaoStart, (botaoSelecionado = &botaoStart) ? GOLD : BLUE);
    DrawText("Iniciar jogo", botaoStart.x+20, botaoStart.y+10, 20, DARKGRAY);

    EndDrawing();
}

// int main

int main(){

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes");
    
    SetTargetFPS(60);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        botaoSelecionado = nullptr;
        for (Rectangle rec : botoes){
            if(CheckCollisionPointRec(GetMousePosition(), rec)){
                botaoSelecionado = &rec;
                break;
            }
        }

        draw();
    }

    CloseWindow();

    /*int escolha;
    while (true) {
        cout << "digite um numero:\n(1) Iniciar Jogo\n(2) Dificuldades\n(3) Pontuação / Rank" << endl;
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            /* code * /
            break;
        case 2:
            /* code * /
            break;
        case 3:
            /* code * /
            break;
        
        default:
            cout << "DIGITE UM NUMERO CERTO" << endl;
            break;
        }
    }*/

    return 0;
}
