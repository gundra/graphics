#ifndef GRAPHICSAPP_H
#define GRAPHICSAPP_H

#include "ApplicationBase.h"
#include "Vector3d.h"
#include "Matrix4x4.h"
#include "Rasterizer.h"
#include <vector>

class GraphicsApp: public ApplicationBase
{
    public:
        GraphicsApp(int w, int h);
        ~GraphicsApp();

        void init();
        void update(int elapsedTime);
        void draw(const Display& dis);

    private:
        std::vector<Vector3d> m_vertexes;
        Rasterizer m_rasterizer;
        Matrix4x4 m_modelMatrix; 
        Matrix4x4 m_viewMatrix; 
        Matrix4x4 m_projectionMatrix;
        Matrix4x4 m_finalMatrix;
};

#endif /* GRAPHICSAPP_H */
