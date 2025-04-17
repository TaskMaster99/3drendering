#ifndef RENDER_H
#define RENDER_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "meshe/meshe.h"
#include "../utils/utils.h"
#include "shader/shader.h"
#include "../io/camera.h"

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
typedef struct RenderContext
{
    int width;
    int height;
    float aspect_ratio;
    char* window_name;
    SDL_Window* window;
    SDL_GLContext* openGLContext;
    SDL_Event event;
    unsigned int nb_shaders;
    Shader* shaders;

}RenderContext;

/**
 * initialize SDL2 and loading OpenGl functions
 * @param render_context rendering context
 * @param width window width
 * @param height window height
 * @param window_name window name
 */
void InitOpenglContext(RenderContext* render_context, const int width, const int height, char* window_name);
/**
 * rendering loop
 * @param render_context rendering context
 */
void Loop(RenderContext* render_context);
/**
 * clean all
 * @param render_context rendering context
 */
void CleanRender(RenderContext* render_context);


#endif