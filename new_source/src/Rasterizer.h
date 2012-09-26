#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Display.h"
#include "Point.h"

typedef struct 
{
    int		left;				// 0 if major edge is left, else 1
    float	invDeltaY[3],		// inversed edge delta y
            slopeX[2],			// x slope along the edges
            x[2];				// x coordinate
} ScanConvData;

typedef struct 
{
    long	y;					// y position of the scanline
    float	x[2];				// x start and end positions
} Scanline;

class Rasterizer
{
    public:
        Rasterizer(const Display& display);

        void rasterizeTriangle(const Point& p1, const Point& p2, const Point& p3);
        void rasterizeLines(const Point& p1, const Point& p2, const Point& p3);

    private:
        void scanline32(Scanline *data); 

        const Display& m_display;
        ScanConvData scan;
        Scanline scanline;
};

#endif /* RASTERIZER_H */
