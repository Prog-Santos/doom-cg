#include "utils/assets.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include <cstdio>

bool loadAssets(GameAssets &a)
{
    a.texChao = carregaTextura("assets/181.png");
    a.texParede = carregaTextura("assets/091.png");
    a.texSangue = carregaTextura("assets/016.png");
    a.texLava = carregaTextura("assets/179.png");
    a.texChaoInterno = carregaTextura("assets/100.png");
    a.texParedeInterna = carregaTextura("assets/060.png");
    a.texTeto = carregaTextura("assets/081.png");

    a.texSkydome = carregaTextura("assets/Va4wUMQ.png");
    // a.texSkydome = carregaTextura("assets/7AgU5CT.png");
    // a.texSkydome = carregaTextura("assets/Y1m2NAI.png");

    a.progSangue = criaShader("shaders/blood.vert", "shaders/blood.frag");
    a.progLava = criaShader("shaders/lava.vert", "shaders/lava.frag");

    if (!a.texChao || !a.texParede || !a.texSangue || !a.texLava ||
        !a.texChaoInterno || !a.texParedeInterna || !a.texTeto ||
        !a.texSkydome || !a.progSangue || !a.progLava)
    {
        std::printf("ERRO: falha ao carregar algum asset.\n");
        return false;
    }

    return true;
}
