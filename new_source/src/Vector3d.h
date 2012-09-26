#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3d
{
    public:
        Vector3d();
        Vector3d(const Vector3d& rhs);
        Vector3d(float c1, float v2, float c3);

        virtual ~Vector3d();

        Vector3d& operator=(const Vector3d& rhs);
        float& operator[](const int rhs);
        float operator[](const int rhs) const;

        Vector3d& operator*=(const float rhs);

        float computeLength() const;
        Vector3d& normalize();

    private:
        float m_x;
        float m_y;
        float m_z;
};

Vector3d operator+(const Vector3d& lhs, const Vector3d& rhs);
Vector3d operator-(const Vector3d& lhs, const Vector3d& rhs);
Vector3d operator*(const Vector3d& lhs, const Vector3d& rhs);

Vector3d Vector3dCrossProduct(const Vector3d& lhs, const Vector3d& rhs);

#include <iostream>

std::ostream& operator << (std::ostream& lhs, const Vector3d& rhs);

#endif /* VECTOR3D_H */
