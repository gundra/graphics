#include "Vector4d.h"

#include <math.h>

Vector4d::Vector4d()
    : m_x(0), m_y(0), m_z(0), m_w(0)
{
}

Vector4d::Vector4d(const Vector4d& rhs)
    : m_x(rhs.m_x), m_y(rhs.m_y), m_z(rhs.m_z), m_w(rhs.m_w)
{
}

Vector4d::Vector4d(float x, float y, float z, float w)
    : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

Vector4d::~Vector4d()
{
}

Vector4d& Vector4d::operator=(const Vector4d& rhs)
{
    if (this == &rhs)
        return *this;

    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;
    m_w = rhs.m_w;

    return *this;
}

float& Vector4d::operator[](const int rhs)
{
    switch(rhs)
    {
        case 0:
            return m_x;
        case 1:
            return m_y;
        case 2:
            return m_z;
        case 3:
            return m_w;
    }

    throw 0;
}

float Vector4d::operator[](const int rhs) const
{
    switch(rhs)
    {
        case 0:
            return m_x;
        case 1:
            return m_y;
        case 2:
            return m_z;
        case 3:
            return m_w;
    }

    throw 0;
}

Vector4d& Vector4d::operator*=(const float rhs)
{
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;
    m_w *= rhs;

    return *this;
}

float Vector4d::computeLength() const
{
    // leave w alone?
    
    return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector4d& Vector4d::normalize()
{
    float len = computeLength();

    if (len == 0)
        return *this;

    return (*this) *= (1.0f/computeLength());
}

Vector4d operator+(const Vector4d& lhs, const Vector4d& rhs)
{
    return Vector4d(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]);
}

Vector4d operator-(const Vector4d& lhs, const Vector4d& rhs)
{
    return Vector4d(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]);
}

Vector4d operator*(const Vector4d& lhs, const Vector4d& rhs)
{
    return Vector4d(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]);
}

std::ostream& operator << (std::ostream& lhs, const Vector4d& rhs)
{
    lhs << '(';

    for (int i=0; i<4; ++i)
        lhs << rhs[i] << (i==3 ? "" : " ");
            
    lhs << ')';

    return lhs;
}
