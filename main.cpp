#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

//Newton iteracio tamplate-ekkel :
template<typename F, typename G, typename T>
T newton(F f1, G f2, T x0)
{
    for (int i = 0; i<5; ++i)
    {
        double x1 = x0 - f1(x0)/f2(x0);
        x0 = x1;
    }
    return x0;
}

//egyenes illesztes :
array<double,2> illesztes(vector<double> const& X, vector<double> const& Y)
{
    if (X.size() != Y.size())
    {
        cout << "\nERROR: the lengths of the vectors do not match\n" << endl;
    }
    const int n = static_cast<int>(X.size());   //megadott vektorok hossza
    double X_atlag = accumulate(X.begin(), X.end(), 0.0)/n;     //sum X
    double Y_atlag = accumulate(Y.begin(), Y.end(), 0.0)/n;     //sum Y

    double* M = new double [n];
    double* K = new double [n];

    for (int i = 0; i < n; i++)
    {
        M[i] = (X[i]-X_atlag)*(Y[i]-Y_atlag);
        K[i] = pow(X[i]-X_atlag,2);
    }
    double meredekseg = 0.0;
    double szamlalo = 0.0;
    double nevezo = 0.0;
    for (int i = 0; i < n; i++)
    {
        szamlalo += M[i];
        nevezo += K[i];
    }
    if (nevezo == 0.0)
    {
        cout << "\nERROR: division by zero\n" << endl;
        meredekseg = 0;
    }
    else
    {
        meredekseg = (double)szamlalo/nevezo;
    }
    double tengely = Y_atlag-(meredekseg*X_atlag);
    array<double,2> A = {meredekseg,tengely};
    delete[] M;
    delete[] K;
    return A;
}

//R^2 :
double Rnegyzet(vector<double> &X, vector<double> &Y)
{
    if (X.size() != Y.size())
    {
        cout << "\nERROR: the lengths of the vectors do not match\n" << endl;
    }
    const int n = static_cast<int>(X.size());   //megadott vektorok hossza
    double X_atlag = accumulate(X.begin(), X.end(), 0.0)/n;     //sum X
    double Y_atlag = accumulate(Y.begin(), Y.end(), 0.0)/n;     //sum Y
    double* L = new double [n];     // x*y atlaghoz

    // x*y atlag :
    double szorzatok = 0.0;
    for (int i = 0; i < n; i++)
    {
        L[i] = X[i]*Y[i];
        szorzatok += L[i];
    }
    double XY_atlag = szorzatok/n;

    // x^2 atlag �s y^2 atlag :
    double X2_atlag = accumulate(X.begin(), X.end(), 0.0, [](double a, double b){return a+(b*b); })/n;
    double Y2_atlag = accumulate(Y.begin(), Y.end(), 0.0, [](double a, double b){return a+(b*b); })/n;

    double Rnegyzet_szamlalo = XY_atlag-(X_atlag*Y_atlag);
    double Rnegyzet_nevezo = sqrt(abs( (X2_atlag-pow(X_atlag,2))*(Y2_atlag-pow(Y2_atlag,2))));
    double R2 = (double)Rnegyzet_szamlalo/Rnegyzet_nevezo;

    return 1-pow(R2,2);
}

int main()
{
    double a = 24.738633753705963298928;    //gyok 612 kozelito erteke
    //vektorok illeszteshez:
    vector<double> F = {4.905, 9.81, 14.715, 19.62, 29.43, 34.335, 39.24};
    vector<double> s = {0.17, 0.35, 0.52, 0.69, 1.07, 1.25, 1.43};

    cout.precision(16);
    double w = newton([](double x){return x*x - 612.0;},[](double x){return 2.0*x;}, 10.0);
    cout << "\nNewton iteracio tesztelese:\n" << w << endl;
    cout << "\nElteres a megadott ertektol: ~ " << abs(w-a) << endl;
    cout << "\n\nEgyenes illesztes tesztelese:\n" << endl;
    array<double,2> A = illesztes(F,s);
    cout << "meredekseg: " << A[0] << " tengelymetszet: " << A[1] << endl;
    cout << "R^2: " << Rnegyzet(F,s) << endl;
    return 0;
}
