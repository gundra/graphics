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

    float p1[] = {-1, 0, 0};
    float p2[] = {0, 1, 0};
    float p3[] = {1, 0, 0};

    float pCam[] = {0, 0, 5};

    const float pi = 3.14159265f;
    
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

    //P1.print();
    //P2.print();
    //P3.print();

    Display display(320, 240);
    Frame frame(320, 240);

    drawLine(10+10*P1[0][0], 10+10*P1[1][0], 10+10*P2[0][0], 10+10*P2[1][0], frame);
    drawLine(10+10*P2[0][0], 10+10*P2[1][0], 10+10*P3[0][0], 10+10*P3[1][0], frame);
    drawLine(10+10*P3[0][0], 10+10*P3[1][0], 10+10*P1[0][0], 10+10*P1[1][0], frame);

    //drawLine(50, 10, 280, 100, frame);
    //drawLine(50, 10, 100, 220, frame);
    //drawLine(100, 220, 280, 100, frame);


    display.render(frame);

    sleep(2);
}
