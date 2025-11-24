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

int screenWidth = 700;
int screenHeight = 700;

int pvcSize, sizex, sizey, coordx, coordy, newx, newy;
float tileSizex, tileSizey, pvcPos, ballx, bally, ballvelx, ballvely;

float debug_lastx, debug_lasty, debug_nowx, debug_nowy;

bool morreu;

vector<vector<block>> blocos;

void start(int dificuldade){
    cout << "mann" << endl;
    srand(time(0));

    sizex = 10; sizey = 10;
    tileSizex = ((float)screenWidth/(float)sizex);
    tileSizey = ((float)screenHeight/(float)sizey/2);

    pvcPos = screenWidth/2;
    pvcSize = 100;

    ballx = pvcPos+2;
    bally = screenWidth-70+2;
    ballvelx = 400.0f;
    ballvely = -100.0f;

    morreu = false;

    blocos.resize(sizex, vector<block>(sizey));

    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            blocos[x][y].cor = (Color){rand()%206+50, rand()%206+50, rand()%206+50, 255};
            blocos[x][y].state = 1;
        }
    }
}

float posNWx, posNWy, posNEx, posNEy, posSWx, posSWy, posSEx, posSEy;

float angle(float x1,float y1,float x2,float y2){
    float dot = x1*x2 + y1*y2;
    float det = x1*y2 - y1*x2;
    return atan2(det, dot);
}

bool calcHit(float dt, int count){

    //cout << "dt " << dt << " count " << count << " x " << coordx << " y " << coordy << endl;

    float movementx = ballvelx * dt, movementy = ballvely * dt;

    if (abs(movementx) > tileSizex || abs(movementy) > tileSizey){
        float unit = max(abs(movementx) / tileSizex, abs(movementy) / tileSizey);

        movementx /= unit;
        movementy /= unit;

        float mag = 1 - (1/unit);

        calcHit(mag*dt,count + 1);
    }

    float newballx = ballx + movementx;
    float newbally = bally + movementy;

    if(newbally > screenHeight && morreu){
        return true;
    }

    if (newbally > screenHeight-50 && !morreu) {
        if (ballx < pvcPos + (pvcSize/2) && ballx > pvcPos - (pvcSize/2)){
            ballvely *= -1;
        } else {
            morreu = true;
        }
    }  

    newx = (int)floor((newballx / ((float)screenWidth/(float)sizex)));
    newy = (int)floor(newbally / ((float)screenHeight/(float)sizey/2));

    int teste = ((newx != coordx) ? 1 : 0) + ((newy != coordy) ? 2 : 0);
    
    switch (teste)
    {
    case 0:
        ballx = newballx;
        bally = newbally;
        break;
    case 1:
        
        if (newx < sizex && newy < sizey && blocos[newx][newy].state == 1){
            blocos[newx][newy].state = 0;
            ballvelx *= -1;
        } else if(newx > (sizex-1) || newx < 0){
            float diff = (newballx >= screenWidth) ? (float)screenWidth : 0.0f;

            cout << "borda: " << diff << " " << newballx << " = " << ballx << " + " << movementx << endl;

            float mag = abs(diff - newballx) / abs(movementx);
            ballx = diff;
            bally = newbally;
            ballvelx *= -1;

            printf("side calling with a mag of %f, dt of %f, velx of %f, and ballx of %f\n",mag,dt,ballvelx,ballx);

            calcHit(mag*dt,count + 1);
        }
        break;
    case 2:
        if (newx < sizex && newy < sizey && blocos[newx][newy].state == 1){
            blocos[newx][newy].state = 0;
            ballvely *= -1;
        } else if (newbally < 0) {
            float mag = abs(newbally) / abs(movementy);
            bally = 0.0f;
            ballx = newballx;
            ballvely *= -1;

            printf("up calling with a mag of %f, dt of %f, velx of %f, and ballx of %f\n",mag,dt,ballvelx,ballx);

            calcHit(mag*dt,count + 1);
        }
        break;
    case 3:
        cout << "quina" << endl;

        posNWx = coordx *       tileSizex;
        posNWy = coordy *       tileSizey;

        posNEx = (coordx+1) *   tileSizex;
        posNEy = coordy *       tileSizey;

        posSWx = coordx *       tileSizex;
        posSWy = (coordy+1) *   tileSizey;

        posSEx = (coordx+1) *   tileSizex;
        posSEy = (coordy+1) *   tileSizey;        

        if (newx < sizex && newy < sizey && blocos[newx][newy].state == 1){
            blocos[newx][newy].state = 0;
            ballvelx *= -1;
            ballvely *= -1;
        }   
        break;    
    }
    
    coordx = newx;
    coordy = newy;

    //cout << "CHANGED" << endl;

    return false;
}

bool w_update(float dt){
    float move = (IsKeyDown(KEY_D) ? 1.0 : 0.0)-(IsKeyDown(KEY_A) ? 1.0 : 0.0);
    pvcPos = max( min(pvcPos + move*dt*800.0f,(float)(screenWidth-pvcSize/2)) , (float)pvcSize/2.0f );
    
    return calcHit(dt, 0);
}

void w_draw(){
    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            if (blocos[x][y].state == 1){
                DrawRectangle(screenWidth/sizex*x,screenHeight/sizey/2*y,screenWidth/sizex,screenHeight/sizey/2,blocos[x][y].cor);
            }
        }
    }
    DrawRectangle(coordx * tileSizex,coordy * tileSizey,tileSizex,tileSizey,GOLD);
    DrawRectangle(pvcPos-pvcSize/2, screenWidth-50, pvcSize,20,GOLD);
    DrawCircle((int)ballx, (int)bally, 5, BLACK);

    DrawLine(debug_lastx,debug_lasty,debug_nowx,debug_nowy,GREEN);

    DrawCircle((int)posNWx, (int)posNWy, 2, BLACK); 
    DrawCircle((int)posNEx, (int)posNEy, 2, BLACK); 
    DrawCircle((int)posSWx, (int)posSWy, 2, BLACK); 
    DrawCircle((int)posSEx, (int)posSEy, 2, BLACK);
}