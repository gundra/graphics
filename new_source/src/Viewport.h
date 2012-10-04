#include "Matrix4x4.h"
#include "Vector3d.h"
#include "Vector4d.h"

Vector4d swClipCoordinates(const Matrix4x4& finalMatrix, const Vector3d& eyeCoordinate);

void swNormalizeDeviceCoordinates(Vector4d& clipCoordinates);

void swViewport(const int xOffset, const int yOffset, const int width, const int height, float& x, float& y);
