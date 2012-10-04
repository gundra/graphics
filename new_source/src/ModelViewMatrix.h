#include "Matrix4x4.h"
#include "Vector3d.h"

typedef Matrix4x4 ModelViewMatrix;

void swTranslate(ModelViewMatrix& matrix, float x, float y, float z);

void swLookAt(Matrix4x4& matrix, const Vector3d& eye, const Vector3d& target, const Vector3d& upVector);

void swLoadIdentity(ModelViewMatrix& matrix);
