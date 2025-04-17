#include "camera.h"


void InitCamera(Camera* camera, const float width, const float height)
{
    camera->position = (VEC4){0.0f, 0.0f, -1.0f, 0.0f};

    camera->up = (VEC4){0.0f, 1.0f, 0.0f, 0.0f};

    VEC4 tmp;

    COEFF_M_VEC4(-1.0f, &camera->position, &tmp);
    NORMALIZE(&tmp, &camera->front);

    CROSS_PRODUCT(&camera->front, &camera->up, &tmp);
    NORMALIZE(&tmp, &camera->right);


    CROSS_PRODUCT(&camera->right, &camera->front, &camera->up);


    camera->fov = G_PI_2;

    camera->width = width;
    camera->height = height;

    camera->old_x = width/2;
    camera->old_y = height/2;

    camera->mouse_x = 0.0f;
    camera->mouse_y = 0.0f;



    MAT4x4 A;
    MAT4x4 B;

    INIT_MAT4X4(&A);
    INIT_MAT4X4(&B);


    VIEW(&camera->right,&camera->up,&camera->front, &A);
    TRANSLATION_(camera->position, &B);
    MAT4X4_X_MAT4x4(&A,&B, &camera->view);


}

void ProcessKeyBoard(Camera* camera, const float speed)
{
    const Uint8* Keys = SDL_GetKeyboardState(NULL);

    if(Keys[Z])
    {
        VEC4 tmp0;
        VEC4 tmp1;

        COEFF_M_VEC4(speed, &camera->front, &tmp0);
        ADD_VEC4(&camera->position, &tmp0, &tmp1);
        camera->position = tmp1;
    }
    else if (Keys[S])
    {
        VEC4 tmp0;

        COEFF_M_VEC4(speed, &camera->front, &tmp0);
        MIN_VEC4(&camera->position, &tmp0, &camera->position);
    }
    else if(Keys[D])
    {
        VEC4 tmp0;
        VEC4 tmp1;

        
        CROSS_PRODUCT(&camera->up, &camera->front, &tmp0);
        NORMALIZE(&tmp0, &tmp1);
        COEFF_M_VEC4(speed, &tmp1, &tmp1);
        ADD_VEC4(&camera->position, &tmp1, &camera->position);

    }
    else if(Keys[Q])
    {
        VEC4 tmp0;
        VEC4 tmp1;

        
        CROSS_PRODUCT(&camera->front, &camera->up, &tmp0);
        NORMALIZE(&tmp0, &tmp1);
        COEFF_M_VEC4(speed, &tmp1, &tmp1);
        ADD_VEC4(&camera->position, &tmp1, &camera->position);
    }


    

    MAT4x4 A;
    MAT4x4 B;

    INIT_MAT4X4(&A);
    INIT_MAT4X4(&B);

    
    VIEW(&camera->right,&camera->up,&camera->front, &A);
    TRANSLATION_(camera->position, &B);
    MAT4X4_X_MAT4x4(&A,&B, &camera->view);
}



void ProcessMouse(Camera* camera)
{
    int X;
    int Y;

    int offset_x;

    int offset_y;

    if(SDL_GetMouseState(&X,&Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        
            
            offset_x = X - camera->old_x;
            offset_y = camera->old_y - Y;
            

            if(!is_approx_equal(offset_x,0.0f) || !is_approx_equal(offset_y,0.0f))
            {
                camera->mouse_x += (float)(offset_x * 0.1f);
                camera->mouse_y += (float)(offset_y * 0.1f);

                camera->mouse_x =  90.0f < camera->mouse_x ?  90.0f : camera->mouse_x;
                camera->mouse_x = -90.0f > camera->mouse_x ? -90.0f : camera->mouse_x;
    
                camera->mouse_y =  90.0f < camera->mouse_y ?  90.0f : camera->mouse_y;
                camera->mouse_y = -90.0f > camera->mouse_y ? -90.0f : camera->mouse_y;
    
                printf("x = %f .\n", camera->mouse_x/camera->width);
                printf("y = %f .\n", camera->mouse_y/camera->height);


                VEC4 x = (VEC4){1.0f,0.0f,0.0f,0.0f};
                VEC4 x_ = (VEC4){-1.0f,0.0f,0.0f,0.0f};

                VEC4 y = (VEC4){0.0f,1.0f,0.0f,0.0f};
                VEC4 y_ = (VEC4){0.0f,-1.0f,0.0f,0.0f};

                VEC4 z = (VEC4){0.0f,0.0f,1.0f,0.0f};
                
                MAT4x4 tmp0;
                MAT4x4 tmp1;
                MAT4x4 tmp3;


                QUATERNION_ROTATION(radian(camera->mouse_y), &x_, &tmp0);
                QUATERNION_ROTATION(radian(camera->mouse_x), &y_, &tmp1);

                MAT4X4_X_MAT4x4(&tmp0, &tmp1, &tmp3);
                VEC4 res;
                
                MAT4X4_X_VEC4(&tmp3, &z, &res);
                DISPLAY_VEC4(&res);

                DISPLAY_VEC4(&camera->front);


                 
                NORMALIZE(&res, &camera->front);

                VEC4 tmp4;
                CROSS_PRODUCT(&camera->front, &x, &tmp4);
                NORMALIZE(&tmp4, &camera->up);

                VEC4 tmp5;
                CROSS_PRODUCT(&camera->front, &camera->up, &tmp5);
                NORMALIZE(&tmp5, &camera->right);
        
                MAT4x4 A;
                MAT4x4 B;
            
                INIT_MAT4X4(&A);
                INIT_MAT4X4(&B);
            
                VIEW(&camera->right,&camera->up,&camera->front, &A);
                TRANSLATION_(camera->position, &B);
                MAT4X4_X_MAT4x4(&A,&B, &camera->view);

                camera->old_x = X;
                camera->old_y = Y;
            }
        
    }



}
