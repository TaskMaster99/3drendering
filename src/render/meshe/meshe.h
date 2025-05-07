#ifndef MESHE_H
#define MESHE_H

#include <GL/glew.h>

#include "../../data_structure/array/array.h"
#include "../../utils/utils.h"

typedef struct Vertex
{
    float Coord[3];
    float Color[3];
}Vertex;

typedef struct Vertex_t
{
    float Coord[3];
    float text_coord[2];
}Vertex_t;

typedef struct Meshe
{
    GLuint               VAO;
    GLuint               EBO;
    D_Array_float        vertices;
    D_Array_uint32_t     indices;
}Meshe;

typedef struct Meshe_t
{
    GLuint               VAO;
    GLuint               texture_id;
    GLuint               EBO;
    D_Array_float        vertices;
    D_Array_uint32_t     indices;
}Meshe_t;

void GenerateCube(Meshe* cube, float r, float g, float b);
void GenerateSquare(Meshe* square);
void GenerateArrow(Meshe* arrow);
void GenerateTexturedCube(Meshe_t* cube_t);

void DrawMeshe(Meshe* meshe);
void DrawArrowMeshe(Meshe* meshe);
void DrawMeshe_t(Meshe_t* meshe);


#endif