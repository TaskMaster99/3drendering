#ifndef MESHE_HPP
#define MESHE_HPP

#include <GL/glew.h>
#include "../../data_structure/array/array.h"
#include "../../utils/utils.h"

typedef struct Vertex
{
    float Coord[3];
    float Color[3];
}Vertex;

typedef struct Meshe
{
    GLuint               VAO;
    GLuint               EBO;
    Vector(float)        vertices;
    Vector(uint32_t) indices;
}Meshe;

void GenerateCube(Meshe* cube);
void GenerateSquare(Meshe* square);

void DrawMeshe(Meshe* meshe);

#endif