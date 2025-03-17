#include "matrice.h"


inline void INIT_MAT4X4(MAT4x4* mat)
{
    mat->ROW_0_ = (VEC4){ 1.0f, 0.0f, 0.0f, 0.0f };
    mat->ROW_1_ = (VEC4){ 0.0f, 1.0f, 0.0f, 0.0f };
    mat->ROW_2_ = (VEC4){ 0.0f, 0.0f, 1.0f, 0.0f };
    mat->ROW_3_ = (VEC4){ 0.0f, 0.0f, 0.0f, 1.0f };
}

void DISPLAY_MAT4X4(MAT4x4* mat)
{
    printf("[   %f  %f  %f  %f   ]\n", mat->ROW_0_.X, mat->ROW_0_.Y, mat->ROW_0_.Z, mat->ROW_0_.W);
    printf("[   %f  %f  %f  %f   ]\n", mat->ROW_1_.X, mat->ROW_1_.Y, mat->ROW_1_.Z, mat->ROW_1_.W);
    printf("[   %f  %f  %f  %f   ]\n", mat->ROW_2_.X, mat->ROW_2_.Y, mat->ROW_2_.Z, mat->ROW_2_.W);
    printf("[   %f  %f  %f  %f   ]\n", mat->ROW_3_.X, mat->ROW_3_.Y, mat->ROW_3_.Z, mat->ROW_3_.W);
}

void DISPLAY_VEC4(VEC4* vec)
{
    printf("[%f]\n[%f]\n[%f]\n[%f]\n", vec->X, vec->Y, vec->Z, vec->W);

}

inline void SCALAR_PRODUCT(VEC4* vec0, VEC4* vec1, float* result)
{
    *result = (((vec0->X * vec1->X) + (vec0->Y * vec1->Y)) + (vec0->Z * vec1->Z)) + (vec0->W * vec1->W);
}


void MAT4X4_X_VEC4(MAT4x4* mat, VEC4* vec, VEC4* result)
{
    SCALAR_PRODUCT(&mat->ROW_0_, vec, &result->X);
    SCALAR_PRODUCT(&mat->ROW_1_, vec, &result->Y);
    SCALAR_PRODUCT(&mat->ROW_2_, vec, &result->Z);
    SCALAR_PRODUCT(&mat->ROW_3_, vec, &result->W);
}


void MAT4X4_X_MAT4x4(MAT4x4* mat0, MAT4x4* mat1, MAT4x4* result)
{
    for(unsigned int i = 0; i < 16; i += 4)
    {
        result->RAW_[i]     = (mat0->RAW_[i]     * mat1->RAW_[0])  + (mat0->RAW_[i + 1] * mat1->RAW_[4]) + 
                              (mat0->RAW_[i + 2] * mat1->RAW_[8])  + (mat0->RAW_[i + 3] * mat1->RAW_[12]);
        result->RAW_[i + 1] = (mat0->RAW_[i]     * mat1->RAW_[1])  + (mat0->RAW_[i + 1] * mat1->RAW_[5]) + 
                              (mat0->RAW_[i + 2] * mat1->RAW_[9])  + (mat0->RAW_[i + 3] * mat1->RAW_[13]);

        result->RAW_[i + 2] = (mat0->RAW_[i]     * mat1->RAW_[2])  + (mat0->RAW_[i + 1] * mat1->RAW_[6]) + 
                              (mat0->RAW_[i + 2] * mat1->RAW_[10]) + (mat0->RAW_[i + 3] * mat1->RAW_[14]);
        result->RAW_[i + 3] = (mat0->RAW_[i]     * mat1->RAW_[3])  + (mat0->RAW_[i + 1] * mat1->RAW_[7]) + 
                              (mat0->RAW_[i + 2] * mat1->RAW_[11]) + (mat0->RAW_[i + 3] * mat1->RAW_[15]);
    }
}

