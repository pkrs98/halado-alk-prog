#ifndef HEADER2_H_INCLUDED
#define HEADER2_H_INCLUDED

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

//Large Matrix class:
template<typename T>
struct Matrix
{
    int n;
	std::vector<std::vector<T>> data;

	//Subscript operator for reading and writing:
	T&       operator()( int i, int j )       { return data[i][j]; }
	T const& operator()( int i, int j ) const { return data[i][j]; }

	//Function call operator for reading and writing:
	T&       operator[]( int i )       {
	    int y = i/n;
	    int x = i%n;
	    return &data[x][y];
	    }
	T const& operator[]( int i ) const {
        int y = i/n;
	    int x = i%n;
	    return data[x][y];
	    }

	//Default, Copy and Move constructors implemented by the compiler:
	Matrix() = default;
	Matrix( Matrix const& ) = default;
	Matrix( Matrix && ) = default;

	//Copy and Move assignment operators implemented by the compiler:
	Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix &&) = default;

	//Construct from function by passing indices from 0 to n-1:
	template<typename F>
	Matrix(F f, int N):n(N)
	{
	    data.resize(n);
	    for(int i=0; i<n; ++i){ data[i].resize(n); }
		//for(int i=0; i<n; ++i){ data[i] = f(i); }
	}

	template<typename K>
	Matrix(K* t, int N):n(N)
	{
	    data.resize(n);
	    for(int i=0; i<n; i++){ data[i].resize(n); }
	    for(int i=0; i<n*n; i++)
        {
            int y = i/n;
            int x = i%n;
            data[x][y] = t[i];
        }
	}

	int getSize()
	{
	    return n*n;
	}

	int getN()
	{
	    return n;
	}

	//Add assignment operators:
	Matrix<T> operator+= (Matrix<T> const& cpy)
	{
	    if (n != cpy.getN())
		return *this;
		else
        {
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j < n; j++)
                    {
                        data[i][j] += cpy(i,j);
                    }
            }
            return *this;
        }
	}

	Matrix<T> operator+= (T const& s)
	{
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j < n; j++)
                {
                    data[i][j] += s;
                }
        }
        return *this;
    }

	//Subtract assignment operators:
	Matrix<T> operator-= (Matrix<T> const& cpy)
	{
        if (n != cpy.getN())
		return *this;
		else
        {
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    data[i][j] -= cpy(i,j);
                }
            }
            return *this;
        }
	}

	Matrix<T> operator-= (T const& s)
	{
	    for(int i = 0; i<n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    data[i][j] -= s;
                }
            }
            return *this;
	}

	//Multiplication by scalar:
	Matrix<T> operator*= (T const& s)
	{
	    for(int i = 0; i<n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                data[i][j] *= s;
            }
        }
        return *this;
	}

	Matrix<T> operator*= (Matrix<T> const& m)
	{
	    Matrix<T> a(this->n);
        if (n != m.getN())
        {
            std::cout<<"\nmeret nem jo";
            return *this;
        }
        else
        {
            for (int i=0; i<n; i++)
            {
                for (int j=0; j<n; j++)
                {
                    for (int k=0; k<n; k++)
                    {
                         a.data[i][j] += data[i][k]*m(k,j);
                         //std::cout<<"\n"<<i<<" "<<j<<" "<<k<<" "<<a.data[i][j]<<" "<<data[i][k]<<" "<<m(k,j);
                    }
                }
            }
        }
        *this = a;
        return *this;
	}

	//Division by scalar:
	Matrix<T> operator/= (T const& s)
	{
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                data[i][j] /= s;
            }
        }
        return *this;
	}
    /*
	//&&:
	//Add assignment operators:
	Matrix<T>&& operator+= (Matrix<T> const&& cpy)
	{
	    if (n != cpy.getN())
		return this;
		else
        {
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j < n; j++)
                    {
                        data[i][j] += cpy(i,j);
                    }
            }
            return this;
        }
	}

	//Subtract assignment operators:
	Matrix<T>&& operator-= (Matrix<T> const&& cpy)
	{
        if (n != cpy.getN())
		return this;
		else
        {
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    data[i][j] -= cpy(i,j);
                }
            }
            return this;
        }
	}

	//Multiplication by scalar:
	Matrix<T>&& operator*= (T const&& s)
	{
	    for(int i = 0; i<n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                data[i][j] *= s;
            }
        }
        return this;
	}

	//Division by scalar:
	Matrix<T>&& operator/= (T const&& s)
	{
	    Matrix<T> a(this->n);
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                a.data[i][j] = a.data[i][j]/s;
            }
        }
        return &&a;
	}
    */

	Matrix<T> (int N)
	{
	    n=N;
        data.resize(n);
	    for(int i=0; i<n; i++){ data[i].resize(n); }
	}

	bool operator== (Matrix<T> const& m)
	{
	    for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (data[i][j] != m(i,j))
                {
                    return false;
                }
            }
        }
        return true;
	}

	void print()
	{
	    std::cout << "\n------------------";
	    for (int i=0; i<n; i++)
        {
            std::cout << "\n";
            for (int j=0; j<n; j++)
            {
                std::cout << " " << (float)data[i][j];
            }
        }
	}

};


//ADDITION OF TWO MATRICES:
template<typename T>
Matrix<T> operator+ (Matrix<T> const& m1, Matrix<T> const& m2)
{
    Matrix<T> a;
    if (m1.getN() != m2.getN())
    {
        return a;
    }
    else
    {
        int n = m1.getN();
        a = Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                a.data[i][j] = m1(i,j)+m2(i,j);
            }
        }
    }
    return a;
}

