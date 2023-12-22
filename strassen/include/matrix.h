#pragma once
class Matrix {
    double *m;
    int n;
    int i0;
    int j0;
    int sub_n;
    
    public:
    Matrix(int size, bool random = false, bool fill = true, bool alloc = true);
    Matrix(const Matrix& mat);
    Matrix(const Matrix& a, int i0, int j0, int size);

    ~Matrix();

    void setSubMatrix(const Matrix& a, int i, int j, int size);
    void eqSubMatrix(const Matrix& sub);

    void addSubMatrix(double alpha, const Matrix& sub, int i1, int j1);
    void addSubMatrices(double alpha, const Matrix& arg1, const Matrix& arg2);
    void mulSubMatrices(const Matrix& arg1, const Matrix& arg2);
    
    int size() const;
    void set_size(int k);
    double* getm() const;
    void zero();
    void setn(int k);
    
    Matrix extend() const;
    
    double &operator[](int k);
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