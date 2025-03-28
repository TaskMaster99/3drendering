#ifndef RENDER_H
#define RENDER_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../utils/utils.h"
#include "shader/shader.h"

#define GL_COLOR_RED 1.0f,0.0f,0.0f
#define GL_COLOR_GREEN 0.0f,1.0f,.0f
#define GL_COLOR_BLUE 0.0f,0.0f,1.0f
#define GL_COLOR_GRAY 0.5f,0.5f,0.5f
#define GL_COLOR_WHITE 1.0f,1.0f,1.0f
#define GL_COLOR_BLACK 0.0f,0.0f,0.0f

/**
 * Context rendering
 * @param width width of the window
 * @param height height of the window
 * @param window_name name of the window
 * @param window pointer to the window
 * @param openGLContext pointer to the openGL context
 * @param event pointer* to user envent
 * @param nb_shaders number of shaders running
 * @param shaders pointer to shaders
 */
typedef struct Render_context
{
    int width;
    int height;
    char* window_name;
    SDL_Window* window;
    SDL_GLContext* openGLContext;
    SDL_Event* event;
    unsigned int nb_shaders;
    Shader* shaders;

}Render_context;

/**
 * initialize SDL2 and loading OpenGl functions
 * @param render_context rendering context
 * @param width window width
 * @param height window height
 * @param window_name window name
 */
void init_opengl_context(Render_context* render_context, const int width, const int height, char* window_name);
/**
 * rendering loop
 * @param render_context rendering context
 */
void loop(Render_context* render_context);
/**
 * clean all
 * @param render_context rendering context
 */
void clean(Render_context* render_context);


#endif