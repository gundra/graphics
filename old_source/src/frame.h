#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"

class Frame
{
    public:
        Frame(int w, int h);
        ~Frame();

        void setPixel(int x, int y, const Pixel& pixel);
        const Pixel& getPixel(int x, int y);

    private:
        Frame(const Frame&);
        Frame& operator=(const Frame&);

        int m_width;
        int m_height;
        Pixel* m_pixel;
};

#endif /* FRAME_H */
