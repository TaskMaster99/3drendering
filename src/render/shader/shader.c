#include "shader.h"

void Get_Shader_Error(const char * shader_name,const unsigned int* shader)
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

void Get_Porgram_Error(const unsigned int* program, const int status)
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

void init_shader(Shader* Shader)
{
    char* vertex_path_buffer = "";
    char* fragment_path_buffer = "";

    SHADER_CODE_PATHING(vertex_path_buffer, "vertex.vs");
    SHADER_CODE_PATHING(fragment_path_buffer, "fragment.vs");

    Shader->vertex_shader_code.name = "vertex.vs";
    Shader->fragment_shader_code.name = "fragment.vs";

    char* vertex_code_buffer = "";
    char* fragment_code_buffer = "";    

    Shader->vertex_shader_code.shader_file = fopen(vertex_path_buffer, "r");
    Shader->fragment_shader_code.shader_file = fopen(fragment_path_buffer, "r");

    fread(vertex_code_buffer, sizeof(char),1024, Shader->vertex_shader_code.shader_file);
    fread(fragment_code_buffer, sizeof(char),1024, Shader->fragment_shader_code.shader_file);

    unsigned int vertex = glCreateShader(VERTEX);
    unsigned int fragment = glCreateShader(FRAGMENT);

    const GLchar* vertex_code_buffer_const = vertex_code_buffer;
    const GLchar* fragment_code_buffer_const = fragment_code_buffer;

    glShaderSource(vertex, 1, &vertex_code_buffer_const, NULL);
    glShaderSource(fragment, 1, &fragment_code_buffer_const, NULL);

    glCompileShader(vertex);
    Get_Shader_Error("vertex", &vertex);

    glCompileShader(fragment);
    Get_Shader_Error("fragment", &fragment);

    Shader->program = glCreateProgram();
    
    glAttachShader(Shader->program, vertex);
    glAttachShader(Shader->program, fragment);

    glLinkProgram(Shader->program);
    Get_Porgram_Error(&Shader->program, GL_LINK_STATUS);

    glValidateProgram(Shader->program);
    Get_Porgram_Error(&Shader->program, GL_VALIDATE_STATUS);

    glAttachShader(0, vertex);
    glAttachShader(0, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
   
}