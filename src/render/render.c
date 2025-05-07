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
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    
    render_context->openGLContext = SDL_GL_CreateContext(render_context->window);

    if(glewInit() != 0)
    {
        ERROR_LOGGING("GLEW failed to load OpenGL functions ...");
    }


    LOGGING("OpenGl version : %s.\n", glGetString(GL_VERSION));
    LOGGING("Graphic Card Constructor : %s.\n", glGetString(GL_VENDOR));
    LOGGING("Graphic Card : %s.\n", glGetString(GL_RENDERER));

    LOGGING("%s is running ...\n", render_context->window_name);

    glViewport(0, 0, render_context->width, render_context->height);

}

void LoopSquare(RenderContext* render_context)
{
    SDL_bool isQuitting = 0;

    Meshe cube;
    Meshe arrow;

    GenerateCube(&cube, GL_COLOR_ORANGE);
    GenerateArrow(&arrow);

    Shader shader0;
    InitShader(&shader0,"src/render/shader/GLSL/vert.vs","src/render/shader/GLSL/frag.fs");

    MAT4x4 model;
    MAT4x4 rot;
    MAT4x4 projection;
    
    INIT_MAT4X4(&projection);
    INIT_MAT4X4(&model);
    INIT_MAT4X4(&rot);

    Camera user;
    InitCamera(&user, render_context->width, render_context->height);
    PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_3, render_context->aspect_ratio, 0.1f, 100.f, &projection);

    float i = 1.0f;

    int o_width = render_context->width;
    int o_height = render_context->height;


    UseShaderProgram(&shader0);

    while(!isQuitting)
    {
        clock_t b_frame_time = clock();
        while(SDL_PollEvent(&render_context->event))
        {
            if(render_context->event.type == SDL_QUIT)
            {
                isQuitting = SDL_TRUE;
                break;
            }
        }

        SDL_GetWindowSize(render_context->window, &render_context->width, &render_context->height);

        if((render_context->width ^ o_width) || (render_context->height ^ o_height))
        {
            glViewport(0, 0, render_context->width, render_context->height);
        
            render_context->aspect_ratio = ((float)render_context->width/render_context->height);

            LOGGING(" TO %f\n", render_context->aspect_ratio);

            o_height = render_context->height;
            o_width = render_context->width;

            PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_3, render_context->aspect_ratio, 0.1f, 100.f, &projection);

        }

        ProcessKeyBoard(&user, 0.05f);
        ProcessMouse(&user);

        glClearColor(GL_COLOR_GRAY,0.0f);
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        INIT_MAT4X4(&rot);
        //EULER_ROTATION_(0.0f, G_PI_6 * i, 0.0f, &rot);
        QUATERNION_ROTATION_(G_PI_6 * i, 1.0f, 0.0f, 0.0f, &rot);
        //QUATERNION_ROTATION_(G_PI_6 * i, 0.0f, 1.0f, 0.0f, &rot);
        //QUATERNION_ROTATION_(G_PI_6 * i, 0.0f, 0.0f, 1.0f, &rot);

        SetMatrix4x4Uniform(&shader0, "projection", &projection);
        SetMatrix4x4Uniform(&shader0, "view", &user.view);
        SetMatrix4x4Uniform(&shader0, "model", &rot);
        DrawMeshe(&cube);
        DrawArrowMeshe(&arrow);

        i += 0.05f;
        float delta_time = 1.0f/60.f;
        DELAY(delta_time * 1000.0f);

        clock_t e_frame_time = clock();

        float time = (((float)(e_frame_time - b_frame_time))/ CLOCKS_PER_SEC);
        float fps = 1.0f/(time);

        LOGGING("\rfps : %f .",fps);
        SDL_GL_SwapWindow(render_context->window);

    }

    ClearShader(&shader0);
}

void LoopSquareTexture(RenderContext* render_context)
{
    SDL_bool isQuitting = 0;

    Meshe_t cube;
    Meshe arrow;

    GenerateTexturedCube(&cube);
    GenerateArrow(&arrow);

    Shader shader0;
    InitShader(&shader0,"src/render/shader/GLSL/text.vs","src/render/shader/GLSL/text.fs");

    Shader shader1;
    InitShader(&shader1,"src/render/shader/GLSL/vert.vs","src/render/shader/GLSL/frag.fs");


    MAT4x4 model;
    MAT4x4 rot;
    MAT4x4 projection;
    
    INIT_MAT4X4(&projection);
    INIT_MAT4X4(&model);
    INIT_MAT4X4(&rot);

    Camera user;
    InitCamera(&user, render_context->width, render_context->height);
    PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_3, render_context->aspect_ratio, 0.1f, 100.f, &projection);



    TRANSLATION(0.0f, 0.0f, -1.0f, &model);

    float i = 1.0f;

    int o_width = render_context->width;
    int o_height = render_context->height;

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

        SDL_GetWindowSize(render_context->window, &render_context->width, &render_context->height);

        if((render_context->width ^ o_width) || (render_context->height ^ o_height))
        {
            glViewport(0, 0, render_context->width, render_context->height);
        
            render_context->aspect_ratio = ((float)render_context->width/render_context->height);

            LOGGING(" TO %f\n", render_context->aspect_ratio);

            o_height = render_context->height;
            o_width = render_context->width;

            PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_3, render_context->aspect_ratio, 0.1f, 100.f, &projection);

        }

        ProcessKeyBoard(&user, 0.05f);
        ProcessMouse(&user);

        glClearColor(GL_COLOR_GRAY,0.0f);
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        INIT_MAT4X4(&rot);
        //EULER_ROTATION_(0.0f, G_PI_6 * i, 0.0f, &rot);
        QUATERNION_ROTATION_(G_PI_6 * i, 1.0f, 0.0f, 0.0f, &rot);
        //QUATERNION_ROTATION_(G_PI_6 * i, 0.0f, 1.0f, 0.0f, &rot);
        //QUATERNION_ROTATION_(G_PI_6 * i, 0.0f, 0.0f, 1.0f, &rot);

        UseShaderProgram(&shader0);

        SetMatrix4x4Uniform(&shader0, "projectionM", &projection);
        SetMatrix4x4Uniform(&shader0, "modelM", &user.view);
        SetMatrix4x4Uniform(&shader0, "rotM", &rot);
        DrawMeshe_t(&cube);

        UseShaderProgram(&shader1);

        SetMatrix4x4Uniform(&shader1, "projectionM", &projection);
        SetMatrix4x4Uniform(&shader1, "modelM", &user.view);
        SetMatrix4x4Uniform(&shader1, "rotM", &rot);
        SetTexture(&shader1, "texture1", 0);
        DrawArrowMeshe(&arrow);

        i += 0.05f;
        SDL_GL_SwapWindow(render_context->window);
    }

    ClearShader(&shader0);
    ClearShader(&shader1);

}


