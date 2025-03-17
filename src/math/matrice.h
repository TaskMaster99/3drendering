#ifndef MATRICE_H
#define MATRICE_H

#include <stdlib.h>
#include <stdio.h>

#define ROW_0_ DATA.FORMATED.ROW_0 
#define ROW_1_ DATA.FORMATED.ROW_1
#define ROW_2_ DATA.FORMATED.ROW_2 
#define ROW_3_ DATA.FORMATED.ROW_3 

#define RAW_ DATA.RAW

/**
* Vector with 4 floating compenants
*/
typedef struct VEC4
{

    float X;
    float Y;
    float Z;
    float W;

}VEC4;

/**
 * MAT4x4, a 4 by 4 matrice
 */
typedef struct MAT4x4
{
    union 
    {
        struct FORMATED
        {
            VEC4 ROW_0;
            VEC4 ROW_1;
            VEC4 ROW_2;
            VEC4 ROW_3;
        }FORMATED;

        float RAW[16];
    }DATA;
    

} MAT4x4;

/**
 * Initialiaze the matrice 4x4
 * @param mat matrice 4x4
 */
void INIT_MAT4X4(MAT4x4* mat);

/**
 * display the matrice 4x4
 * @param mat matrice 4x4
 */
void DISPLAY_MAT4X4(MAT4x4* mat);
/**
 * display the vector of 4 compenants
 * @param vec vectro 4
 */
void DISPLAY_VEC4(VEC4* vec);

/**
 * Scalar product between two vector 4
 * @param vec0 vectro 4
 * @param vec1 vectro 4
 * @param result result of the scalar product
 */
void SCALAR_PRODUCT(VEC4* vec0, VEC4* vec1, float* result);

/**
 * mutliplication beetwen matrice 4x4 and a vector 4 compenants
 * @param mat matrice 4x4
 * @param vec vectro 4
 * @param result vector 4 result of the the product beetween a matrice 4x4 and a vector 4
 */
void MAT4X4_X_VEC4(MAT4x4* mat, VEC4* vec, VEC4* result);
/**
 * mutliplication beetwen matrice 4x4 and a matrice 4x4
 * @param mat0 matrice 4x4
 * @param mat1 matrice 4x4
 * @param result matrice 4x4 result of the the product beetween a matrice 4x4 and a matrice 4x4
 */
void MAT4X4_X_MAT4x4(MAT4x4* mat0, MAT4x4* mat1, MAT4x4* result);
/**
 * inversion of a matrice 4x4
 * @param mat matrice 4x4
 * @param result inversed matrice 4x4 
 */
void MAT4X4_INVERSE(MAT4x4* mat, MAT4x4* result);
/**
 * transpose of a matrice 4x4
 * @param mat matrice 4x4
 * @param result transposed matrice 4x4
 */
void MAT4X4_TRANSPOSE(MAT4x4* mat, MAT4x4* result);

/**
 * translation of a matrice 4x4
 * @param mat matrice 4x4
 * @param x x-axis 
 * @param y y-axis
 * @param z z-axis  
 * @param result translated matrice 4x4
 */
void TRANSLATION(MAT4x4* mat, const float x, const float y, const float z, MAT4x4* result);
/**
 * translation of a matrice 4x4
 * @param mat matrice 4x4
 * @param vec vector translation
 * @param result translated matrice 4x4
 */
void TRANSLATION_(MAT4x4* mat, const VEC4 vec, MAT4x4* result);

void PERSPECTIVE_PROJECTION_RIGHT_HAND();
void PERSPECTIVE_PROJECTION_LEFT_HAND();

void ORTHOGRAPHIC_PROJECTION();

void EULER_ROTATION();
void QUATERNION_ROTATION();

#endif


