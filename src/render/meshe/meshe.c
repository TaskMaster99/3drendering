#define DEFINE_ARRAY_STRUCTS
#include "meshe.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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
    { 
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

void GenerateCube(Meshe* cube, float r, float g, float b)
{
    float data[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f,  0.5f,  r, g, b,
        
        // Back face
        -0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b,
        
        // Right face
         0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
        
        // Left face
        -0.5f, -0.5f, -0.5f,  r, g, b,
        -0.5f, -0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b,
        
        // Top face
        -0.5f,  0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b,
        
        // Bottom face
        -0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
        -0.5f, -0.5f,  0.5f,  r, g, b
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



void GenerateArrow(Meshe* arrow)
{

    float data[] = 
    {
        0.0f, 0.0f, 0.0f, GL_COLOR_BLACK,
        1.0f, 0.0f, 0.0f, GL_COLOR_RED,
        0.0f, 1.0f, 0.0f, GL_COLOR_BLUE,
        0.0f, 0.0f, 1.0f, GL_COLOR_GREEN
    };

    uint32_t data_[] = 
    { 
        0, 1, 
        0, 2,
        0, 3
    };

    VecReserve(arrow->vertices, 24, sizeof(float));
    VecInsert(arrow->vertices, data);

    VecReserve(arrow->indices, 6, sizeof(uint32_t));
    VecInsert(arrow->indices, data_);

    GLuint VBO;

    glCreateVertexArrays(1, &arrow->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &arrow->EBO);

    glBindVertexArray(arrow->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, arrow->vertices.size * arrow->vertices.size_type, arrow->vertices.full_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrow->EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, arrow->indices.size * arrow->indices.size_type, arrow->indices.full_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GenerateTexturedSquare(Meshe_t* square_t)
{
    float data[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    uint32_t data_[] = 
    { 
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    glGenTextures(1, &square_t->texture_id);
    glBindTexture(GL_TEXTURE_2D, square_t->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *t_data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (t_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, t_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ERROR_LOGGING("Failed to load container.jpg");
    }
    stbi_image_free(data);

    VecReserve(square_t->vertices, 24, sizeof(float));
    VecInsert(square_t->vertices, data);

    VecReserve(square_t->indices, 6, sizeof(uint32_t));
    VecInsert(square_t->indices, data_);

    GLuint VBO;

    glCreateVertexArrays(1, &square_t->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &square_t->EBO);

    glBindVertexArray(square_t->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, square_t->vertices.size * square_t->vertices.size_type, square_t->vertices.full_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square_t->EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, square_t->indices.size * square_t->indices.size_type, square_t->indices.full_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
}


void GenerateTexturedCube(Meshe_t* cube_t)
{
    float data[] = {
        // Front face (Z+)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Back face (Z-)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Right face (X+)
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

         // Left face (X-)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        // Top face (Y+)
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Bottom face (Y-)
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f
    };
    

    uint32_t data_[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    VecReserve(cube_t->vertices, 120, sizeof(float));
    VecInsert(cube_t->vertices, data);

    VecReserve(cube_t->indices, 36, sizeof(uint32_t));
    VecInsert(cube_t->indices, data_);

    glGenTextures(1, &cube_t->texture_id);
    glBindTexture(GL_TEXTURE_2D, cube_t->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *t_data = stbi_load("src/texture/container.jpg", &width, &height, &nrChannels, 0);
    if (t_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, t_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ERROR_LOGGING("Failed to load container.jpg\n");
    }
    stbi_image_free(t_data);

    GLuint VBO;

    glCreateVertexArrays(1, &cube_t->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &cube_t->EBO);

    glBindVertexArray(cube_t->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, cube_t->vertices.size * cube_t->vertices.size_type, cube_t->vertices.full_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_t->EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_t->indices.size * cube_t->indices.size_type, cube_t->indices.full_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

}

void DrawMeshe(Meshe* meshe)
{
    glBindVertexArray(meshe->VAO);
    
    if(meshe->EBO != 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshe->EBO);
        glDrawElements(GL_TRIANGLES, meshe->indices.size, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, meshe->vertices.size);
    }
}



void DrawArrowMeshe(Meshe* meshe)
{
    glBindVertexArray(meshe->VAO);
    
    if(meshe->EBO != 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshe->EBO);
        glLineWidth(3.0f);
        glDrawElements(GL_LINES, meshe->indices.size, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_LINES, 0, meshe->vertices.size);
    }
}

void DrawMeshe_t(Meshe_t* meshe)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, meshe->texture_id);
    glBindVertexArray(meshe->VAO);

    glDrawElements(GL_TRIANGLES, meshe->indices.size, GL_UNSIGNED_INT, 0);
}