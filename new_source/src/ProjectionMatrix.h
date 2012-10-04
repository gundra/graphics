#include "Matrix4x4.h"

typedef Matrix4x4 ProjectionMatrix;

void swOrtho(ProjectionMatrix& matrix, float left, float right, float bottom, float top, float zNear, float zFar);

void swPerspective(ProjectionMatrix& matrix, float fovy, float aspect, float zNear, float zFar);
