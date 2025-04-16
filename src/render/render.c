#include "render.h"

void InitOpenglContext(RenderContext* render_context, const int width, const int height, char* window_name)
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
    render_context->aspect_ratio = ((float)width/height);
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

void Loop(RenderContext* render_context)
{
    SDL_bool isQuitting = 0;

    Meshe cube;
    Meshe arrow;

    GenerateCube(&cube);
    GenerateArrow(&arrow);

    Shader shader;
    InitShader(&shader);

    UseShaderProgram(&shader);

    MAT4x4 model;
    MAT4x4 rot;
    MAT4x4 projection;
    
    INIT_MAT4X4(&projection);
    INIT_MAT4X4(&model);
    INIT_MAT4X4(&rot);


    TRANSLATION(0.0f, 0.0f, -1.0f, &model);

    float i = 1.0f;

    while(!isQuitting)
    {
        while(SDL_PollEvent(&render_context->event))
        {
            if(render_context->event.type == SDL_QUIT)
            {
                isQuitting = SDL_TRUE;
                break;
            }
        }

        glClearColor(GL_COLOR_GRAY,0.0f);
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_2, render_context->aspect_ratio, 0.1f, 100.f, &projection);
        INIT_MAT4X4(&rot);
        //EULER_ROTATION_(0.0f, G_PI_6 * i, 0.0f, &rot);
        QUATERNION_ROTATION_(G_PI_6 * i, 1.0f, 0.0f, 0.0f, &rot);
        //QUATERNION_ROTATION_(G_PI_6 * i, 0.0f, 1.0f, 0.0f, &rot);
        //QUATERNION_ROTATION_(G_PI_6 * i, 0.0f, 0.0f, 1.0f, &rot);

        SetMatrix4x4Uniform(&shader, "projectionM", &projection);
        SetMatrix4x4Uniform(&shader, "modelM", &model);
        SetMatrix4x4Uniform(&shader, "rotM", &rot);


        DrawMeshe(&cube);
        DrawArrowMeshe(&arrow);

        i += 0.05f;
        SDL_GL_SwapWindow(render_context->window);
    }

    ClearShader(&shader);
}

void CleanRender(RenderContext* render_context)
{
    SDL_GL_DeleteContext(render_context->openGLContext);
    SDL_DestroyWindow(render_context->window);
    SDL_Quit();
}