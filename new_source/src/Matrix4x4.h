#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector4d.h"

class Matrix4x4
{
    public:
        Matrix4x4();
        Matrix4x4(const Matrix4x4& rhs);
        Matrix4x4(const float* rhs);
        Matrix4x4(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10, float v11, float v12, float v13, float v14, float v15, float v16);

        virtual ~Matrix4x4();

        Matrix4x4& operator=(const Matrix4x4& rhs);
        float& operator()(const int row, const int col);
        float operator()(const int row, const int col) const;
        float& operator[](const int index);
        float operator[](const int index) const;

        Matrix4x4& operator*=(const Matrix4x4& rhs);

    private:
        float m_data[16];
};

Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
Vector4d operator*(const Matrix4x4& matrix, const Vector4d& vector);

#include <iostream>
std::ostream& operator << (std::ostream& lhs, Matrix4x4 const& rhs);

#endif /* MATRIX4X4_H */
