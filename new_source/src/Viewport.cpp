#include "Viewport.h"

Vector4d swClipCoordinates(const Matrix4x4& finalMatrix, const Vector3d& eyeCoordinate)
{
        static Vector4d vertex;

        vertex[0] = eyeCoordinate[0];
        vertex[1] = eyeCoordinate[1];
        vertex[2] = eyeCoordinate[2];
        vertex[3] = 1.0f;

        return (finalMatrix * vertex);
}

void swNormalizeDeviceCoordinates(Vector4d& clipCoordinates)
{
        clipCoordinates /= clipCoordinates[3];
}

void swViewport(const int xOffset, const int yOffset, const int width, const int height, float& x, float& y)
{
    x = (x + 1.0f) * (width/2.0f) + xOffset;
    y = (y + 1.0f) * (height/2.0f) + yOffset;
}
