#include "raylib.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

struct block
{
    Color cor;
    int state = 0;
};

int screenWidth = 800;
int screenHeight = 800;

int pvcSize, sizex, sizey;

float pvcPos, ballx, bally, ballvelx, ballvely; 

int coordx, coordy;
int lastx, lasty;

bool morreu;

vector<vector<block>> blocos;

void start(int dificuldade){
    cout << "mann" << endl;
    srand(time(0));

    sizex = 10; sizey = 10;
    pvcPos = screenWidth/2;
    pvcSize = 100;
    ballx = pvcPos;
    bally = screenWidth-70;
    ballvelx = 400.0f;
    ballvely = -400.0f;
    morreu = false;

    blocos.resize(sizex, vector<block>(sizey));

    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            blocos[x][y].cor = (Color){rand()%206+50, rand()%206+50, rand()%206+50, 255};
        }
    }
}

bool w_update(float dt){
    float move = (IsKeyDown(KEY_D) ? 1.0 : 0.0)-(IsKeyDown(KEY_A) ? 1.0 : 0.0);
    pvcPos = max( min(pvcPos + move*dt*800.0f,(float)(screenWidth-pvcSize/2)) , (float)pvcSize/2.0f );
    ballx += ballvelx * dt;
    bally += ballvely * dt;

    if(ballx>screenWidth || ballx < 0){
        cout << "damnn" << endl;
        ballvelx *= -1;   
    }
    if(bally < 0){
        ballvely *= -1;   
    }
    if(bally>screenHeight && morreu){
        return true;
    }
    if (bally > screenHeight-50 && !morreu) {
        if (ballx < pvcPos + (pvcSize/2) && ballx > pvcPos - (pvcSize/2)){
            ballvely *= -1;
        } else {
            morreu = true;
        }
    }

    coordx = (int)(ballx / ((float)screenWidth/(float)sizex));
    coordy = (int)(bally / ((float)screenHeight/(float)sizey/2));

    if (coordx != lastx || coordy != lasty){
        cout << "CHANGED" << endl;
        int posNWx = coordx * (screenWidth/sizex);
        int posNWy = coordy * (screenHeight/sizey);

        int posNEx = coordx+1 * (screenWidth/sizex);
        int posNEy = coordy * (screenHeight/sizey);

        int posSWx = coordx * (screenWidth/sizex);
        int posSWy = coordy+1 * (screenHeight/sizey);

        int posSEx = coordx+1 * (screenWidth/sizex);
        int posSEy = coordy+1 * (screenHeight/sizey);
    }

    lastx = coordx;
    lasty = coordy;

    cout << coordx << " " << coordy << endl;
    //max(min(,,(float)());
    return false;
}

void w_draw(){
    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            DrawRectangle(screenWidth/sizex*x,screenHeight/sizey/2*y,screenWidth/sizex,screenHeight/sizey/2,blocos[x][y].cor);
        }
    }
    DrawRectangle(coordx * (screenWidth/sizex),coordy * (screenHeight/sizey/2),(screenWidth/sizex),(screenHeight/sizey/2),GOLD);
    //DrawRectangle(pvcPos-pvcSize/2, screenWidth-50, pvcSize,20,GOLD);
    DrawCircle((int)ballx, (int)bally, 5, BLACK); 
}