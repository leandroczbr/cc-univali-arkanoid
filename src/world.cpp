#include "raylib.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include "world.h"

using namespace std;

struct block
{
    int colorBase;
    int state = 0; // 0 = dead, state > 0 = vida
};

int screenWidth;
int screenHeight;

int blocosDestruidos;
int quantidadeDeBlocos;

Texture2D ttijolo[3];

int pvcSize, sizex, sizey, coordx, coordy, newx, newy;
float tileSizex, tileSizey, pvcPos, ballx, bally, ballvelx, ballvely;

int dificuldade1;
int pontuacao;

float debug_lastx, debug_lasty, debug_nowx, debug_nowy;

bool morreu;

vector<vector<block>> blocos;

void start(int df, int pontos){

    pontuacao = pontos;
    dificuldade1 = df;

    cout << "mann" << endl;
    srand(time(0));

    sizex = 3; sizey = 3;
    tileSizex = ((float)screenWidth/(float)sizex);
    tileSizey = ((float)screenHeight/(float)sizey/2);

    pvcPos = screenWidth/2;
    pvcSize = 200;

    blocosDestruidos = 0;
    quantidadeDeBlocos = sizex*sizey;

    ballx = pvcPos+2;
    bally = screenWidth-70+2;
    ballvelx = 400.0f * (1 + (float)dificuldade1/4);
    ballvely = -400.0f * (1 + (float)dificuldade1/4);

    morreu = false;

    blocos.resize(sizex, vector<block>(sizey));

    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            blocos[x][y].colorBase = rand()%206+50;
            blocos[x][y].state = rand()%3+1;
        }
    }
}

float posNWx, posNWy, posNEx, posNEy, posSWx, posSWy, posSEx, posSEy;

float angle(float x1,float y1,float x2,float y2){
    float dot = x1*x2 + y1*y2;
    float det = x1*y2 - y1*x2;
    return atan2(det, dot);
}

int calcHit(float dt, int count){

    //cout << "dt " << dt << " count " << count << " x " << coordx << " y " << coordy << endl;

    float movementx = ballvelx * dt, movementy = ballvely * dt;

    float newballx = ballx + movementx;
    float newbally = bally + movementy;

    if(newbally > screenHeight && morreu){
        return 1;
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

    int testex = 0;
    int testey = 0;

    if(newx != coordx){
        testex = 1;
        if (newx >= 0 && newy >= 0 && newx < sizex && newy < sizey && blocos[newx][coordy].state > 0){
            testex = 2;
        } else if (newballx > screenWidth || newballx < 0){
            testex = 3;
            cout << "CRASH" << endl;
        }
    }
    
    if(newy != coordy){
        testey = 1;
        if (newx >= 0 && newy >= 0 && newx < sizex && newy < sizey && blocos[coordx][newy].state > 0){
            testey = 2;
        } else if (newbally < 0){
            testey = 3;
        }
    }

    if (testex > 1){ // horizontal hit
        ballvelx *= -1;
    } else {
        coordx = newx;
        ballx = newballx;
    }
    if (testey > 1){ // vertical hit
        ballvely *= -1;
    } else {
        bally = newbally;  
        coordy = newy;
    }

    if (testex == 2){
        blocos[newx][coordx].state--;
        if (blocos[newx][coordx].state <= 0){
            blocosDestruidos ++;
            cout << blocosDestruidos << "/" << quantidadeDeBlocos << endl;
            if (blocosDestruidos >= quantidadeDeBlocos){
                return 2;
            }
        }
    }

    if (testey == 2){
        blocos[coordx][newy].state--;
        if (blocos[coordx][newy].state <= 0){
            blocosDestruidos ++;
            cout << blocosDestruidos << "/" << quantidadeDeBlocos << endl;
            if (blocosDestruidos >= quantidadeDeBlocos){
                return 2;
            }
        }
    }

    if(testex == 1 && testey == 1 && blocos[newx][newy].state > 0){
        blocos[newx][newy].state--;
        if (blocos[newx][newy].state <= 0){
            blocosDestruidos ++;
            cout << blocosDestruidos << "/" << quantidadeDeBlocos << endl;
            if (blocosDestruidos >= quantidadeDeBlocos){
                return 2;
            }
        }
    }

    return 0;
}

resultado w_update(float dt){
    

    float move = (IsKeyDown(KEY_D) ? 1.0 : 0.0)-(IsKeyDown(KEY_A) ? 1.0 : 0.0);
    pvcPos = max( min(pvcPos + move*dt*800.0f,(float)(screenWidth-pvcSize/2)) , (float)pvcSize/2.0f );
    
    switch (calcHit(dt, 0))
    {
    case 1: //morreu
        
        return (resultado){false,blocosDestruidos,false};
    case 2: //ganhou
        return (resultado){false,blocosDestruidos,true};
    default:
        return resultado();
    }
}

void w_load(int sw, int sh){
    screenWidth = sw;
    screenHeight = sh;
    
    for (int i = 0; i < 3; i++){
        cout << "debug1" << endl;
        Image fundo = LoadImage(TextFormat("..\\assets\\tijolo%d.png",i)); 
        cout << "debug2" << endl;
        ImageResize(&fundo, tileSizex, tileSizey);
        cout << "debug3" << endl;
        ttijolo[i] = LoadTextureFromImage(fundo);
        cout << "debug4" << endl;
        UnloadImage(fundo);
    }
}

void w_draw(float Tempo){
    for (int x = 0; x < sizex; x++){
        for (int y = 0; y < sizey; y++){
            if (blocos[x][y].state > 0){;
                int corBase = blocos[x][y].colorBase;
                Color temp = (Color){blocos[x][y].state == 1 ? corBase : 0,blocos[x][y].state == 2 ? corBase : 0,blocos[x][y].state == 3 ? corBase : 0,255};
                DrawRectangle(screenWidth/sizex*x,screenHeight/sizey/2*y,screenWidth/sizex,screenHeight/sizey/2,temp);
                //DrawTexture(ttijolo[blocos[x][y].state-1],screenWidth/sizex*x,screenHeight/sizey/2*y,WHITE);
            }
        }
    }
    //DrawRectangle(coordx * tileSizex,coordy * tileSizey,tileSizex,tileSizey,GOLD);
    DrawRectangle(pvcPos-pvcSize/2, screenWidth-50, pvcSize,20,GOLD);
    DrawCircle((int)ballx, (int)bally, 5, WHITE);

    DrawText(TextFormat("tijolos: %d/%d",blocosDestruidos,quantidadeDeBlocos), 20, 20, 20, BLACK);
    DrawText(TextFormat("tempo: %.2f",Tempo), 20, 40, 20, BLACK);

    //DrawLine(debug_lastx,debug_lasty,debug_nowx,debug_nowy,GREEN);
}