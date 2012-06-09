#include <iostream>
#include <algorithm>
using std::swap;

#include <unistd.h>
#include <time.h>
#include <math.h>

#include "display.h"
#include "rasterizer.h"
#include "matrix.h"

int main()
{
    const int width = 320;
    const int height = 240;

    float p1[] = {-1, -1, 0};
    float p2[] = {0, 1, 0};
    float p3[] = {1, -1, 0};

    const float pi = 3.14159265f;

    Display display(width, height);
    Frame frame(width, height);

    float pCam[] = {0, 0, -2};

    float cameraAlphaX = 0.0f*pi/180.0f;
    float cameraAlphaY = 0.0f*pi/180.0f;
    float cameraAlphaZ = 0.0f*pi/180.0f;

    float cx[] = {1.0f,    0.0f,               0.0f,
        0.0f,    cosf(cameraAlphaX),  -sinf(cameraAlphaX), 
        0.0f,    sinf(cameraAlphaX),  cosf(cameraAlphaX)};

    float cy[] = {cosf(cameraAlphaY),    0.0f,  sinf(cameraAlphaY), 
        0.0f,                  1.0f,  0.0f, 
        -sinf(cameraAlphaY),   0.0f,  cosf(cameraAlphaY)};

    float cz[] = {cosf(cameraAlphaZ),    -sinf(cameraAlphaZ), 0.0f, 
        sinf(cameraAlphaZ),    cosf(cameraAlphaZ),  0.0f, 
        0.0f,                  0.0f,               1.0f};

    Matrix<float> cameraTransformX(3,3,cx); 
    Matrix<float> cameraTransformY(3,3,cy); 
    Matrix<float> cameraTransformZ(3,3,cz); 

    Matrix<float> cameraPoint(3,1,pCam); 

    Matrix<float> cameraTransformation = cameraTransformX*cameraTransformY*cameraTransformZ;
    Matrix<float> currentPoint(3, 1);

    currentPoint = p1;
    Matrix<float> P1(3, 1);
    P1 = currentPoint - cameraPoint;
    P1 = cameraTransformation*P1;

    currentPoint = p2;
    Matrix<float> P2(3, 1);
    P2 = currentPoint - cameraPoint;
    P2 = cameraTransformation*P2;

    currentPoint = p3;
    Matrix<float> P3(3, 1);
    P3 = currentPoint - cameraPoint;
    P3 = cameraTransformation*P3;

    Matrix<float> PS1(2, 1);
    Matrix<float> PS2(2, 1);
    Matrix<float> PS3(2, 1);

    float ez /*fov*/ = 1.0f / tan(90.0f*pi/180.0f / 2.0f);
    float ex  = width/2;
    float ey  = height/2;

    PS1[0][0] = (P1[0][0]*(ez / P1[2][0]) *100 + ex);
    PS1[1][0] = (P1[1][0]*(ez / P1[2][0]) *100 + ey);

    PS2[0][0] = (P2[0][0]*(ez / P2[2][0]) *100 + ex);
    PS2[1][0] = (P2[1][0]*(ez / P2[2][0]) *100 + ey);

    PS3[0][0] = (P3[0][0]*(ez / P3[2][0]) *100 + ex);
    PS3[1][0] = (P3[1][0]*(ez / P3[2][0]) *100 + ey);

    //    PS1[0][0] = (P1[0][0] - ex)*(ez / P1[2][0]);
    //    PS1[1][0] = (P1[1][0] - ey)*(ez / P1[2][0]);
    //    PS2[0][0] = (P2[0][0] - ex)*(ez / P2[2][0]);
    //    PS2[1][0] = (P2[1][0] - ey)*(ez / P2[2][0]);
    //    PS3[0][0] = (P3[0][0] - ex)*(ez / P3[2][0]);
    //    PS3[1][0] = (P3[1][0] - ey)*(ez / P3[2][0]);

    P1.print("virtual 1:");
    P2.print("virtual 2:");
    P3.print("virtual 3:");

    PS1.print("screen 1:");
    PS2.print("screen 2:");
    PS3.print("screen 3:");


    drawLine(PS1[0][0], PS1[1][0], PS2[0][0], PS2[1][0], frame);
    drawLine(PS2[0][0], PS2[1][0], PS3[0][0], PS3[1][0], frame);
    drawLine(PS3[0][0], PS3[1][0], PS1[0][0], PS1[1][0], frame);

    display.render(frame);

    sleep(1);
}
