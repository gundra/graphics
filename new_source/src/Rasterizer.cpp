#include "Rasterizer.h"

#include <math.h>

#define FLT_ERROR		1e-4

Rasterizer::Rasterizer(const Display& display)
    : m_display(display), scan(), scanline()
{
}
        
void Rasterizer::scanline32(Scanline *data) 
{
    float	invDeltaX;
    long	xe, xs;

    // apply top-left fill-convention to scanline

    xs = ceil(data->x[0]);
    xe = ceil(data->x[1]) - 1;

    if(xe < xs)
       return;

    // calculate slopes

    invDeltaX = data->x[1] - data->x[0];

    if(invDeltaX < FLT_ERROR) invDeltaX = 1.0f;
    else invDeltaX = 1.0f / invDeltaX; 

    // rasterize line
    
    for (int x=xs; x<=xe; ++x)
        m_display.putPixel(x, data->y, 0xFFFFFFFF); 
}

void Rasterizer::rasterizeTriangle(const Point& p1, const Point& p2, const Point& p3)
{
    Point	*sp[3], *temp;
    float	v1[2], v2[2], sub;
    long	yStart, yEnd;
    int		i;

    sp[0] = (Point*)&p1;
    sp[1] = (Point*)&p2;
    sp[2] = (Point*)&p3;

    // order in increasing y order

    if(sp[0]->y > sp[1]->y) 
    {
        temp	= sp[0];
        sp[0]	= sp[1];
        sp[1]	= temp;
    }

    if(sp[0]->y > sp[2]->y) 
    {
        temp	= sp[0];
        sp[0]	= sp[2];
        sp[2]	= temp;
    }

    if(sp[1]->y > sp[2]->y) 
    {
        temp	= sp[1];
        sp[1]	= sp[2];
        sp[2]	= temp;
    }

    // calculate delta y of the edges

    scan.invDeltaY[0] = sp[2]->y - sp[0]->y;

    if(scan.invDeltaY[0] < FLT_ERROR)
        return;

    scan.invDeltaY[1] = sp[1]->y - sp[0]->y;
    scan.invDeltaY[2] = sp[2]->y - sp[1]->y;

    scan.invDeltaY[0] = 1.0f / scan.invDeltaY[0];
    if(scan.invDeltaY[1] >= FLT_ERROR) scan.invDeltaY[1] = 1.0f / scan.invDeltaY[1];
    if(scan.invDeltaY[2] >= FLT_ERROR) scan.invDeltaY[2] = 1.0f / scan.invDeltaY[2];

    // find if the major edge is left or right aligned

    v1[0] = sp[0]->x - sp[2]->x;
    v1[1] = sp[0]->y - sp[2]->y;
    v2[0] = sp[1]->x - sp[0]->x;
    v2[1] = sp[1]->y - sp[0]->y;

    if(v1[0] * v2[1] - v1[1] * v2[0] > 0) scan.left = 0;
    else scan.left = 1;

    // calculate slopes for the major edge

    scan.slopeX[0]		= (sp[2]->x - sp[0]->x) * scan.invDeltaY[0];
    scan.x[0]			= sp[0]->x;

    // rasterize upper sub-triangle

    if(scan.invDeltaY[1] >= FLT_ERROR) 
    {
        // calculate slopes for top edge

        scan.slopeX[1]		= (sp[1]->x - sp[0]->x) * scan.invDeltaY[1];
        scan.x[1]			= sp[0]->x;

        yStart				= ceil(sp[0]->y);
        yEnd				= ceil(sp[1]->y) - 1;

        sub					= (float)yStart - sp[0]->y;

        scan.x[0]			+= scan.slopeX[0] * sub;
        scan.x[1]			+= scan.slopeX[1] * sub;		

        // rasterize the edge scanlines

        for(i = yStart; i <= yEnd; i++) 
        {
            scanline.y				= i;
            scanline.x[scan.left]	= scan.x[0];
            scanline.x[!scan.left]	= scan.x[1];

            // draw a scanline

            scanline32(&scanline);	

            scan.x[0]	+= scan.slopeX[0];
            scan.x[1]	+= scan.slopeX[1];
        }
    }

    // rasterize lower sub-triangle

    if(scan.invDeltaY[2] >= FLT_ERROR) 
    {
        // advance major edge attirubtes to middle point (if we have process the other edge)

        if(scan.invDeltaY[1] >= FLT_ERROR) 
        {
            float dy = sp[1]->y - sp[0]->y;
            scan.x[0] = sp[0]->x + scan.slopeX[0] * dy;
        }

        // calculate slopes for bottom edge

        scan.slopeX[1]		= (sp[2]->x - sp[1]->y) * scan.invDeltaY[2];
        scan.x[1]			= sp[1]->x;

        yStart				= ceil(sp[1]->y);
        yEnd				= ceil(sp[2]->y) - 1;

        sub					= (float)yStart - sp[1]->y;

        scan.x[0] 			+= scan.slopeX[0] * sub;
        scan.x[1] 			+= scan.slopeX[1] * sub;

        // rasterize the edge scanlines

        for(i = yStart; i <= yEnd; i++) 
        {
            scanline.y				= i;
            scanline.x[scan.left]	= scan.x[0];
            scanline.x[!scan.left]	= scan.x[1];

            // draw a scanline

            scanline32(&scanline);

            scan.x[0] += scan.slopeX[0];
            scan.x[1] += scan.slopeX[1];
        }
    }
}

static void drawLine(int x0, int y0, int x1, int y1, const Display& d)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1 ? 1 : -1);
    int sy = (y0 < y1 ? 1 : -1);
    int err = dx - dy;

    while (true)
    { 
        d.putPixel(x0,y0,0xFFFFFF);

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

void Rasterizer::rasterizeLines(const Point& p1, const Point& p2, const Point& p3)
{
    drawLine(p1.x,p1.y,p2.x,p2.y,m_display);
    drawLine(p2.x,p2.y,p3.x,p3.y,m_display);
    drawLine(p3.x,p3.y,p1.x,p1.y,m_display);
}
