#include "pixel.h"

Pixel::Pixel(int r, int g, int b)
	: m_R(r), m_G(g), m_B(b), m_A(0)
{
}

Pixel::Pixel(const Pixel& pixel)
	: m_R(pixel.m_R), m_G(pixel.m_G), m_B(pixel.m_B), m_A(0)
{
}

Pixel& Pixel::operator=(const Pixel& pixel)
{
    if (this != &pixel)
    {
        m_R = pixel.m_R;
        m_G = pixel.m_G;
        m_B = pixel.m_B;
        m_A = 0;
    }

    return *this;
}

uint32_t Pixel::toInt32() const
{
    return (m_A << 24) | (m_R << 16) | (m_G << 8) | m_B;
}


