#include "GraphicsApp.h"

#include "Vector4d.h"
#include "Display.h"

#include <math.h>

void swTranslate(Matrix4x4& matrix, float x, float y, float z)
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

void swLookAt(Matrix4x4& matrix, const Vector3d& eye, const Vector3d& target, const Vector3d& upVector)
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

void swOrtho(Matrix4x4& matrix, float left, float right, float bottom, float top, float zNear, float zFar)
{
    matrix = Matrix4x4
        (
         2.0f/(right-left), 0.0f,              0.0f,                  -(right+left)/(right-left),
         0.0f,              2.0f/(top-bottom), 0.0f,                  -(top+bottom)/(top-bottom),
         0.0f,              0.0f,              -2.0f/(zFar-zNear),    -(zFar+zNear)/(zFar-zNear), 
         0.0f,              0.0f,              0.0f,                  1.0f
        );
}

void swPerspective(Matrix4x4& matrix, float fovy, float aspect, float zNear, float zFar)
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

void swViewport(const int xOffset, const int yOffset, const int width, const int height, int& x, int& y)
{
    x = (x + 1.0f) * (width/2.0f) + xOffset;
    y = (y + 1.0f) * (height/2.0f) + yOffset;
}

void swViewportf(const int xOffset, const int yOffset, const int width, const int height, float& x, float& y)
{
    x = (x + 1.0f) * (width/2.0f) + xOffset;
    y = (y + 1.0f) * (height/2.0f) + yOffset;
}

Vector4d operator*(Matrix4x4& matrix, Vector4d& vector)
{
    return Vector4d
        (
         matrix(0, 0) * vector[0] + matrix(0, 1) * vector[1] + matrix(0, 2) * vector[2] + matrix(0, 3) * vector[3],
         matrix(1, 0) * vector[0] + matrix(1, 1) * vector[1] + matrix(1, 2) * vector[2] + matrix(1, 3) * vector[3], 
         matrix(2, 0) * vector[0] + matrix(2, 1) * vector[1] + matrix(2, 2) * vector[2] + matrix(2, 3) * vector[3],
         matrix(3, 0) * vector[0] + matrix(3, 1) * vector[1] + matrix(3, 2) * vector[2] + matrix(3, 3) * vector[3]
        );
}

Vector4d operator*(Matrix4x4& matrix, Vector3d& vector)
{
    Vector4d res;
    res[0] = vector[0];
    res[1] = vector[1];
    res[2] = vector[2];
    res[3] = 1.0f;

    return matrix * res;
}

std::vector<Vector3d> getVertexes()
{
    std::vector<Vector3d> vertexes;

    // front
    vertexes.push_back(Vector3d(0,0,0));
    vertexes.push_back(Vector3d(1,0,0));
    vertexes.push_back(Vector3d(0,1,0));

    vertexes.push_back(Vector3d(1,0,0));
    vertexes.push_back(Vector3d(1,1,0));
    vertexes.push_back(Vector3d(0,1,0));

    // back
    vertexes.push_back(Vector3d(0,0,1));
    vertexes.push_back(Vector3d(1,0,1));
    vertexes.push_back(Vector3d(0,1,1));

    vertexes.push_back(Vector3d(1,0,1));
    vertexes.push_back(Vector3d(1,1,1));
    vertexes.push_back(Vector3d(0,1,1));

    // bottom
    vertexes.push_back(Vector3d(0,0,0));
    vertexes.push_back(Vector3d(1,0,0));
    vertexes.push_back(Vector3d(0,0,1));

    vertexes.push_back(Vector3d(1,0,1));
    vertexes.push_back(Vector3d(1,0,0));
    vertexes.push_back(Vector3d(0,0,1));

    // daaah...

    return vertexes;
}

GraphicsApp::GraphicsApp(int w, int h)
    : ApplicationBase(w, h), m_vertexes(), m_rasterizer(getDisplay()), m_modelMatrix(), m_viewMatrix(), m_projectionMatrix(), m_finalMatrix()
{
}

GraphicsApp::~GraphicsApp()
{
    stop();
}

void GraphicsApp::init()
{
    m_vertexes = getVertexes();

    float identityMatrix[16] = 
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    m_modelMatrix = Matrix4x4(identityMatrix); 
    m_viewMatrix = Matrix4x4(identityMatrix); 
    m_projectionMatrix = Matrix4x4(identityMatrix);

    //swPerspective(m_projectionMatrix, 30, (float)getDisplay().getWidth()/(float)getDisplay().getHeight(), 1, 10);
    swOrtho(m_projectionMatrix, -2, 2, -2, 2, -2, 2);
}

void GraphicsApp::update(int elapsedTime)
{
    static Vector3d eye(5,5,5);
    static Vector3d target(0,0,0);
    static Vector3d up(0,1,0);

    static float z = 0;
    z += (float)elapsedTime / (100000.0f*10.0f);

    eye[0] = 1*cos(z);
    eye[1] = 1;
    eye[2] = 1*sin(z);

    m_viewMatrix = Matrix4x4
        (
         1,0,0,0,
         0,1,0,0,
         0,0,1,0,
         0,0,0,1
        );

    swLookAt(m_viewMatrix, eye, target, up);

    m_finalMatrix = m_projectionMatrix * m_viewMatrix;
}

void GraphicsApp::draw(const Display& dis)
{
    dis.clear();

    for (size_t i=0; i<m_vertexes.size(); i+=3)
    {
        static Point p1;
        static Point p2;
        static Point p3;

        static Vector4d vertex;

        vertex = m_finalMatrix * m_vertexes[i];
        p1.x = vertex[0] / vertex[3];
        p1.y = vertex[1] / vertex[3];

        vertex = m_finalMatrix * m_vertexes[i+1];
        p2.x = vertex[0] / vertex[3];
        p2.y = vertex[1] / vertex[3];

        vertex = m_finalMatrix * m_vertexes[i+2];
        p3.x = vertex[0] / vertex[3];
        p3.y = vertex[1] / vertex[3];

        swViewportf(0,0,dis.getWidth(),dis.getHeight(),p1.x,p1.y);
        swViewportf(0,0,dis.getWidth(),dis.getHeight(),p2.x,p2.y);
        swViewportf(0,0,dis.getWidth(),dis.getHeight(),p3.x,p3.y);

        m_rasterizer.rasterizeTriangleSolid(p1, p2, p3);
        //m_rasterizer.rasterizeTriangleLines(p1, p2, p3);
    }
}
