#include "strassen.h"
#include <iostream>
constexpr int STRASS_CONST = 128;
constexpr int BLOCK_CONST = 64;
void Strassen(const Matrix& a, const Matrix& b, Matrix& ans) {
    int n = a.size();
    //std::cout << n << std::endl;
    if (n == STRASS_CONST && n == b.size()) {
        ans.blockMulSubMatrices(a, b, BLOCK_CONST);
        return;
    }
    int halfn = n/2;

    Matrix arg1(halfn);
    Matrix arg2(halfn);
    Matrix res(halfn);

    Matrix sub1(a, 0, 0, halfn); //a11
    Matrix sub2(a, halfn, halfn, halfn); //a22

    arg1.addSubMatrices(1, sub1, sub2); //arg1 = a11 + a22

    sub1.setSubMatrix(b, 0, 0, halfn); //b11
    sub2.setSubMatrix(b, halfn, halfn, halfn); //b22

    arg2.addSubMatrices(1, sub1, sub2); //arg2 = b11 + b22
    
    Strassen(arg1, arg2, res); //d = (a11 + a22)(b11 + b22)

    ans.addSubMatrix(1, res, 0, 0); //ans11 += d
    ans.addSubMatrix(1, res, halfn, halfn); //ans22 += d
    res.zero();



    sub1.setSubMatrix(a, 0, halfn, halfn); //a12
    sub2.setSubMatrix(a, halfn, halfn, halfn); //a22

    arg1.addSubMatrices(-1, sub1, sub2); //arg1 = a12 - a22

    sub1.setSubMatrix(b, halfn, 0, halfn); //b21
    sub2.setSubMatrix(b, halfn, halfn, halfn); //b22

    arg2.addSubMatrices(1, sub1, sub2); //arg2 = b21 + b22

    Strassen(arg1, arg2, res); //d1

    ans.addSubMatrix(1, res, 0, 0); //ans11 += d1
    res.zero();



    sub1.setSubMatrix(a, halfn, 0, halfn); //a21
    sub2.setSubMatrix(a, 0, 0, halfn); //a11

    arg1.addSubMatrices(-1, sub1, sub2); //arg1 = a21 - a11

    sub1.setSubMatrix(b, 0, 0, halfn); //b11
    sub2.setSubMatrix(b, 0, halfn, halfn); //b12

    arg2.addSubMatrices(1, sub1, sub2); //arg2 = b11 + b12

    Strassen(arg1, arg2, res); //d2

    ans.addSubMatrix(1, res, halfn, halfn); //ans22 += d2
    res.zero();



    sub1.setSubMatrix(a, 0, 0, halfn); //a11
    sub2.setSubMatrix(a, 0, halfn, halfn); //a12

    arg1.addSubMatrices(1, sub1, sub2); //arg1 = a11 + a12

    sub1.setSubMatrix(b, halfn, halfn, halfn); //b22

    arg2.eqSubMatrix(sub1); //arg2 = b22

    Strassen(arg1, arg2, res); //h1

    ans.addSubMatrix(-1, res, 0, 0); //ans11 -= h1
    ans.addSubMatrix(1, res, 0, halfn); //ans12 += h1
    res.zero();



    sub1.setSubMatrix(a, halfn, 0, halfn); //a21
    sub2.setSubMatrix(a, halfn, halfn, halfn); //a22

    arg1.addSubMatrices(1, sub1, sub2); //arg1 = a21 + a22

    sub1.setSubMatrix(b, 0, 0, halfn); //b11

    arg2.eqSubMatrix(sub1); //arg2 = b11

    Strassen(arg1, arg2, res); //h2

    ans.addSubMatrix(1, res, halfn, 0); //ans21 += h2
    ans.addSubMatrix(-1, res, halfn, halfn); //ans22 -= h2
    res.zero();



    sub1.setSubMatrix(a, halfn, halfn, halfn); //a22

    arg1.eqSubMatrix(sub1); //arg1 = a22

    sub1.setSubMatrix(b, halfn, 0, halfn); //b21
    sub2.setSubMatrix(b, 0, 0, halfn); //b11

    arg2.addSubMatrices(-1, sub1, sub2); //arg2 = b21 - b11

    Strassen(arg1, arg2, res); //v1

    ans.addSubMatrix(1, res, 0, 0); //ans11 += v1
    ans.addSubMatrix(1, res, halfn, 0); //ans21 += v1
    res.zero();



    sub1.setSubMatrix(a, 0, 0, halfn); //a11

    arg1.eqSubMatrix(sub1); //arg1 = a11

    sub1.setSubMatrix(b, 0, halfn, halfn); //b12
    sub2.setSubMatrix(b, halfn, halfn, halfn); //b22

    arg2.addSubMatrices(-1, sub1, sub2); //arg2 = b12 - b22

    Strassen(arg1, arg2, res); //v2

    ans.addSubMatrix(1, res, 0, halfn); //ans12 += v2
    ans.addSubMatrix(1, res, halfn, halfn); //ans22 += v2
    res.zero();
    return;
}