#ifndef MATRICE_H
#define MATRICE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../utils/utils.h"

#define ROW_0_ DATA.FORMATED.ROW_0 
#define ROW_1_ DATA.FORMATED.ROW_1
#define ROW_2_ DATA.FORMATED.ROW_2 
#define ROW_3_ DATA.FORMATED.ROW_3 

#define CELL_11 DATA.RAW[0]
#define CELL_12 DATA.RAW[1]
#define CELL_13 DATA.RAW[2]
#define CELL_14 DATA.RAW[3]

#define CELL_21 DATA.RAW[4]
#define CELL_22 DATA.RAW[5]
#define CELL_23 DATA.RAW[6]
#define CELL_24 DATA.RAW[7]

#define CELL_31 DATA.RAW[8]
#define CELL_32 DATA.RAW[9]
#define CELL_33 DATA.RAW[10]
#define CELL_34 DATA.RAW[11]

#define CELL_41 DATA.RAW[12]
#define CELL_42 DATA.RAW[13]
#define CELL_43 DATA.RAW[14]
#define CELL_44 DATA.RAW[15]


#define RAW_ DATA.RAW

/**
* Vector with 4 floating compenants
* @param X x coordinate
* @param Y y coordinate
* @param Z z coordinate
* @param W w width
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
 * @param ROW_0 row 0
 * @param ROW_1 row 1
 * @param ROW_2 row 2
 * @param ROW_3 row 3
 * @param RAW pointer to the matrix
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
 * determinant of a matrice 4x4
 * @param mat matrice 4x4
 * @return determinant
 */
float determinant(MAT4x4* mat);
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

/**
 * matrice 4x4 perspective projection right handed
 * @param fov field of view
 * @param apsect_ratio aspect ration
 * @param near Znear
 * @param far Zfar
 * @param result the matrice 4x4 perspective projection
 */
void PERSPECTIVE_PROJECTION_RIGHT_HANDED(const float fov, const float apsect_ratio, const float near, const float far, MAT4x4* result);
/**
 * matrice 4x4 perspective projection left handed
 * @param fov field of view
 * @param apsect_ratio aspect ratio
 * @param near Znear
 * @param far Zfar
 * @param result the matrice 4x4 perspective projection
 */
void PERSPECTIVE_PROJECTION_LEFT_HANDED(const float fov, const float apsect_ratio, const float near, const float far, MAT4x4* result);

/**
 * matrice 4x4 orthographic projection
 * @param near Znear
 * @param far Zfar
 * @param right Xright
 * @param left Xleft
 * @param top Ytop
 * @param bottom Ybottom
 * @param result the matrice 4x4 orthographic projection
 */
void ORTHOGRAPHIC_PROJECTION(const float near, const float far, const float right, const float left, const float top, const float bottom, MAT4x4* result);

/**
 * matrice 4x4 euler rotation
 * @param coord vector axes rotation
 * @param result the matrice 4x4 eurler rotation
 */
void EULER_ROTATION(VEC4* coord, MAT4x4* result);
/**
 * matrice 4x4 euler rotation
 * @param radian angle in radian
 * @param x x axes rotation
 * @param y y axes rotation
 * @param z z axes rotation
 * @param result the matrice 4x4 eurler rotation
 */
void EULER_ROTATION_(const float x, const float y, const float z, MAT4x4* result);
/**
 * matrice 4x4 quaternion rotation
 * @param coord rotation axes
 * @param result the matrice 4x4 quaternion rotation
 */
void QUATERNION_ROTATION(VEC4* coord, MAT4x4* result);
/**
 * matrice 4x4 quaternion rotation
 * @param x x axes rotation
 * @param y y axes rotation
 * @param z z axes rotation
 * @param w w axes rotation
 * @param result the matrice 4x4 quaternion rotation
 */
void QUATERNION_ROTATION_(const float x, const float y, const float z, const float w, MAT4x4* result);
/**
 * matrice 4x4 view
 * @param u right x axes rotation
 * @param v up y axes rotation
 * @param n forward z axes rotation
 * @param result the matrice 4x4 view
 */
void VIEW(const VEC4* u, const VEC4* v, const VEC4* n, MAT4x4* result);

#endif


