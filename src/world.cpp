#include "raylib.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

struct block
{
    Color cor;
    int state = 0;
};

int screenWidth = 800;
int screenHeight = 800;

int sizex, sizey;

int pvcPos, pvcSize;

vector<vector<block>> blocos;

void start(int dificuldade){
    srand(time(0));

    sizex = 100; sizey = 100;
    pvcPos = screenWidth/2;
    pvcSize = 100;
    
    blocos.resize(sizex, vector<block>(sizey));

    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            blocos[x][y].cor = (Color){rand()%256, rand()%256, rand()%256, 255};
        }
    }
}

void w_update(float dt){
    int move = (IsKeyDown(KEY_D) ? 1 : 0)-(IsKeyDown(KEY_A) ? 1 : 0);
    pvcPos += move;
}

void w_draw(){
    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            DrawRectangle(screenWidth/sizex*x,screenHeight/sizey/2*y,screenWidth/sizex,screenHeight/sizey/2,blocos[x][y].cor);
            DrawRectangle(pvcPos-pvcSize/2, screenWidth-50, pvcSize,20,GOLD);
        }
    }
}