#pragma once
class Matrix {
    double *m;
    int n;
    
    public:
    Matrix(int size, bool random = false);
    Matrix(const Matrix& mat);

    ~Matrix();
    
    int size() const;
    void set_size(int k);
    double* get_m() const;
    
    Matrix extend() const;
    
    double operator[](int k) const;
    Matrix operator* (const Matrix& mat) const;
    Matrix operator+ (const Matrix& mat) const;
    Matrix operator- (const Matrix& mat) const;
    void operator= (const Matrix& mat);
};

double F(const Matrix& m);
double C(const Matrix& m);
void print(const Matrix& m, int w);
void print2(const Matrix& m1, const Matrix& m2, int w); 