#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>
#include"../../utils/utils.h"
#include "../../math/matrice.h"

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
    char* shader_file;
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
void GetShaderError(const char * shader_name,const unsigned int* shader);
/**
 * check program error
 * @param program pointer to a program
 * @param status program status
 */
void GetPorgramError(const unsigned int* program, const int status);
/**
 * create shader program
 * @param shader shader
 */
void InitShader(Shader* Shader, char* path0, char* path1);

/**
 * user shader program
 * @param shader shader
 */
void UseShaderProgram(Shader* shader);
/**
 * send matrix to uniform variable
 * @param shader pointer to a shader
 * @param name name of the uniform variable
 * @param mat pointer to the matrix
 */
void SetMatrix4x4Uniform(Shader* shader,char* name, MAT4x4* mat);
void SetVec3Uniform(Shader* shader,char* name, float r, float g, float b);
void SetFloatUniform(Shader* shader,char* name, const float value);
void SetTexture(Shader* shader, char* name, GLuint texture);

/**
 * clear shader program
 * @param shader pointer to a shader
 */
void ClearShader(Shader* shader);

#endif