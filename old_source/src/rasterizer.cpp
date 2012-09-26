#include "rasterizer.h"

static int abs(int value)
{
    return (value < 0 ? -value : value);
}

void drawLine(int x0, int y0, int x1, int y1, Frame& frame)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1 ? 1 : -1);
    int sy = (y0 < y1 ? 1 : -1);
    int err = dx - dy;

    while (true)
    { 
        frame.setPixel(x0,y0,Pixel(255,255,255));

        if (x0 == x1 && y0 == y1) 
            break;

        int e2 = 2*err;
        if (e2 > -dy)
        { 
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 <  dx)
        { 
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}
