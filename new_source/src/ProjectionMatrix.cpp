#include "ProjectionMatrix.h"
#include <math.h>

void swOrtho(ProjectionMatrix& matrix, float left, float right, float bottom, float top, float zNear, float zFar)
{
    matrix = Matrix4x4
        (
         2.0f/(right-left), 0.0f,              0.0f,                  -(right+left)/(right-left),
         0.0f,              2.0f/(top-bottom), 0.0f,                  -(top+bottom)/(top-bottom),
         0.0f,              0.0f,              -2.0f/(zFar-zNear),    -(zFar+zNear)/(zFar-zNear), 
         0.0f,              0.0f,              0.0f,                  1.0f
        );
}

void swPerspective(ProjectionMatrix& matrix, float fovy, float aspect, float zNear, float zFar)
{
    float f = 1.0f/tan((fovy * 3.14159265f / 180.0) / 2.0f);

    matrix = Matrix4x4
        (
         f/aspect,   0.0f,   0.0f,                           0.0f,
         0.0f,       f,      0.0f,                           0.0f,
         0.0f,       0.0f,   (zFar + zNear)/(zNear - zFar),  2.0f * zFar * zNear/(zNear - zFar),
         0.0f,       0.0f,   -1.0f,                          0.0f
        );
}

