#include "meshe.h"

void GenerateSquare(Meshe* square)
{

    float data[] = 
    {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };

    uint32_t data_[] = 
    { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    VecReserve(square->vertices, 12, sizeof(float));
    VecInsert(square->vertices, data);

    VecReserve(square->indices, 6, sizeof(uint32_t));
    VecInsert(square->indices, data_);

    GLuint VBO;

    glCreateVertexArrays(1, &square->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &square->EBO);

    glBindVertexArray(square->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, square->vertices.size * square->vertices.size_type, square->vertices.full_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square->EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, square->indices.size * square->indices.size_type, square->indices.full_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

void GenerateCube(Meshe* cube)
{
    float data[] = {
        // Front face (red)
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        
        // Back face (green)
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        
        // Right face (blue)
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        
        // Left face (yellow)
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        
        // Top face (cyan)
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        
        // Bottom face (magenta)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f
    };

    uint32_t data_[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    VecReserve(cube->vertices, 144, sizeof(float));
    VecInsert(cube->vertices, data);

    VecReserve(cube->indices, 36, sizeof(uint32_t));
    VecInsert(cube->indices, data_);

    GLuint VBO;

    glCreateVertexArrays(1, &cube->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &cube->EBO);

    glBindVertexArray(cube->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cube->vertices.size * cube->vertices.size_type, cube->vertices.full_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->indices.size * cube->indices.size_type, cube->indices.full_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void DrawMeshe(Meshe* meshe)
{
    glBindVertexArray(meshe->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshe->EBO);
    glDrawElements(GL_TRIANGLES, meshe->indices.size, GL_UNSIGNED_INT, 0);
}