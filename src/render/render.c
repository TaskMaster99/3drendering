#include "render.h"

void init_opengl_context(Render_context* render_context, const int width, const int height, char* window_name)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        ERROR_LOGGING("SDL2 failed to initialized ...");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


    render_context->width = width;
    render_context->height = height;
    render_context->window_name = window_name;
    render_context->window = SDL_CreateWindow(render_context->window_name, 
                                              SDL_WINDOWPOS_CENTERED, 
                                              SDL_WINDOWPOS_CENTERED, 
                                              render_context->width, 
                                              render_context->height, 
                                              SDL_WINDOW_OPENGL);
    
    render_context->openGLContext = SDL_GL_CreateContext(render_context->window);

    if(glewInit() != 0)
    {
        ERROR_LOGGING("GLEW failed to load OpenGL functions ...");
    }


    LOGGING("OpenGl version : %s.\n", glGetString(GL_VERSION));
    LOGGING("Graphic Card Constructor : %s.\n", glGetString(GL_VENDOR));
    LOGGING("Graphic Card : %s.\n", glGetString(GL_RENDERER));

    LOGGING("%s is running ...\n", render_context->window_name);


}

void loop(Render_context* render_context)
{
    SDL_bool isQuitting = 0;

    while(!isQuitting)
    {
        while(SDL_PollEvent(render_context->event))
        {
            if(render_context->event->type == SDL_QUIT)
            {
                isQuitting = SDL_TRUE;
                break;
            }
        }

        glClearColor(GL_COLOR_GRAY,0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(render_context->window);
    }
}

void clean(Render_context* render_context)
{
    SDL_GL_DeleteContext(render_context->openGLContext);
    SDL_DestroyWindow(render_context->window);
    SDL_Quit();
}