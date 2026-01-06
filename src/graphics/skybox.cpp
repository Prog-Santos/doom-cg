#include "graphics/skybox.h"
#include <GL/glut.h>
#include <cmath>

// 1 textura panorâmica (equiretangular) para o céu
extern GLuint texSkydome;

static inline float clampf(float x, float a, float b)
{
    return (x < a) ? a : (x > b) ? b
                                 : x;
}

static float vFromPhi(float phi, float phiMax, float vStart, float vHorizon)
{
    float t = phi / phiMax;
    float v = vStart + t * (vHorizon - vStart);
    return clampf(v, 0.0f, 1.0f);
}

void drawSkydome(float camX, float camY, float camZ)
{
    const float R = 200.0f; // raio do dome
    const int slices = 64;  // horizontal
    const int stacks = 24;  // vertical

    // Esfera completa
    const float phiMax = 3.1415926535f;

    const float vStart = 0.00f;
    const float vHorizon = 2.00f; // aumente/diminua pra subir/descer a imagem

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    glColor3f(1.0f, 1.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texSkydome);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glPushMatrix();
    glTranslatef(camX, camY, camZ);

    for (int i = 0; i < stacks; ++i)
    {
        const float t0 = (float)i / (float)stacks;
        const float t1 = (float)(i + 1) / (float)stacks;

        const float phi0 = t0 * phiMax;
        const float phi1 = t1 * phiMax;

        const float v0 = vFromPhi(phi0, phiMax, vStart, vHorizon);
        const float v1 = vFromPhi(phi1, phiMax, vStart, vHorizon);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j)
        {
            const float s = (float)j / (float)slices; // 0..1
            const float theta = s * (2.0f * 3.1415926535f);

            const float x0 = R * std::sin(phi0) * std::cos(theta);
            const float y0 = R * std::cos(phi0);
            const float z0 = R * std::sin(phi0) * std::sin(theta);

            const float x1 = R * std::sin(phi1) * std::cos(theta);
            const float y1 = R * std::cos(phi1);
            const float z1 = R * std::sin(phi1) * std::sin(theta);

            float u = s;

            // Se ficar espelhado, descomente:
            // u = 1.0f - s;

            glTexCoord2f(u, v1);
            glVertex3f(x1, y1, z1);
            glTexCoord2f(u, v0);
            glVertex3f(x0, y0, z0);
        }
        glEnd();
    }

    glPopMatrix();

    glDepthMask(GL_TRUE);
    glPopAttrib();
}
