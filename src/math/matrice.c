#include "matrice.h"


 void INIT_MAT4X4(MAT4x4* mat)
{
    mat->ROW_0_ = (VEC4){ 1.0f, 0.0f, 0.0f, 0.0f };
    mat->ROW_1_ = (VEC4){ 0.0f, 1.0f, 0.0f, 0.0f };
    mat->ROW_2_ = (VEC4){ 0.0f, 0.0f, 1.0f, 0.0f };
    mat->ROW_3_ = (VEC4){ 0.0f, 0.0f, 0.0f, 1.0f };
}

void DISPLAY_MAT4X4(MAT4x4* mat)
{
    LOGGING("[   %f  %f  %f  %f   ]\n", mat->ROW_0_.X, mat->ROW_0_.Y, mat->ROW_0_.Z, mat->ROW_0_.W);
    LOGGING("[   %f  %f  %f  %f   ]\n", mat->ROW_1_.X, mat->ROW_1_.Y, mat->ROW_1_.Z, mat->ROW_1_.W);
    LOGGING("[   %f  %f  %f  %f   ]\n", mat->ROW_2_.X, mat->ROW_2_.Y, mat->ROW_2_.Z, mat->ROW_2_.W);
    LOGGING("[   %f  %f  %f  %f   ]\n", mat->ROW_3_.X, mat->ROW_3_.Y, mat->ROW_3_.Z, mat->ROW_3_.W);
    LOGGING("\n");
}

void DISPLAY_VEC4(VEC4* vec)
{
    LOGGING("[%f]\n[%f]\n[%f]\n[%f]\n", vec->X, vec->Y, vec->Z, vec->W);
    LOGGING("\n");
}

void SCALAR_PRODUCT(VEC4* vec0, VEC4* vec1, float* result)
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

float determinant(MAT4x4* mat)
{
    return mat->CELL_11 *((mat->CELL_22 * mat->CELL_33 * mat->CELL_44) 
                        + (mat->CELL_23 * mat->CELL_34 * mat->CELL_42)
                        + (mat->CELL_24 * mat->CELL_32 * mat->CELL_43)
                        - (mat->CELL_24 * mat->CELL_33 * mat->CELL_42)
                        - (mat->CELL_23 * mat->CELL_32 * mat->CELL_44)
                        - (mat->CELL_22 * mat->CELL_34 * mat->CELL_43)) -

           mat->CELL_21 *((mat->CELL_12 * mat->CELL_33 * mat->CELL_44) 
                        + (mat->CELL_13 * mat->CELL_34 * mat->CELL_42)
                        + (mat->CELL_14 * mat->CELL_32 * mat->CELL_43)
                        - (mat->CELL_14 * mat->CELL_33 * mat->CELL_42)
                        - (mat->CELL_13 * mat->CELL_32 * mat->CELL_44)
                        - (mat->CELL_12 * mat->CELL_34 * mat->CELL_43)) +

           mat->CELL_31 *((mat->CELL_12 * mat->CELL_23 * mat->CELL_44) 
                        + (mat->CELL_13 * mat->CELL_24 * mat->CELL_42)
                        + (mat->CELL_14 * mat->CELL_22 * mat->CELL_43)
                        - (mat->CELL_14 * mat->CELL_23 * mat->CELL_42)
                        - (mat->CELL_13 * mat->CELL_22 * mat->CELL_44)
                        - (mat->CELL_12 * mat->CELL_24 * mat->CELL_43)) -

           mat->CELL_41 *((mat->CELL_12 * mat->CELL_23 * mat->CELL_34) 
                        + (mat->CELL_13 * mat->CELL_24 * mat->CELL_32)
                        + (mat->CELL_14 * mat->CELL_22 * mat->CELL_33)
                        - (mat->CELL_14 * mat->CELL_23 * mat->CELL_32)
                        - (mat->CELL_13 * mat->CELL_22 * mat->CELL_34)
                        - (mat->CELL_12 * mat->CELL_24 * mat->CELL_33)) ;
}


