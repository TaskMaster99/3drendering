#ifndef CAMERA_H
#define CAMERA_H

#include "../utils/utils.h"
#include <GL/glew.h>
#include "../math/matrice.h"
#include <SDL2/SDL.h>

#define A SDL_SCANCODE_Q
#define Z SDL_SCANCODE_W
#define E SDL_SCANCODE_E
#define Q SDL_SCANCODE_A
#define S SDL_SCANCODE_S
#define D SDL_SCANCODE_D


typedef struct Camera{
    VEC4 up;
    VEC4 right;
    VEC4 front;

    VEC4 position;

    MAT4x4 view;

    float fov;

    float width;
    float height;

    float old_x;
    float old_y;

    float mouse_x;
    float mouse_y;

    float angle_x;
    float angle_y;

}Camera;


void InitCamera(Camera* camera, const float width, const float height);
void ProcessKeyBoard(Camera* camera, const float speed);
void ProcessMouse(Camera* camera);


#endif