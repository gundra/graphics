#ifndef GRAPHICSAPP_H
#define GRAPHICSAPP_H

#include "ApplicationBase.h"
#include "Vector3d.h"
#include "Rasterizer.h"
#include "ModelViewMatrix.h"
#include "ProjectionMatrix.h"
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
        ModelViewMatrix m_modelViewMatrix;
        ProjectionMatrix m_projectionMatrix;
        Matrix4x4 m_finalMatrix;
};

#endif /* GRAPHICSAPP_H */