void MAT4X4_INVERSE(MAT4x4* mat, MAT4x4* result)
{
    float det = determinant(mat);
    ASSERT_LOGGING(det != 0,"matrix is inversable : %f\n",det);

    result->CELL_11 = (1.0f/det) * ( (mat->CELL_22 * mat->CELL_33 * mat->CELL_44) + (mat->CELL_23 * mat->CELL_34 * mat->CELL_42) + (mat->CELL_24 * mat->CELL_32 * mat->CELL_43) -
                                     (mat->CELL_24 * mat->CELL_33 * mat->CELL_42) - (mat->CELL_23 * mat->CELL_32 * mat->CELL_44) - (mat->CELL_22 * mat->CELL_34 * mat->CELL_43));
    result->CELL_12 = (1.0f/det) * (-(mat->CELL_12 * mat->CELL_33 * mat->CELL_44) - (mat->CELL_13 * mat->CELL_34 * mat->CELL_42) - (mat->CELL_14 * mat->CELL_32 * mat->CELL_43) +
                                     (mat->CELL_14 * mat->CELL_33 * mat->CELL_42) + (mat->CELL_13 * mat->CELL_32 * mat->CELL_44) + (mat->CELL_12 * mat->CELL_34 * mat->CELL_43));
    result->CELL_13 = (1.0f/det) * ( (mat->CELL_12 * mat->CELL_23 * mat->CELL_44) + (mat->CELL_13 * mat->CELL_24 * mat->CELL_42) + (mat->CELL_14 * mat->CELL_22 * mat->CELL_43) -
                                     (mat->CELL_14 * mat->CELL_23 * mat->CELL_42) - (mat->CELL_13 * mat->CELL_22 * mat->CELL_44) - (mat->CELL_12 * mat->CELL_24 * mat->CELL_43));
    result->CELL_14 = (1.0f/det) * (-(mat->CELL_12 * mat->CELL_23 * mat->CELL_34) - (mat->CELL_13 * mat->CELL_24 * mat->CELL_32) - (mat->CELL_14 * mat->CELL_22 * mat->CELL_33) +
                                     (mat->CELL_14 * mat->CELL_23 * mat->CELL_32) + (mat->CELL_13 * mat->CELL_22 * mat->CELL_34) + (mat->CELL_12 * mat->CELL_24 * mat->CELL_33));

    result->CELL_21 = (1.0f/det) * (-(mat->CELL_21 * mat->CELL_33 * mat->CELL_44) - (mat->CELL_23 * mat->CELL_34 * mat->CELL_41) - (mat->CELL_24 * mat->CELL_31 * mat->CELL_43) +
                                     (mat->CELL_24 * mat->CELL_33 * mat->CELL_41) + (mat->CELL_23 * mat->CELL_31 * mat->CELL_44) + (mat->CELL_21 * mat->CELL_34 * mat->CELL_43));
    result->CELL_22 = (1.0f/det) * ( (mat->CELL_11 * mat->CELL_33 * mat->CELL_44) + (mat->CELL_13 * mat->CELL_34 * mat->CELL_41) + (mat->CELL_14 * mat->CELL_31 * mat->CELL_43) -
                                     (mat->CELL_14 * mat->CELL_33 * mat->CELL_41) - (mat->CELL_13 * mat->CELL_31 * mat->CELL_44) - (mat->CELL_11 * mat->CELL_34 * mat->CELL_43));
    result->CELL_23 = (1.0f/det) * (-(mat->CELL_11 * mat->CELL_23 * mat->CELL_44) - (mat->CELL_13 * mat->CELL_24 * mat->CELL_41) - (mat->CELL_14 * mat->CELL_21 * mat->CELL_43) +
                                     (mat->CELL_14 * mat->CELL_23 * mat->CELL_41) + (mat->CELL_13 * mat->CELL_21 * mat->CELL_44) + (mat->CELL_11 * mat->CELL_24 * mat->CELL_43));
    result->CELL_24 = (1.0f/det) * ( (mat->CELL_11 * mat->CELL_23 * mat->CELL_34) + (mat->CELL_13 * mat->CELL_24 * mat->CELL_31) + (mat->CELL_14 * mat->CELL_21 * mat->CELL_33) -
                                     (mat->CELL_14 * mat->CELL_23 * mat->CELL_31) - (mat->CELL_13 * mat->CELL_21 * mat->CELL_34) - (mat->CELL_11 * mat->CELL_24 * mat->CELL_33));

    result->CELL_31 = (1.0f/det) * ( (mat->CELL_21 * mat->CELL_32 * mat->CELL_44) + (mat->CELL_22 * mat->CELL_34 * mat->CELL_41) + (mat->CELL_24 * mat->CELL_31 * mat->CELL_42) -
                                     (mat->CELL_24 * mat->CELL_32 * mat->CELL_41) - (mat->CELL_22 * mat->CELL_31 * mat->CELL_44) - (mat->CELL_21 * mat->CELL_34 * mat->CELL_42));
    result->CELL_32 = (1.0f/det) * (-(mat->CELL_11 * mat->CELL_32 * mat->CELL_44) - (mat->CELL_12 * mat->CELL_34 * mat->CELL_41) - (mat->CELL_14 * mat->CELL_31 * mat->CELL_42) +
                                     (mat->CELL_14 * mat->CELL_32 * mat->CELL_41) + (mat->CELL_12 * mat->CELL_31 * mat->CELL_44) + (mat->CELL_11 * mat->CELL_34 * mat->CELL_42));
    result->CELL_33 = (1.0f/det) * ( (mat->CELL_11 * mat->CELL_22 * mat->CELL_44) + (mat->CELL_12 * mat->CELL_24 * mat->CELL_41) + (mat->CELL_14 * mat->CELL_21 * mat->CELL_42) -
                                     (mat->CELL_14 * mat->CELL_22 * mat->CELL_41) - (mat->CELL_12 * mat->CELL_21 * mat->CELL_44) - (mat->CELL_11 * mat->CELL_24 * mat->CELL_42));
    result->CELL_34 = (1.0f/det) * (-(mat->CELL_11 * mat->CELL_22 * mat->CELL_34) - (mat->CELL_12 * mat->CELL_24 * mat->CELL_31) - (mat->CELL_14 * mat->CELL_21 * mat->CELL_42) +
                                     (mat->CELL_14 * mat->CELL_22 * mat->CELL_31) + (mat->CELL_12 * mat->CELL_21 * mat->CELL_34) + (mat->CELL_11 * mat->CELL_24 * mat->CELL_42));

    result->CELL_41 = (1.0f/det) * (-(mat->CELL_21 * mat->CELL_32 * mat->CELL_43) - (mat->CELL_22 * mat->CELL_33 * mat->CELL_41) - (mat->CELL_23 * mat->CELL_31 * mat->CELL_42) +
                                     (mat->CELL_23 * mat->CELL_32 * mat->CELL_41) + (mat->CELL_22 * mat->CELL_31 * mat->CELL_43) + (mat->CELL_21 * mat->CELL_33 * mat->CELL_42));
    result->CELL_42 = (1.0f/det) * ( (mat->CELL_11 * mat->CELL_32 * mat->CELL_43) + (mat->CELL_12 * mat->CELL_33 * mat->CELL_41) + (mat->CELL_13 * mat->CELL_31 * mat->CELL_42) -
                                     (mat->CELL_13 * mat->CELL_32 * mat->CELL_41) - (mat->CELL_12 * mat->CELL_31 * mat->CELL_43) - (mat->CELL_11 * mat->CELL_33 * mat->CELL_42));
    result->CELL_43 = (1.0f/det) * (-(mat->CELL_11 * mat->CELL_22 * mat->CELL_43) - (mat->CELL_12 * mat->CELL_23 * mat->CELL_41) - (mat->CELL_13 * mat->CELL_21 * mat->CELL_42) +
                                     (mat->CELL_13 * mat->CELL_22 * mat->CELL_41) + (mat->CELL_12 * mat->CELL_21 * mat->CELL_43) + (mat->CELL_11 * mat->CELL_23 * mat->CELL_42));
    result->CELL_44 = (1.0f/det) * ( (mat->CELL_11 * mat->CELL_22 * mat->CELL_33) + (mat->CELL_12 * mat->CELL_23 * mat->CELL_31) + (mat->CELL_13 * mat->CELL_21 * mat->CELL_32) -
                                     (mat->CELL_13 * mat->CELL_22 * mat->CELL_31) - (mat->CELL_12 * mat->CELL_21 * mat->CELL_33) - (mat->CELL_11 * mat->CELL_23 * mat->CELL_32));
}


