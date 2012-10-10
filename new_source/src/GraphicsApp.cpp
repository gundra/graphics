#include "GraphicsApp.h"

#include "Vector4d.h"
#include "Display.h"
#include "Viewport.h"
#include <math.h>

std::vector<Vector3d> getVertexes()
{
    std::vector<Vector3d> vertexes;

    Vector3d v1(0.0, 0.0, 0.0);
    Vector3d v2(0.0, 0.0, 1.0);
    Vector3d v3(0.0, 1.0, 0.0);
    Vector3d v4(0.0, 1.0, 1.0);
    Vector3d v5(1.0, 0.0, 0.0);
    Vector3d v6(1.0, 0.0, 1.0);
    Vector3d v7(1.0, 1.0, 0.0);
    Vector3d v8(1.0, 1.0, 1.0);

    vertexes.push_back(v1);  vertexes.push_back(v7);  vertexes.push_back(v5);
    vertexes.push_back(v1);  vertexes.push_back(v3);  vertexes.push_back(v7); 
    vertexes.push_back(v1);  vertexes.push_back(v4);  vertexes.push_back(v3); 
    vertexes.push_back(v1);  vertexes.push_back(v2);  vertexes.push_back(v4); 
    vertexes.push_back(v3);  vertexes.push_back(v8);  vertexes.push_back(v7); 
    vertexes.push_back(v3);  vertexes.push_back(v4);  vertexes.push_back(v8); 
    vertexes.push_back(v5);  vertexes.push_back(v7);  vertexes.push_back(v8); 
    vertexes.push_back(v5);  vertexes.push_back(v8);  vertexes.push_back(v6); 
    vertexes.push_back(v1);  vertexes.push_back(v5);  vertexes.push_back(v6); 
    vertexes.push_back(v1);  vertexes.push_back(v6);  vertexes.push_back(v2); 
    vertexes.push_back(v2);  vertexes.push_back(v6);  vertexes.push_back(v8); 
    vertexes.push_back(v2);  vertexes.push_back(v8);  vertexes.push_back(v4); 

    return vertexes;
}

GraphicsApp::GraphicsApp(int w, int h)
    : ApplicationBase(w, h), m_vertexes(), m_rasterizer(getDisplay()), m_modelViewMatrix(), m_projectionMatrix(), m_finalMatrix()
{
}

GraphicsApp::~GraphicsApp()
{
    stop();
}

void GraphicsApp::init()
{
    m_vertexes = getVertexes();

    swLoadIdentity(m_modelViewMatrix);
    swLoadIdentity(m_projectionMatrix);

    //swPerspective(m_projectionMatrix, 30, (float)getDisplay().getWidth()/(float)getDisplay().getHeight(), 1, 10);
    swOrtho(m_projectionMatrix, -2, 2, -2, 2, -2, 2);
}

void GraphicsApp::update(int elapsedMicroseconds)
{
    static Vector3d eye(3,3,3);
    static Vector3d target(0,0,0);
    static Vector3d up(0,1,0);

    std::cerr << 1.0f/(elapsedMicroseconds/1000000.0f) << " fps" << std::endl;

    static float z = 0;
    z += (float)elapsedMicroseconds / (1000000.0f*1.0f);

    eye[0] = 1*cos(z);
    eye[1] = 1;
    eye[2] = 1*sin(z);

    swLoadIdentity(m_modelViewMatrix);
    swLookAt(m_modelViewMatrix, eye, target, up);

    swTranslate(m_modelViewMatrix, -0.5, 0, -0.5);

    m_finalMatrix = m_projectionMatrix * m_modelViewMatrix;
}

bool swIsFacing(const Point& a, const Point& b, const Point& c)
{
    Vector3d ab(b.x-a.x, b.y-a.y, b.z-a.z);
    Vector3d cb(b.x-c.x, b.y-c.y, b.z-c.z);
    Vector3d faceNormal = Vector3dCrossProduct(cb, ab);

    return faceNormal[2] > 0;
}

void GraphicsApp::draw(const Display& dis)
{
    dis.clear();

    for (size_t i=0; i<m_vertexes.size(); i+=3)
    {
        static Vector4d tmpVertex;

        static Point p1;
        static Point p2;
        static Point p3;

        tmpVertex = swClipCoordinates(m_finalMatrix, m_vertexes[i]);        
        swNormalizeDeviceCoordinates(tmpVertex);
        p1.x = tmpVertex[0]; p1.y = tmpVertex[1]; p1.z = tmpVertex[2];

        tmpVertex = swClipCoordinates(m_finalMatrix, m_vertexes[i+1]);        
        swNormalizeDeviceCoordinates(tmpVertex);
        p2.x = tmpVertex[0]; p2.y = tmpVertex[1]; p2.z = tmpVertex[2];

        tmpVertex = swClipCoordinates(m_finalMatrix, m_vertexes[i+2]);        
        swNormalizeDeviceCoordinates(tmpVertex);
        p3.x = tmpVertex[0]; p3.y = tmpVertex[1]; p3.z = tmpVertex[2];

        swViewport(0, 0, dis.getWidth(), dis.getHeight(), p1.x, p1.y);
        swViewport(0, 0, dis.getWidth(), dis.getHeight(), p2.x, p2.y);
        swViewport(0, 0, dis.getWidth(), dis.getHeight(), p3.x, p3.y);

        if(swIsFacing(p1, p2, p3))
        {
            m_rasterizer.rasterizeTriangleSolid(p1, p2, p3);
            m_rasterizer.rasterizeTriangleLines(p1, p2, p3);
        }
    }
}
