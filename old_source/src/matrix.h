#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using std::cerr;
using std::endl;

#include <assert.h>

template <class T> class Matrix
{
    public:
        Matrix(int r, int c)
            : m_r(r), m_c(c), m_matrix(new T[r * c])
        {
        }

        Matrix(int r, int c, const T* data)
            : m_r(r), m_c(c), m_matrix(new T[r * c])
        {
           memcpy(m_matrix, data, m_r * m_c * sizeof(T)); 
        }

        Matrix(const Matrix& rhs)
            : m_r(rhs.m_r), m_c(rhs.m_c), m_matrix(new T[m_r * m_c])
        {
           memcpy(m_matrix, rhs.m_matrix, m_r * m_c * sizeof(T)); 
        }

        Matrix& operator=(const Matrix& rhs)
        {
            m_r = rhs.m_r;
            m_c = rhs.m_c;
            memcpy(m_matrix, rhs.m_matrix, m_r * m_c * sizeof(T)); 

            return *this;
        }

        Matrix& operator=(const T* data)
        {
            memcpy(m_matrix, data, m_r * m_c * sizeof(T)); 
            return *this;
        }

        ~Matrix()
        {
            delete [] m_matrix;
        }

        T* operator[](int index)
        {
            return m_matrix + index * m_c;
        }

        Matrix operator*(Matrix& matrix)
        {
            assert(m_c == matrix.m_r);

            T sum = 0;
            Matrix<T> resultMatrix(m_r, matrix.m_c);

            for (int i=0; i<m_r; i++)
            {
                for (int j=0; j<matrix.m_c; j++)
                {
                    sum = 0;
                    for (int k=0; k<m_c; k++)
                        sum = sum + (*this)[i][k] * matrix[k][j];

                    resultMatrix[i][j] = sum;
                }
            }

            return resultMatrix;
        }

        Matrix operator-(Matrix& matrix)
        {
            Matrix<T> resultMatrix(m_r, m_c);

            for (int i=0; i<m_r; i++)
                for (int j=0; j<m_c; j++)
                    resultMatrix[i][j] = (*this)[i][j] - matrix[i][j];

            return resultMatrix;
        }

        void print(const char* str = 0)
        {
            if (str)
                cerr << str << endl;

            for (int i=0; i<m_r; i++)
            {
                for (int j=0; j<m_c; j++)
                    cerr << (*this)[i][j]  << "\t";

                cerr << endl;
            }
            cerr << endl;
        }

    private:
        int m_r;
        int m_c;
        T* m_matrix;
};

#endif /* MATRIX_H */
