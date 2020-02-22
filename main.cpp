#include <iostream>
#include <cmath>

using namespace std;

//Newton iteration:
//Find the square root of 'num' by starting the iteration from 'x0'
double sqrt_newton(double num, double x0)
{
    for (int i=0; i<=4; ++i)
    {
        double x1 = x0 - (x0*x0-num)/(2*x0);
        x0 = x1;
    }
    return x0;
}

//example function for integral:
double examplefunc(double x)
{
    return cos(x)*exp(-pow(x,2));
}

//numerical integration with Newton-Cotes (Trapezoidal) formula:
//integrate [x0,x1],
double integrate(int n, double x0, double x1)
{
    double h = (x1-x0)/n;
    double sum = 0;
    while (x0 < x1)
    {
        sum += h*0.5*(examplefunc(x0)+examplefunc(x0+h));
        x0 += h;
    }
    return sum;
}

int main()
{
    //some data to check accuracy;
    double root_of_612 = 24.738633753767;
    double integral_of_exfunc = 1.34638795680345037669816;

    //results:
    cout.precision(16);
    cout << "Square root of 612, from a starting point at 10:" << endl;
    cout << "Result: " << sqrt_newton(612,10) << "   accuracy: ~ "
    << abs(sqrt_newton(612,10)-root_of_612) << "\n" << endl;

    cout << "Numerical integral of the example function:" << endl;
    cout << "Result: " << integrate(9999,-1,3) << "   accuracy: ~ "
    << abs(integrate(999,-1,3)-integral_of_exfunc) << "\n\n" << endl;

    cout << "Convergence of the numerical integration:\n" << endl;
    int i = 1;
    while (i < 9999)
    {
        cout << "n: " << i << "     integral: " << integrate(i,-1,3)
        << "    accuracy: "<< abs(integrate(i,-1,3)-integral_of_exfunc) << endl;
        i += 999;
    }
    return 0;
}
