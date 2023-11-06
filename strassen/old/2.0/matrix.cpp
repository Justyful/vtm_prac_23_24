#include <iostream>
#include <iomanip>
#include <cmath>
using std::cout;
using std::endl;
using std::setw;
class Matrix {
    double *m;
    int n;
    
    public:
    Matrix(int size, bool random = false) {
        n = size;
        m = new double [n * n];
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
    Matrix(const Matrix& mat) {
        n = mat.size();
        m = new double [n * n];
        for (int i = 0; i < n * n; i++) {
            m[i] = mat[i];
        }
    }

    ~Matrix() {
        delete[] m;
    }
    
    int size() const {
        return n;
    }
    
    void setn(int k) {
        n = k;   
    }
    
    double* getm() const {
        return m;
    }
    
    Matrix extend() const {
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
    
    double operator[](int k) const {
        return m[k];
    }
    
    Matrix operator* (const Matrix& mat) const {
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
    
    Matrix operator+ (const Matrix& mat) const {
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
    
    Matrix operator- (const Matrix& mat) const {
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
    
    void operator= (const Matrix& mat) {
        delete[] m;
        n = mat.size();
        m = new double [n * n];
        for (int i = 0; i < n * n; i++) {
            m[i] = mat[i];
        }
    }
    
    Matrix get11() const {
        int halfn = n/2;
        Matrix ans(halfn, false);
        double* ansm = ans.getm();
        for (int i = 0; i < halfn; i++) {
            for (int j = 0; j < halfn; j++) {
                ansm[i * halfn + j] = m[i * n + j];
            }
        }
        return ans;
    }
    Matrix get12() const {
        int halfn = n/2;
        Matrix ans(n / 2, false);
        double* ansm = ans.getm();
        for (int i = 0; i < halfn; i++) {
            for (int j = halfn; j < n; j++) {
                ansm[i * halfn + j - halfn] = m[i * n + j];
            }
        }
        return ans;
    }
    Matrix get21() const {
        int halfn = n/2;
        Matrix ans(n / 2, false);
        double* ansm = ans.getm();
        for (int i = halfn; i < n; i++) {
            for (int j = 0; j < halfn; j++) {
                ansm[(i - halfn) * halfn + j] = m[i * n + j];
            }
        }
        return ans;
    }
    Matrix get22() const {
        int halfn = n/2;
        Matrix ans(halfn, false);
        double* ansm = ans.getm();
        for (int i = halfn; i < n; i++) {
            for (int j = halfn; j < n; j++) {
                ansm[(i - halfn) * halfn + j - halfn] = m[i * n + j];
            }
        }
        return ans;
    }
};

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

Matrix assemble(const Matrix& a11, const Matrix& a12, const Matrix& a21, const Matrix& a22) {
    if (a11.size() != a12.size() || a12.size() != a21.size() || a21.size() != a22.size()) {
        cout << "error assemble" << endl;
        exit(1);
    }
    int n  = a11.size();
    int n2 = n * 2;
    Matrix ans(n2, false);
    double* ansm = ans.getm();
    double* a11m = a11.getm();
    double* a12m = a12.getm();
    double* a21m = a21.getm();
    double* a22m = a22.getm();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ansm[i * n2 + j] = a11m[i * n + j];
        }
        for (int j = n; j < n2; j++) {
            ansm[i * n2 + j] = a12m[i * n + j - n];
        }
    }
    
    for (int i = n; i < n2; i++) {
        for (int j = 0; j < n; j++) {
            ansm[i * n2 + j] = a21m[(i - n) * n + j];
        }
        for (int j = n; j < n2; j++) {
            ansm[i * n2 + j] = a22m[(i - n) * n + j - n];
        }
    }
    return ans;
}