#include "Rasterizer.h"

#include <math.h>

Rasterizer::Rasterizer(const Display& display)
    : m_display(display)
{
}

// =============== Chris Hecker RASTERIZER ===============

#define FLT_ERROR 1e-4

typedef struct {
    union {
        struct {
            float r, g, b, a;
        };
        float rgba[4];
    };
} RGBA_F;

typedef struct {
    int		left;				// 0 if major edge is left, else 1
    float	invDeltaY[3],		// inversed edge delta y
            slopeX[2],			// x slope along the edges
            x[2];				// x coordinate
    RGBA_F	slopeC[2],			// color slope
            c[2];				// color values
} ScanConvData;

ScanConvData scan;

typedef struct {
    long	y;					// y position of the scanline
    float	x[2];				// x start and end positions
    RGBA_F	c[2];				// r, g, b, a color start and end positions
} Scanline;

Scanline scanline;
#define COPY_RGBA(dst, src) {			\
    dst.r = src.r;						\
    dst.g = src.g;						\
    dst.b = src.b;						\
    dst.a = src.a;						\
}

static void scanline32(Scanline *data, const Display& dis) {
    float	invDeltaX,
            sub;
    RGBA_F	slopeC;
    long	xe, xs;
    int		i;

    // we cannot render without a frame buffer, aight ?

    // apply top-left fill-convention to scanline

    xs = ceil(data->x[0]);
    xe = ceil(data->x[1]) - 1;

    if(xe < xs)
        return;

    // calculate slopes

    invDeltaX = data->x[1] - data->x[0];

    if(invDeltaX < FLT_ERROR) invDeltaX = 1.0f;
    else invDeltaX = 1.0f / invDeltaX;

    sub = (float)xs - data->x[0];

    slopeC.r = (data->c[1].r - data->c[0].r) * invDeltaX;
    slopeC.g = (data->c[1].g - data->c[0].g) * invDeltaX;
    slopeC.b = (data->c[1].b - data->c[0].b) * invDeltaX;

    data->c[0].r += slopeC.r * sub;
    data->c[0].g += slopeC.g * sub;
    data->c[0].b += slopeC.b * sub;

    // get pointer to frame buffer's bits

    ///bitsFrame = (dword*)frameBuffer + data->y *frameBufferPitch + xs;
    for (int i=xs;i<=xe;++i)
        dis.putPixel(i, data->y, 0xFFFFFFFF);

    // rasterize line

}

