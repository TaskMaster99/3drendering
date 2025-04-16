#include "shader.h"

void GetShaderError(const char * shader_name,const unsigned int* shader)
{
    int success;
    char info_Log[512];

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog( *shader, 512, NULL, info_Log);
        ERROR_LOGGING("OpenGL Error %s :\n %s",shader_name,info_Log);
    }
}

void GetPorgramError(const unsigned int* program, const int status)
{
    int success;
    char info_Log[512];

    glGetProgramiv(*program, status, &success);

    if(!success)
    {
        glGetProgramInfoLog( *program, 512, NULL, info_Log);
        ERROR_LOGGING("OpenGL Program Error :\n %s",info_Log);
    }
}


void InitShader(Shader* Shader)
{
    char* vertex_path_buffer = "src/render/shader/GLSL/square.vs";
    char* fragment_path_buffer = "src/render/shader/GLSL/square.fs";

    Shader->vertex_shader_code.name = "square.vs";
    Shader->fragment_shader_code.name = "square.fs";

    char* vertex_code_buffer = ReadFile(vertex_path_buffer);
    char* fragment_code_buffer = ReadFile(fragment_path_buffer);  

    unsigned int vertex = glCreateShader(VERTEX);
    unsigned int fragment = glCreateShader(FRAGMENT);

    glShaderSource(vertex, 1, (const char **)&vertex_code_buffer, NULL);
    glShaderSource(fragment, 1, (const char **)&fragment_code_buffer, NULL);

    glCompileShader(vertex);
    GetShaderError(Shader->vertex_shader_code.name, &vertex);

    glCompileShader(fragment);
    GetShaderError(Shader->fragment_shader_code.name, &fragment);

    Shader->program = glCreateProgram();
    
    glAttachShader(Shader->program, vertex);
    glAttachShader(Shader->program, fragment);

    glLinkProgram(Shader->program);
    GetPorgramError(&Shader->program, GL_LINK_STATUS);

    glValidateProgram(Shader->program);
    GetPorgramError(&Shader->program, GL_VALIDATE_STATUS);

    glAttachShader(0, vertex);
    glAttachShader(0, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
   
}

void SetMatrix4x4Uniform(Shader* shader,char* name, MAT4x4* mat)
{
    unsigned int transformLoc = glGetUniformLocation(shader->program,name);
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, mat->RAW_);
}

void UseShaderProgram(Shader* shader)
{
    glUseProgram(shader->program);
}

void ClearShader(Shader* shader)
{
    glDeleteProgram(shader->program);
}