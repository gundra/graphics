#include "Vector3d.h"

#include <math.h>

Vector3d::Vector3d()
    : m_x(0), m_y(0), m_z(0)
{
}

Vector3d::Vector3d(const Vector3d& rhs)
    : m_x(rhs.m_x), m_y(rhs.m_y), m_z(rhs.m_z)
{
}

Vector3d::Vector3d(float c1, float c2, float c3)
    : m_x(c1), m_y(c2), m_z(c3)
{
}

Vector3d::~Vector3d()
{
}

Vector3d& Vector3d::operator=(const Vector3d& rhs)
{
    if (this == &rhs)
        return *this;

    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;

    return *this;
}

float& Vector3d::operator[](const int rhs)
{
    return rhs == 0 ? m_x : (rhs == 1 ? m_y : m_z);
}

float Vector3d::operator[](const int rhs) const
{
    return rhs == 0 ? m_x : (rhs == 1 ? m_y : m_z);
}

Vector3d& Vector3d::operator*=(const float rhs)
{
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;

    return *this;
}

float Vector3d::computeLength() const
{
    return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector3d& Vector3d::normalize()
{
    float len = computeLength();

    if (len == 0)
        return *this;

    return (*this) *= (1.0f/len);
}

Vector3d operator+(const Vector3d& lhs, const Vector3d& rhs)
{
    return Vector3d(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs)
{
    return Vector3d(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

Vector3d operator*(const Vector3d& lhs, const Vector3d& rhs)
{
    return Vector3d(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

Vector3d Vector3dCrossProduct(const Vector3d& lhs, const Vector3d& rhs)
{
    return Vector3d(lhs[1] * rhs[2] - lhs[2] * rhs[1], 
            lhs[2] * rhs[0] - lhs[0] * rhs[2], 
            lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

std::ostream& operator << (std::ostream& lhs, const Vector3d& rhs)
{
    lhs << '(';

    for (int i=0; i<3; ++i)
        lhs << rhs[i] << (i==2 ? "" : " ");
            
    lhs << ')';

    return lhs;
}
