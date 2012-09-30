#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Display.h"
#include "Point.h"

class Rasterizer
{
    public:
        Rasterizer(const Display& display);

        void rasterizeTriangleSolid(const Point& p1, const Point& p2, const Point& p3);
        void rasterizeTriangleLines(const Point& p1, const Point& p2, const Point& p3);

    private:
        const Display& m_display;
};

#endif /* RASTERIZER_H */
