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

void TRANSLATION(const float x, const float y, const float z, MAT4x4* result)
{
    result->CELL_14  = x;
    result->CELL_24  = y;
    result->CELL_34  = z;
}

void TRANSLATION_(const VEC4 vec, MAT4x4* result)
{
    result->CELL_14  = vec.X;
    result->CELL_24  = vec.Y;
    result->CELL_34  = vec.Z;
}

void PERSPECTIVE_PROJECTION_RIGHT_HANDED(const float fov, const float apsect_ratio, const float near, const float far, MAT4x4* result)
{
    result->CELL_11 =  1.0f/(apsect_ratio * tanf(fov/2.0f));
    result->CELL_22 =  1.0f/tanf(fov/2.0f);

    result->CELL_33 = (-far-near)/(far - near);
    result->CELL_34 = -2.0f*near*far/(far - near);

    result->CELL_43 = -1.0f;

}

void PERSPECTIVE_PROJECTION_LEFT_HANDED(const float fov, const float apsect_ratio, const float near, const float far, MAT4x4* result)
{
    result->CELL_11 =  1.0f/(apsect_ratio * tanf(fov/2.0f));
    result->CELL_22 =  1.0f/tanf(fov/2);

    result->CELL_33 = (-near-far)/(near - far);
    result->CELL_34 = 2.0f*near*far/(near - far);
    
    result->CELL_43 = -1.0f;
}

void ORTHOGRAPHIC_PROJECTION(const float near, const float far, const float right, const float left, const float top, const float bottom, MAT4x4* result)
{
    result->CELL_11 = 2.0f/(right - left);
    result->CELL_14 = -(right + left)/(right - left);

    result->CELL_22 = 2.0f/(top - bottom);
    result->CELL_24 = -(top + bottom)/(top - bottom);

    result->CELL_33 = -2.0f/(far - near);
    result->CELL_34 = -(far + near)/(far - near);

    result->CELL_44 = 1.0f;
}

void EULER_ROTATION(VEC4* coord, MAT4x4* result)
{
    const float cos_psi = cos(coord->X);
    const float sin_psi = sin(coord->X);

    const float cos_theta = cos(coord->Y);
    const float sin_theta = sin(coord->Y);

    const float cos_phi = cos(coord->Z);
    const float sin_phi = sin(coord->Z);

    result->CELL_11 = cos_theta * cos_phi;
    result->CELL_12 = sin_psi * sin_theta * cos_phi - cos_psi * sin_phi;
    result->CELL_13 = cos_psi * sin_theta * cos_phi + sin_psi * sin_phi;

    result->CELL_21 = cos_theta * sin_phi;
    result->CELL_22 = sin_psi * sin_theta * sin_phi + sin_psi * cos_phi;
    result->CELL_23 = cos_psi * sin_theta * sin_phi - sin_psi * cos_phi;

    result->CELL_31 = -sin_theta;
    result->CELL_32 = sin_psi * cos_theta;
    result->CELL_33 = cos_psi * cos_theta;

    result->CELL_44 = 1.0f;
}

void EULER_ROTATION_(const float x, const float y, const float z, MAT4x4* result)
{
    const float cos_psi = cos(x); // yaw
    const float sin_psi = sin(x);
    
    const float cos_theta = cos(y); // pitch
    const float sin_theta = sin(y);
    
    const float cos_phi = cos(z); // roll
    const float sin_phi = sin(z);
    

    result->CELL_11 = cos_theta * cos_psi;
    result->CELL_12 = -cos_theta * sin_psi;
    result->CELL_13 = sin_theta;
    
    result->CELL_21 = cos_phi * sin_psi + cos_psi * sin_phi * sin_theta;
    result->CELL_22 = cos_phi * cos_psi - sin_psi * sin_phi * sin_theta;
    result->CELL_23 = -cos_theta * sin_phi;
    
    result->CELL_31 = sin_phi * sin_psi - cos_phi * cos_psi * sin_theta;
    result->CELL_32 = cos_phi * sin_psi + cos_psi * sin_phi * sin_theta;
    result->CELL_33 = cos_phi * cos_theta;
    
    result->CELL_44 = 1.0f;
    

}

void QUATERNION_ROTATION(const float radian, VEC4* coord, MAT4x4* result)
{
    const float q0 = cos(radian/2.0f);
    const float q1 = coord->X * sin(radian/2.0f);
    const float q2 = coord->Y * sin(radian/2.0f);
    const float q3 = coord->Z * sin(radian/2.0f);

    result->CELL_11 = 1.0f - (2.0f*q2*q2) - (2.0f*q3*q3);
    result->CELL_12 = (2.0f*q1*q2) - (2.0f*q0*q3);
    result->CELL_13 = (2.0f*q1*q3) + (2.0f*q0*q2);

    result->CELL_21 = (2.0f*q1*q2) + (2.0f*q0*q3);
    result->CELL_22 = 1.0f - (2.0f*q1*q1) - (2.0f*q3*q3);
    result->CELL_23 = (2.0f*q2*q3) - (2.0f*q0*q1);

    result->CELL_31 = (2.0f*q1*q3) - (2.0f*q0*q2);
    result->CELL_32 = (2.0f*q2*q3) + (2.0f*q0*q1);
    result->CELL_33 = 1.0f - (2.0f*q1*q1) - (2.0f*q2*q2);

    result->CELL_44 = 1.0f;

}

void QUATERNION_ROTATION_(const float radian, const float x, const float y, const float z, const float w, MAT4x4* result)
{
    const float q0 = cos(radian/2.0f);
    const float q1 = x * sin(radian/2.0f);
    const float q2 = y * sin(radian/2.0f);
    const float q3 = z * sin(radian/2.0f);

    result->CELL_11 = 1.0f - (2.0f*q2*q2) - (2.0f*q3*q3);
    result->CELL_12 = (2.0f*q1*q2) - (2.0f*q0*q3);
    result->CELL_13 = (2.0f*q1*q3) + (2.0f*q0*q2);

    result->CELL_21 = (2.0f*q1*q2) + (2.0f*q0*q3);
    result->CELL_22 = 1.0f - (2.0f*q1*q1) - (2.0f*q3*q3);
    result->CELL_23 = (2.0f*q2*q3) - (2.0f*q0*q1);

    result->CELL_31 = (2.0f*q1*q3) - (2.0f*q0*q2);
    result->CELL_32 = (2.0f*q2*q3) + (2.0f*q0*q1);
    result->CELL_33 = 1.0f - (2.0f*q1*q1) - (2.0f*q2*q2);

    result->CELL_44 = 1.0f;
}

void VIEW(const VEC4* u, const VEC4* v, const VEC4* n, MAT4x4* result)
{
    result->CELL_11 = u->X;
    result->CELL_12 = u->Y;
    result->CELL_13 = u->Z;

    result->CELL_21 = v->X;
    result->CELL_22 = v->Y;
    result->CELL_23 = v->Z;

    result->CELL_31 = n->X;
    result->CELL_32 = n->Y;
    result->CELL_33 = n->Z;

    result->CELL_44 = 1.0f;
}