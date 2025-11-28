#pragma once

#include "raylib.h"

extern bool ganhou;

struct resultado
{
    bool nulo = true;
    int blocosDestruidos;
    bool ganhou;
};

void start(int df, int pontos = 0);

resultado w_update(float dt);

void w_load(int sw, int sh);

void w_draw(float Tempo);