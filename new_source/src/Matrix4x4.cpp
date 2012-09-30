#include "Matrix4x4.h"

#include <assert.h>

Matrix4x4::Matrix4x4()
{
    for (int i=0; i<16; ++i)
        m_data[i] = 0;
}

Matrix4x4::Matrix4x4(const Matrix4x4& rhs)
{
    for (int i=0; i<16; ++i)
        m_data[i] = rhs.m_data[i];
}

Matrix4x4::Matrix4x4(const float* rhs)
{
    for (int i=0; i<16; ++i)
        m_data[i] = rhs[i];
}

Matrix4x4::Matrix4x4(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10, float v11, float v12, float v13, float v14, float v15, float v16)
{
    m_data[0] = v1;   m_data[1] = v2;   m_data[2] = v3;   m_data[3] = v4; 
    m_data[4] = v5;   m_data[5] = v6;   m_data[6] = v7;   m_data[7] = v8; 
    m_data[8] = v9;   m_data[9] = v10;  m_data[10] = v11; m_data[11] = v12; 
    m_data[12] = v13; m_data[13] = v14; m_data[14] = v15; m_data[15] = v16; 
}

Matrix4x4::~Matrix4x4()
{
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs)
{
    if (this == &rhs)
        return *this;

    for (int i=0; i<16; ++i)
        m_data[i] = rhs.m_data[i];

    return *this;
}

float& Matrix4x4::operator()(const int row, const int col)
{
    assert(row <= 4 && col <= 4);

    return m_data[4*row+col];
}

float Matrix4x4::operator()(const int row, const int col) const
{
    assert(row <= 4 && col <= 4);

    return m_data[4*row+col];
}

float& Matrix4x4::operator[](const int index)
{
    return m_data[index];
}

float Matrix4x4::operator[](const int index) const
{
    return m_data[index];
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
{
    static Matrix4x4 res;
    static float sum = 0;

    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            sum = 0;
            for (int k=0; k<4; k++)
                sum += (*this)(i,k) * rhs(k,j);

            res(i,j) = sum;
        }
    }

    *this = res;

    return *this;
}

Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
    Matrix4x4 res(lhs);
    
    return res *= rhs;
}

std::ostream& operator << (std::ostream& lhs, Matrix4x4 const& rhs)
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
            lhs << rhs(i,j)  << "\t";

        lhs << std::endl;
    }

    return lhs;
}