void MAT4X4_TRANSPOSE(MAT4x4* mat, MAT4x4* result)
{
    unsigned int j = 0;
    for(unsigned int i = 0; i < 16; i+=4)
    {
        result->RAW_[i]     = mat->RAW_[j];
        result->RAW_[i + 1] = mat->RAW_[j + 4];
        result->RAW_[i + 2] = mat->RAW_[j + 8];
        result->RAW_[i + 3] = mat->RAW_[j + 12];
        ++j;
    }
}

void TRANSLATION(MAT4x4* mat, const float x, const float y, const float z, MAT4x4* result)
{
    result->CELL_11  = mat->CELL_11  + x;
    result->CELL_22  = mat->CELL_22  + y;
    result->CELL_33  = mat->CELL_33  + z;
}

void TRANSLATION_(MAT4x4* mat, const VEC4 vec, MAT4x4* result)
{
    result->CELL_11  = mat->CELL_11  + vec.X;
    result->CELL_22  = mat->CELL_22  + vec.Y;
    result->CELL_33  = mat->CELL_33  + vec.Z;
}

void PERSPECTIVE_PROJECTION_RIGHT_HANDED(const float fov, const float apsect_ratio, const float near, const float far, MAT4x4* result)
{
    result->CELL_11 =  1.0f/apsect_ratio * tanf(fov/2);
    result->CELL_22 =  1.0f/tanf(fov/2);

    result->CELL_33 = (-far-near)/(far - near);
    result->CELL_34 = -2.0f*near*far/(far - near);

    result->CELL_43 = -1.0f;

}

void PERSPECTIVE_PROJECTION_LEFT_HANDED(const float fov, const float apsect_ratio, const float near, const float far, MAT4x4* result)
{
    result->CELL_11 =  1.0f/apsect_ratio * tanf(fov/2);
    result->CELL_22 =  1.0f/tanf(fov/2);

    result->CELL_33 = (-near-far)/(near - far);
    result->CELL_34 = 2.0f*near*far/(near - far);
    
    result->CELL_43 = -1.0f;
}