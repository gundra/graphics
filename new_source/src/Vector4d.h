#ifndef VECTOR4D_H
#define VECTOR4D_H

class Vector4d
{
    public:
        Vector4d();
        Vector4d(const Vector4d& rhs);
        Vector4d(float x, float y, float z, float w);

        virtual ~Vector4d();

        Vector4d& operator=(const Vector4d& rhs);
        float& operator[](const int rhs);
        float operator[](const int rhs) const;

        Vector4d& operator*=(const float rhs);
        Vector4d& operator/=(const float rhs);

        float computeLength() const;
        Vector4d& normalize();

    private:
        float m_data[4];
        float m_x;
        float m_y;
        float m_z;
        float m_w;
};

Vector4d operator+(const Vector4d& lhs, const Vector4d& rhs);
Vector4d operator-(const Vector4d& lhs, const Vector4d& rhs);
Vector4d operator*(const Vector4d& lhs, const Vector4d& rhs);

#include <iostream>

std::ostream& operator << (std::ostream& lhs, const Vector4d& rhs);

#endif /* VECTOR4D_H */
