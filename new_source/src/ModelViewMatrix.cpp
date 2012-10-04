#include "ModelViewMatrix.h"

void swTranslate(ModelViewMatrix& matrix, float x, float y, float z)
{
    float data[16] = 
    {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };

    matrix *= Matrix4x4(data);
}

void swLookAt(ModelViewMatrix& matrix, const Vector3d& eye, const Vector3d& target, const Vector3d& upVector)
{
    static Vector3d forward;
    forward = target - eye;
    forward.normalize();

    static Vector3d side;
    side = Vector3dCrossProduct(forward, upVector);
    side.normalize();

    static Vector3d up;
    up = Vector3dCrossProduct(side, forward);

    matrix *= Matrix4x4
        ( 
         side[0],       side[1],        side[2],        0.0f,
         up[0],         up[1],          up[2],          0.0f, 
         -forward[0],   -forward[1],    -forward[2],    0.0f,
         0.0f,          0.0f,           0.0f,           1.0f            
        );

    swTranslate(matrix, -eye[0], -eye[1], -eye[2]);
}

void swLoadIdentity(ModelViewMatrix& matrix)
{
    matrix = Matrix4x4
        (
         1,0,0,0,
         0,1,0,0,
         0,0,1,0,
         0,0,0,1
        );
}
