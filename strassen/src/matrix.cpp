#include <iostream>
#include <iomanip>
#include <cmath>


#include "matrix.h"


using std::cout;
using std::endl;
using std::setw;


    Matrix::Matrix(int size, bool random, bool fill, bool alloc) {
        i0 = 0;
        j0 = 0;
        sub_n = 0;
        n = size;
        if (alloc) m = new double [n * n];
        if (!fill) return;
        if (random) {
            for (int i = 0; i < n * n; i++) {
                m[i] = rand() % 10;
            }
        }
        else {
            for (int j = 0; j < n * n; j++) {
                m[j] = 0;
            }
        }
    }
    Matrix::Matrix(const Matrix& mat) {
        n = mat.size();
        m = new double [n * n];
        for (int i = 0; i < n * n; i++) {
            m[i] = mat[i];
        }
    }

    Matrix::Matrix(const Matrix& a, int i0, int j0, int size) : m(a.m), n(a.n), i0(i0), j0(j0), sub_n(size) {}

    Matrix::~Matrix() {
        if (sub_n == 0) delete[] m;
    }

    void Matrix::setSubMatrix(const Matrix& a, int i, int j, int size) {
        if ((i0 + size > a.n) || (j0 + size > a.n)) {
            cout << "ERROR: setSubMatrix" << endl;
        }
        m = a.m;
        n = a.n;
        i0 = i;
        j0 = j;
        sub_n = size;
    }

    void Matrix::eqSubMatrix(const Matrix& sub) {
        if (sub.n < 1) {
            cout << "ERROR: addSubMatrix2" << endl;
        }
        int i1 = sub.i0;
        int j1 = sub.j0;
        int n1 = sub.n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i * n + j] = sub.m[(i1 + i) * n1 + j1 + j];
            }
        }
    }

    void Matrix::addSubMatrix(double alpha, const Matrix& sub, int i1, int j1) {
        if (sub.n < 1) {
            cout << "ERROR: addSubMatrix2" << endl;
        }
        int n1 = sub.n;
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n1; j++) {
                m[(i1 + i) * n + j1 + j] += alpha * sub.m[i * n1 + j];
            }
        }
    }

    void Matrix::addSubMatrices(double alpha, const Matrix& arg1, const Matrix& arg2) {
        if ((arg1.sub_n != arg2.sub_n) || (arg1.sub_n != n) || (arg1.n != arg2.n)) {
            cout << "ERROR: addSubMatrices" << endl;
        }
        int i1 = arg1.i0;
        int j1 = arg1.j0;
        int i2 = arg2.i0;
        int j2 = arg2.j0;
        int n12 = arg1.n;
        double* m1 = arg1.m;
        double* m2 = arg2.m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                m[i * n + j] = m1[(i1 + i) * n12 + j1 + j] + alpha * m2[(i2 + i) * n12 + j2 + j];
        }
    }

    void Matrix::mulSubMatrices(const Matrix& arg1, const Matrix& arg2) {
        if ((arg1.n != arg2.n) || (arg1.n != n)) {
            cout << "ERROR: mulSubMatrices" << endl;
        }
        double* m1 = arg1.m;
        double* m2 = arg2.m;
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++)
                    m[i * n + j] += m1[i * n + k] * m2[k * n + j];
            }
        }
    }
    
    int Matrix::size() const {
        return n;
    }
    
    void Matrix::setn(int k) {
        n = k;   
    }
    
    double* Matrix::getm() const {
        return m;
    }

    void Matrix::zero() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i * n + j] = 0;
            }
        }
    }
    
    Matrix Matrix::extend() const {
        int new_n = pow(2, ceil(log2(n)));
        Matrix new_m(new_n, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                new_m.m[i * n + j] = m[i * n + j];
            }
            for (int j = n; j < new_n; j++) {
                new_m.m[i * n + j] = 0;
            }
        }
        for (int i = n; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                new_m.m[i * n + j] = 0;
            }
        }
        return new_m;
    }
    
    double& Matrix::operator[](int k) {
        return m[k];
    }

    double Matrix::operator[](int k) const {
        return m[k];
    }
    
    Matrix Matrix::operator* (const Matrix& mat) const {
        if (n != mat.size()) {
            cout << "ERROR WRONG SIZES" << endl;
            exit(1);
        }
        Matrix ans(n, false);
        double* ansm = ans.m;
        double* matm = mat.m;
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    ansm[i * n + j] += m[i * n + k] * matm[k * n + j];
                }
            }
        }
        return ans;
    }
    
    Matrix Matrix::operator+ (const Matrix& mat) const {
        if (n != mat.size()) {
            cout << "ERROR WRONG SIZES" << endl;
            exit(1);
        }
        Matrix ans(n, false);
        double* ansm = ans.m;
        double* matm = mat.m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ansm[i * n + j] = m[i * n + j] + matm[i * n + j];
            }
        }
        return ans;
    }
    
    Matrix Matrix::operator- (const Matrix& mat) const {
        if (n != mat.size()) {
            cout << "ERROR WRONG SIZES" << endl;
            exit(1);
        }
        Matrix ans(n, false);
        double* ansm = ans.m;
        double* matm = mat.m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ansm[i * n + j] = m[i * n + j] - matm[i * n + j];
            }
        }
        return ans;
    }
    
    void Matrix::operator= (const Matrix& mat) {
        delete[] m;
        n = mat.size();
        m = new double [n * n];
        for (int i = 0; i < n * n; i++) {
            m[i] = mat[i];
        }
    }

double F(const Matrix& m) {
    double ans = 0.0;
    double* mm = m.getm();
    for (int i = 0; i < m.size() * m.size(); i++) {
        ans += mm[i] * mm[i];
    }
    return sqrt(ans);
}

double C(const Matrix& m) {
    double ans = 0.0;
    double* mm = m.getm();
    for (int i = 0; i < m.size() * m.size(); i++) {
        ans = abs(mm[i]) > ans ? abs(mm[i]) : ans;
    }
    return ans;
}

void print(const Matrix& m, int w)   {
    int n = m.size();
    double* mm = m.getm();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(w) << mm[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print2(const Matrix& m1, const Matrix& m2, int w) { 
    if (m1.size() != m2.size()) {
        cout << "ERROR print2";
        print(m1, w);
        print(m2, w);
        return;
    }
    int n = m1.size();
    double* m1m = m1.getm();
    double* m2m = m2.getm();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(w) << m1m[i * n + j] << " ";
        }
        cout << "  |  ";
        for (int j = 0; j < n; j++) {
            cout << setw(w) << m2m[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