void LoopSquareAmbient(RenderContext* render_context)
{
    SDL_bool isQuitting = 0;

    Meshe cube;
    Meshe lightSrc;
    Meshe arrow;

    GenerateCube(&cube,GL_COLOR_ORANGE);
    GenerateCube(&lightSrc,GL_COLOR_WHITE);
    GenerateArrow(&arrow);

    Shader shader0;
    InitShader(&shader0,"src/render/shader/GLSL/vert.vs","src/render/shader/GLSL/ambient.fs");

    Shader shader1;
    InitShader(&shader1,"src/render/shader/GLSL/vert.vs","src/render/shader/GLSL/frag.fs");


    MAT4x4 model;
    MAT4x4 lightModel;
    MAT4x4 rot;
    MAT4x4 projection;
    MAT4x4 trans;
    
    INIT_MAT4X4(&projection);
    INIT_MAT4X4(&model);
    INIT_MAT4X4(&lightModel);
    INIT_MAT4X4(&rot);
    INIT_MAT4X4(&trans);

    Camera user;
    InitCamera(&user, render_context->width, render_context->height);
    PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_3, render_context->aspect_ratio, 0.1f, 100.f, &projection);

    TRANSLATION(0.0f, 0.0f, -1.0f, &model);
    TRANSLATION(3.0f, 0.0f, -3.0f, &lightModel);


    float i = 1.0f;

    int o_width = render_context->width;
    int o_height = render_context->height;

    while(!isQuitting)
    {
        clock_t b_frame_time = clock();
        while(SDL_PollEvent(&render_context->event))
        {
            if(render_context->event.type == SDL_QUIT)
            {
                isQuitting = SDL_TRUE;
                break;
            }
        }

        SDL_GetWindowSize(render_context->window, &render_context->width, &render_context->height);

        if((render_context->width ^ o_width) || (render_context->height ^ o_height))
        {
            glViewport(0, 0, render_context->width, render_context->height);
        
            render_context->aspect_ratio = ((float)render_context->width/render_context->height);

            LOGGING(" TO %f\n", render_context->aspect_ratio);

            o_height = render_context->height;
            o_width = render_context->width;

            PERSPECTIVE_PROJECTION_RIGHT_HANDED(G_PI_3, render_context->aspect_ratio, 0.1f, 100.f, &projection);

        }

        ProcessKeyBoard(&user, 0.05f);
        ProcessMouse(&user);

        glClearColor(GL_COLOR_GRAY,0.0f);
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        INIT_MAT4X4(&rot);

        QUATERNION_ROTATION_(G_PI_6 * i, 1.0f, 0.0f, 0.0f, &rot);

        UseShaderProgram(&shader0);
        SetMatrix4x4Uniform(&shader0, "projection", &projection);
        SetMatrix4x4Uniform(&shader0, "view", &user.view);
        SetMatrix4x4Uniform(&shader0, "model", &rot);
        SetVec3Uniform(&shader0, "lightColor", GL_COLOR_WHITE);
        SetVec3Uniform(&shader0, "objectColor", GL_COLOR_ORANGE);
        SetFloatUniform(&shader0, "ambientStrength", 0.6);
        DrawMeshe(&cube);

        UseShaderProgram(&shader1);
        SetMatrix4x4Uniform(&shader1, "projection", &projection);
        SetMatrix4x4Uniform(&shader1, "view", &user.view);
        SetMatrix4x4Uniform(&shader1, "model", &rot);

        DrawArrowMeshe(&arrow);

        UseShaderProgram(&shader1);
        SetMatrix4x4Uniform(&shader1, "projection", &projection);
        SetMatrix4x4Uniform(&shader1, "view", &user.view);
        SetMatrix4x4Uniform(&shader1, "model", &lightModel);

        DrawMeshe(&lightSrc);

        i += 0.05f;
        float delta_time = 1.0f/60.f;
        DELAY(delta_time * 1000.0f);

        clock_t e_frame_time = clock();

        float time = (((float)(e_frame_time - b_frame_time))/ CLOCKS_PER_SEC);
        float fps = 1.0f/(time);

        LOGGING("\rfps : %f .",fps);
        SDL_GL_SwapWindow(render_context->window);

    }

    ClearShader(&shader0);
    ClearShader(&shader1);

}


void CleanRender(RenderContext* render_context)
{
    SDL_GL_DeleteContext(render_context->openGLContext);
    SDL_DestroyWindow(render_context->window);
    SDL_Quit();
}