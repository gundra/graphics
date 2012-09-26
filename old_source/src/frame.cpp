#include "frame.h"

#include <assert.h>

Frame::Frame(int w, int h)
    : m_width(w), m_height(h), m_pixel(new Pixel[m_width * m_height])
{
}

Frame::~Frame()
{
    delete [] m_pixel;
}

void Frame::setPixel(int x, int y, const Pixel& pixel)
{
    assert(x >= 0 && y >= 0 &&  x < m_width && y < m_height);

    m_pixel[y * m_width + x] = pixel;
}

const Pixel& Frame::getPixel(int x, int y)
{
    return m_pixel[y * m_width + x];
}

