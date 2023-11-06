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
    
    Matrix get11() const;
    Matrix get12() const;
    Matrix get21() const;
    Matrix get22() const;
};

double F(const Matrix& m);
double C(const Matrix& m);
void print(const Matrix& m, int w);
void print2(const Matrix& m1, const Matrix& m2, int w); 
Matrix assemble(const Matrix& a11, const Matrix& a12, const Matrix& a21, const Matrix& a22);