static void rasterizeTriangle(const Point *p1, const Point *p2, const Point *p3, const Display& dis) {
    Point	*sp[3], *temp;
    float	v1[2], v2[2], sub;
    long	yStart, yEnd;
    int		i;

    sp[0] = (Point*)p1;
    sp[1] = (Point*)p2;
    sp[2] = (Point*)p3;

    // order in increasing y order

    if(sp[0]->y > sp[1]->y) {
        temp	= sp[0];
        sp[0]	= sp[1];
        sp[1]	= temp;
    }
    if(sp[0]->y > sp[2]->y) {
        temp	= sp[0];
        sp[0]	= sp[2];
        sp[2]	= temp;
    }
    if(sp[1]->y > sp[2]->y) {
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

    if(scan.invDeltaY[1] >= FLT_ERROR) {

        // calculate slopes for top edge

        scan.slopeX[1]		= (sp[1]->x - sp[0]->x) * scan.invDeltaY[1];
        scan.x[1]			= sp[0]->x;

        yStart				= ceil(sp[0]->y);
        yEnd				= ceil(sp[1]->y) - 1;

        sub					= (float)yStart - sp[0]->y;

        scan.x[0]			+= scan.slopeX[0] * sub;

        scan.c[0].r			+= scan.slopeC[0].r * sub;
        scan.c[0].g			+= scan.slopeC[0].g * sub;
        scan.c[0].b			+= scan.slopeC[0].b * sub;

        scan.x[1]			+= scan.slopeX[1] * sub;

        scan.c[1].r			+= scan.slopeC[1].r * sub;
        scan.c[1].g			+= scan.slopeC[1].g * sub;
        scan.c[1].b			+= scan.slopeC[1].b * sub;

        // rasterize the edge scanlines

        for(i = yStart; i <= yEnd; i++) {
            scanline.y				= i;
            scanline.x[scan.left]	= scan.x[0];
            scanline.x[!scan.left]	= scan.x[1];
            COPY_RGBA(scanline.c[scan.left], scan.c[0]);
            COPY_RGBA(scanline.c[!scan.left], scan.c[1]);

            // draw a scanline

            scanline32(&scanline, dis);

            scan.x[0]	+= scan.slopeX[0];
            scan.c[0].r += scan.slopeC[0].r;
            scan.c[0].g += scan.slopeC[0].g;
            scan.c[0].b += scan.slopeC[0].b;

            scan.x[1]	+= scan.slopeX[1];
            scan.c[1].r += scan.slopeC[1].r;
            scan.c[1].g += scan.slopeC[1].g;
            scan.c[1].b += scan.slopeC[1].b;
        }
    }

    // rasterize lower sub-triangle

    if(scan.invDeltaY[2] >= FLT_ERROR) {

        // advance major edge attirubtes to middle point (if we have process the other edge)

        if(scan.invDeltaY[1] >= FLT_ERROR) {
            float dy = sp[1]->y - sp[0]->y;
            scan.x[0] = sp[0]->x + scan.slopeX[0] * dy;
        }

        // calculate slopes for bottom edge

        scan.slopeX[1]		= (sp[2]->x - sp[1]->x) * scan.invDeltaY[2];
        scan.x[1]			= sp[1]->x;

        yStart				= ceil(sp[1]->y);
        yEnd				= ceil(sp[2]->y) - 1;

        sub					= (float)yStart - sp[1]->y;

        scan.x[0] 			+= scan.slopeX[0] * sub;

        scan.c[0].r			+= scan.slopeC[0].r * sub;
        scan.c[0].g			+= scan.slopeC[0].g * sub;
        scan.c[0].b			+= scan.slopeC[0].b * sub;

        scan.x[1] 			+= scan.slopeX[1] * sub;

        scan.c[1].r			+= scan.slopeC[1].r * sub;
        scan.c[1].g			+= scan.slopeC[1].g * sub;
        scan.c[1].b			+= scan.slopeC[1].b * sub;

        // rasterize the edge scanlines

        for(i = yStart; i <= yEnd; i++) {
            scanline.y				= i;
            scanline.x[scan.left]	= scan.x[0];
            scanline.x[!scan.left]	= scan.x[1];
            COPY_RGBA(scanline.c[scan.left], scan.c[0]);
            COPY_RGBA(scanline.c[!scan.left], scan.c[1]);

            // draw a scanline

            scanline32(&scanline, dis);

            scan.x[0] += scan.slopeX[0];

            scan.c[0].r += scan.slopeC[0].r;
            scan.c[0].g += scan.slopeC[0].g;
            scan.c[0].b += scan.slopeC[0].b;

            scan.x[1] += scan.slopeX[1];

            scan.c[1].r += scan.slopeC[1].r;
            scan.c[1].g += scan.slopeC[1].g;
            scan.c[1].b += scan.slopeC[1].b;
        }
    }
}

// =============== End of C hris Hecker RASTERIZER ===============

void Rasterizer::rasterizeTriangleSolid(const Point& p1, const Point& p2, const Point& p3)
{
    rasterizeTriangle(&p1, &p2, &p3, m_display);
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
        d.putPixel(x0,y0,0xFF777777);

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

void Rasterizer::rasterizeTriangleLines(const Point& p1, const Point& p2, const Point& p3)
{
    drawLine(p1.x,p1.y,p2.x,p2.y,m_display);
    drawLine(p2.x,p2.y,p3.x,p3.y,m_display);
    drawLine(p3.x,p3.y,p1.x,p1.y,m_display);
}