//ADDITION OF MATRIX AND SCALAR:
template<typename T>
Matrix<T> operator+ (Matrix<T> const& m, T const& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)+s;
            //std::cout<<"\n"<<i<<" "<<j<<" "<<a.data[i][j]<<" "<<m(i,j)<<" "<<s;
        }
    }
    return a;
}

template<typename T>
Matrix<T> operator+ (Matrix<T>& m, T const& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)+s;
            //std::cout<<"\n"<<i<<" "<<j<<" "<<a.data[i][j]<<" "<<m(i,j)<<" "<<s;
        }
    }
    return a;
}

template<typename T>
Matrix<T> operator+ (Matrix<T> const& m, T& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)+s;
            //std::cout<<"\n"<<i<<" "<<j<<" "<<a.data[i][j]<<" "<<m(i,j)<<" "<<s;
        }
    }
    return a;
}

template<typename T>
Matrix<T> operator+ (Matrix<T>& m, T& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)+s;
            //std::cout<<"\n"<<i<<" "<<j<<" "<<a.data[i][j]<<" "<<m(i,j)<<" "<<s;
        }
    }
    return a;
}

//SUBTRACTION OF TWO MATRICES:
template<typename T>
Matrix<T> operator- (Matrix<T> const& m1, Matrix<T> const& m2)
{
    Matrix<T> a;
    if (m1.getN() != m2.getN())
    {
        return a;
    }
    else
    {
        int n = m1.getN();
        a = Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                a.data[i][j] = m1(i,j)-m2(i,j);
            }
        }
    }
    return a;
}

//SUBTRACTION OF MATRIX BY SCALAR:
template<typename T>
Matrix<T> operator- (Matrix<T> const& m, T const& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)-s;
        }
    }
    return a;
}

template<typename T>
Matrix<T> operator- (Matrix<T>& m, T const& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)-s;
        }
    }
    return a;
}

template<typename T>
Matrix<T> operator- (Matrix<T> const& m, T& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)-s;
        }
    }
    return a;
}

template<typename T>
Matrix<T> operator- (Matrix<T>& m, T& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)-s;
        }
    }
    return a;
}

//MULTIPLICATION OF TWO MATRICES:
template<typename T>
Matrix<T> operator* (Matrix<T> const& m1, Matrix<T> const& m2)
{
    Matrix<T> a;
    if (m1.getN() != m2.getN())
    {
        return a;
    }
    else
    {
        int n = m1.getN();
        a=Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                for (int k=0; k<n; k++)
                {
                    a.data[i][j] += m1(i,k)*m2(k,j);
                }
            }
        }
    }
    return a;
}

//MULTIPLICATION OF MATRIX BY SCALAR (s*M):
template<typename T>
Matrix<T> operator* (T const& s, Matrix<T> const& m)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)*s;
        }
    }
    return a;
}

//DIVISION OF MATRIX BY SCALAR:
template<typename T>
Matrix<T> operator/ (Matrix<T> const& m, T const& s)
{
    Matrix<T> a;
    if (s == 0)
    {
        return a;
    }
    else
    {
        int n = m.getN();
        a=Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                a.data[i][j] = m(i,j)/s;
            }
        }
    }
    return a;
}

//&&:

//ADDITION OF TWO MATRICES:
template<typename T>
Matrix<T>&& operator+ (Matrix<T> const&& m1, Matrix<T> const&& m2)
{
    Matrix<T> a;
    if (m1.getN() != m2.getN())
    {
        return a;
    }
    else
    {
        int n = m1.getN();
        a=Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                a.data[i][j] = m1(i,j)+m2(i,j);
            }
        }
    }
    return a;
}

//ADDITION OF MATRIX AND SCALAR:
template<typename T>
Matrix<T>&& operator+ (Matrix<T> const&& m, T const&& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)+s;
        }
    }
    return a;
}

//SUBTRACTION OF TWO MATRICES:
template<typename T>
Matrix<T>&& operator- (Matrix<T> const&& m1, Matrix<T> const&& m2)
{
    Matrix<T> a;
    if (m1.getN() != m2.getN())
    {
        return a;
    }
    else
    {
        int n = m1.getN();
        a=Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                a.data[i][j] = m1(i,j)-m2(i,j);
            }
        }
    }
    return a;
}

//SUBTRACTION OF MATRIX BY SCALAR:
template<typename T>
Matrix<T>&& operator- (Matrix<T> const&& m, T const&& s)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)-s;
        }
    }
    return a;
}

//MULTIPLICATION OF TWO MATRICES:
template<typename T>
Matrix<T>&& operator* (Matrix<T> const&& m1, Matrix<T> const&& m2)
{
    Matrix<T> a;
    if (m1.getN() != m2.getN())
    {
        return a;
    }
    else
    {
        int n = m1.getN();
        a = Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                for (int k=0; k<n; k++)
                {
                    a.data[i][j] += m1(i,k)*m2(k,j);
                }
            }
        }
    }
    return a;
}

//MULTIPLICATION OF MATRIX BY SCALAR (s*M):
template<typename T>
Matrix<T>&& operator* (T const&& s, Matrix<T> const&& m)
{
    int n = m.getN();
    Matrix<T> a(n);
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a.data[i][j] = m(i,j)*s;
        }
    }
    return a;
}

//DIVISION OF MATRIX BY SCALAR:
template<typename T>
Matrix<T> operator/ (Matrix<T> const&& m, T const&& s)
{
    Matrix<T> a;
    if (s == 0)
    {
        return a;
    }
    else
    {
        int n = m.getN();
        a = Matrix<T>(n);
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                a.data[i][j] = m(i,j)/s;
            }
        }
    }
    return a;
}

#endif // HEADER2_H_INCLUDED
