#include <iostream>
#include <cmath>
using namespace std;

template<typename T>
struct vector2d
{
    T x, y;

    vector2d<T>& operator+=(vector2d<T> const& v)
    { x += v.x; y += v.y;
    return *this;
    }

    vector2d<T>& operator-=(vector2d<T> const& v)
    {
        x -= v.x; y -= v.y;
        return *this;
    }

    vector2d<T>& operator*=(T const& a)
    {
        x *= a; y *= a;
        return *this;
    }

    vector2d<T>& operator/=(T const& a)
    {
        x /= a; y /= a;
        return *this;
    }

};

template<typename T>
ostream& operator<<(ostream& o, const vector2d<T>& v)
{
    o << v.x << " " << v.y;
    return o;
}

template<typename T>
istream& operator>>(istream& i, vector2d<T>& v)
{
    i >> v.x;
    i >> v.y;
    return i;
}

// 2 vektor osszeadasa:
template<typename T>
vector2d<T> operator+(vector2d<T> const& v1, vector2d<T> const& v2)
{
    return {v1.x + v2.x, v1.y + v2.y};
}

// 2 vektor kivonasa:
template<typename T>
vector2d<T> operator-(vector2d<T> const& v1, vector2d<T> const& v2)
{
    return { v1.x - v2.x, v1.y - v2.y };
}

// vektor szorzasa skalar szammal egyik oldalrol:
template<typename T>
vector2d<T> operator*(T const& a, vector2d<T> const& v)
{
    return { a*v.x, a*v.y };
}

// vektor szorzasa skalar szammal masik oldalrol:
template<typename T>
vector2d<T> operator*(vector2d<T> const& v, T const& a)
{
    return { a*v.x, a*v.y };
}

// vektor osztasa skalar szammal:
template<typename T>
vector2d<T> operator/(vector2d<T> const& v, T const& a)
{
    return { v.x/a, v.y/a };
}

// vektorok kereszt szorzata :
template<typename T>
T cross_product(vector2d<T> const& v1, vector2d<T> const& v2)
{
    return v1.y*v2.x - v1.x*v2.y;
}

// vektorok skalaris szorzata :
template<typename T>
T dot(vector2d<T> const& v1, vector2d<T> const& v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

// vektor hossza :
template<typename T>
T length(vector2d<T> const& v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

// 2 vektor altal kozbezart szog :
template<typename T>
T angle(vector2d<T> const& v1, vector2d<T> const& v2)
{
    T b = dot(v1,v2)/(length(v1)*length(v2));
    return acos(b);
}

// vektor hosszanak negyzete :
template<typename T>
T sqlength(vector2d<T> const& v)
{
    return v.x*v.x + v.y*v.y;
}

// vektor lenormalasa :
template<typename T>
vector2d<T> normalize(vector2d<T> const& v)
{
    return { v.x/sqrt(v.x*v.x+v.y*v.y), v.y/sqrt(v.x*v.x+v.y*v.y) };
}

int main()
{
    // teszteles :
    cout << "\nA kulonbozo vektormuveletek tesztelesehez adjon meg adatokat!" << endl;
    cout << "\nAdja meg az 1. vektor elemeit:" << endl;
    vector2d<double> v1{};
    cin >> v1;

    cout << "\nAdja meg a 2. vektor elemeit:" << endl;
    vector2d<double> v2{};
    cin >> v2;

    cout << "\nAdjon meg egy skalar erteket:" << endl;
    double a;
    cin >> a;

    cout << "\nAz On altal megadott adatok:\nv1 = " << v1 << "\nv2 = " << v2 << "\na = " << a << endl;

    cout << "\nVEKTOROK OSSZEADASA:         v1 + v2 = " << v1+v2;
    cout << "\nVEKTOROK KIVONASA:           v1 - v2 = " << v1-v2;
    cout << "\nVEKTOR SKALARRAL SZORZASA:   a * v1 = " << a*v1;
    cout << "\nVEKTOR SKALARRAL OSZTASA:    v1 / a = " << v1/a;
    cout << "\nVEKTOROK SKALAR SZORZATA:    v1 * v2 = " << dot(v1,v2);
    cout << "\nVEKTOROK KERESZT-SZORZATA:   v1 x v2 = " << cross_product(v1,v2);
    cout << "\nVEKTOROK KOZBEZART SZOGE:    w(v1,v2) = " << angle(v1,v2);
    cout << "\nVEKTOR HOSSZA:               v1_length = " << length(v1);
    cout << "\nVEKTOR LENORMALASA:          v1_n = " << normalize(v1) << endl;

    return 0;
}
