#include <iostream>
#include "matrix.h"

using namespace std;

//matrices for testing:
int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
int B[] = {2, 10, 5, 4, 20, 0, 4, 3, 54, 23, 10, 3, 97, 4, 18, 6};
// A+B:
int A_plus_B[] = {3, 12, 8, 8, 25, 6, 11, 11, 63, 33, 21, 15, 110, 18, 33, 22};
// A-B:
int A_minus_B[] = {-1, -8, -2, 0, -15, 6, 3, 5, -45, -13, 1, 9, -84, 10, -3, 10};
// A+1:
int A_plus_1[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
//A-1:
int A_minus_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
//A*B:
int A_mul_B[] = {149, 170, 191, 212, 95, 122, 149, 176, 298, 388, 478, 568, 357, 482, 607, 732};
// 2*A:
int A_mul_2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
// A/2:
int A_div_2[] ={0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8};


int main()
{
    //example matrices:
    //std::cout<<"\nkonstr 1"<<std::endl;
    Matrix<int> m1(&A[0], 4);
    //std::cout<<"\nkonstr 2"<<std::endl;
    Matrix<int> m2(&B[0], 4);

    //operation testing:
    //std::cout<<"\ntest1";
    Matrix<int> test1;
    test1 = m1+m2;
    //std::cout<<"\ntest2";
    Matrix<int> test2;
    test2 = m1-m2;
    //std::cout<<"\ntest3";
    Matrix<int> test3;
    test3 = m1/2;
    //std::cout<<"\ntest4";
    Matrix<int> test4;
    test4 = 2*m1;
    //std::cout<<"\ntest5";
    Matrix<int> test5;
    test5 = m1*m2;
    //std::cout<<"\ntest6";
    Matrix<int> test6;
    test6 = m1-1;
    //std::cout<<"\ntest7";
    Matrix<int> test7;
    test7 = m1+1;
    //std::cout<<"\ntest8";
    Matrix<int> test8 = m1;
    test8 += m2;
    //std::cout<<"\ntest9";
    Matrix<int> test9 = m1;
    test9 -= m2;

    Matrix<int> test10 = m1;
    test10 /= 2;

    Matrix<int> test11 = m1;
    test11 *= 2;

    Matrix<int> test12 = m1;
    test12 += 1;

    Matrix<int> test13 = m1;
    test13 -= 1;

    Matrix<int> test14 = m1;
    test14 *= m2;

    //expected results:
    Matrix<int> result1(&A_plus_B[0],4);        //m1 + m2
    Matrix<int> result2(&A_minus_B[0],4);       //m1 - m2
    Matrix<int> result3(&A_div_2[0], 4);        //m1 / 2
    Matrix<int> result4(&A_mul_2[0], 4);        //m1 * 2
    Matrix<int> result5(&A_mul_B[0], 4);        //m1 * m2
    Matrix<int> result6(&A_minus_1[0], 4);      //m1 - 1
    Matrix<int> result7(&A_plus_1[0], 4);       //m1 + 1

    if (test1 == result1) {std::cout<<"\nmatrix osszeadas jo";}
    else {std::cout<<"\nmatrix osszeadas rossz";}

    if (test2 == result2) {std::cout<<"\nmatrix kivonas jo";}
    else {std::cout<<"\n matrix kivonas rossz";}

    if (test3 == result3) {std::cout<<"\nskalarral osztas jo";}
    else {std::cout<<"\nskalarral osztas rossz";}

    if (test4 == result4) {std::cout<<"\nskalarral szorzas jo";}
    else {std::cout<<"\nskalarral szorzas rossz";}

    if (test5 == result5) {std::cout<<"\nmatrix szorzas jo";}
    else {std::cout<<"\nmatrix szorzas rossz";}

    if (test6 == result6) {std::cout<<"\nkivonas jo";}
    else {std::cout<<"\nkivonas rossz";}

    if (test7 == result7) {std::cout<<"\nosszeadas jo";}
    else {std::cout<<"\nosszeadas rossz";}

    if (test8 == result1) {std::cout<<"\n+= jo";}
    else {std::cout<<"\n+= rossz";}

    if (test9 == result2) {std::cout << "\n-= jo" ;}
    else {std::cout<<"\n-= rossz";}

    if (test10 == result3) {std::cout << "\n/= jo" ;}
    else {std::cout<<"\n/= rossz";}

    if (test11 == result4) {std::cout << "\n*= skalarral jo" ;}
    else {std::cout<<"\n*= skalarral rossz";}

    if (test12 == result7) {std::cout << "\n+= skalarral jo" ;}
    else {std::cout<<"\n+= skalarral rossz";}

    if (test13 == result6) {std::cout << "\n-= skalarral jo" ;}
    else {std::cout<<"\n-= skalarral rossz";}

    if (test14 == result5) {std::cout << "\n*= matrixszal jo" ;}
    else {std::cout<<"\n*= matrixszal rossz";}

    return 0;
}
