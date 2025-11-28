#pragma once
#include "raylib.h"

extern bool ganhou;

struct resultado {
    bool nulo = true;
    int blocosDestruidos = 0;
    bool ganhou = false;
};

void start(int df);

// cada frame
resultado w_update(float dt);

// texturas dos tijolos
void w_load(int sw, int sh);

void w_draw(float tempo);