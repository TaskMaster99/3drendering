#ifndef SHADER_HPP
#define SHADER_HPP

#include<stdlib.h>
#include<stdio.h>
#include<GL/glew.h>
#include"../../utils/utils.h"

#define SHADER_CODE_PATHING(result,code_name) snprintf(result,1024,"render/shader/GLSL/%s", code_name)
#define VERTEX GL_VERTEX_SHADER
#define FRAGMENT GL_FRAGMENT_SHADER

/**
 * shader structure 
 * @param name file name
 * @param shader_file pointer to the file code
 */
typedef struct Shader_Code
{
    char* name;
    FILE* shader_file;
}Shader_Code;


/**
 * Shader structure
 * @param vertex_shader_code
 * @param fragment_shader_code
 * @param tesselation_code
 * @param geometry_shader_code
 * @param program
 */
typedef struct Shader
{
    Shader_Code vertex_shader_code;
    Shader_Code fragment_shader_code;
    Shader_Code tesselation_code;
    Shader_Code geometry_shader_code;

    GLuint program;

}Shader;

/**
 * check shader error
 * @param shader_name name
 * @param shader pointer to a shader
 */
void Get_Shader_Error(const char * shader_name,const unsigned int* shader);
/**
 * check program error
 * @param program pointer to a program
 * @param status program status
 */
void Get_Porgram_Error(const unsigned int* program, const int status);
/**
 * create shader program
 * @param shader shader
 */
void init_shader(Shader* Shader);

#endif