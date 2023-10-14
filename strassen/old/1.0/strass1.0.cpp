#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::to_string;

int STRASS_CONST = 2;

class Matrix {
    double **m;
    int n;
    
    public:
    Matrix(int size, bool random = false) {
        n = size;
        m = new double*[n];
        if (random) {
            for (int i = 0; i < n; i++) {
                m[i] = new double[n];
                for (int j = 0; j < n; j++) {
                    m[i][j] = rand() % 10;
                }
            }
        }
        else {
            for (int i = 0; i < n; i++) {
                m[i] = new double[n];
                for (int j = 0; j < n; j++) {
                    m[i][j] = 0;
                }
            }
        }
    }
    
    Matrix(const Matrix& mat) {
        n = mat.size();
        m = new double*[n];
        for (int i = 0; i < n; i++) {
            m[i] = new double[n];
            for (int j = 0; j < n; j++) {
                m[i][j] = mat[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < n; i++) {
            delete[] m[i];
        }
        delete[] m;
    }
    
    int size() const {
        return n;
    }
    
    void setn(int k) {
        n = k;   
    }
    
    double** getm() const {
        return m;
    }
    
    Matrix extend() const {
        int new_n = pow(2, ceil(log2(n)));
        Matrix new_m(new_n, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                new_m[i][j] = m[i][j];
            }
            for (int j = n; j < new_n; j++) {
                new_m[i][j] = 0;
            }
        }
        for (int i = n; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                new_m[i][j] = 0;
            }
        }
        return new_m;
    }
    
    double* operator[](int k) const {
        return m[k];
    }
    
    Matrix operator* (const Matrix& mat) const {
        if (n != mat.size()) {
            cout << "ERROR WRONG SIZES" << endl;
            exit(1);
        }
        Matrix ans(n, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    ans[i][j] += m[i][k] * mat[k][j];
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
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][j] = m[i][j] + mat[i][j];
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
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][j] = m[i][j] - mat[i][j];
            }
        }
        return ans;
    }
    
    void operator= (const Matrix& mat) {
        for (int i = 0; i < n; i++) {
            delete[] m[i];
        }
        delete[] m;
        n = mat.size();
        m = new double*[n];
        for (int i = 0; i < n; i++) {
            m[i] = new double[n];
            for (int j = 0; j < n; j++) {
                m[i][j] = mat[i][j];
            }
        }
    }
    
    Matrix get11() const {
        Matrix ans(n / 2, false);
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {
                ans[i][j] = m[i][j];
            }
        }
        return ans;
    }
    Matrix get12() const {
        Matrix ans(n / 2, false);
        for (int i = 0; i < n / 2; i++) {
            for (int j = n / 2; j < n; j++) {
                ans[i][j - n / 2] = m[i][j];
            }
        }
        return ans;
    }
    Matrix get21() const {
        Matrix ans(n / 2, false);
        for (int i = n / 2; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                ans[i - n / 2][j] = m[i][j];
            }
        }
        return ans;
    }
    Matrix get22() const {
        Matrix ans(n / 2, false);
        for (int i = n / 2; i < n; i++) {
            for (int j = n / 2; j < n; j++) {
                ans[i - n / 2][j - n /2] = m[i][j];
            }
        }
        return ans;
    }
};

double F(Matrix& m) {
    double ans = 0.0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            ans += m[i][j] * m[i][j];
        }
    }
    return sqrt(ans);
}

double C(Matrix& m) {
    double ans = 0.0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            ans = abs(m[i][j]) > ans ? abs(m[i][j]) : ans;
        }
    }
    return ans;
}

void print(Matrix& m, int w) {
    int n = m.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(w) << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print2(Matrix& m1, Matrix& m2, int w) {
    int n = m1.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(w) << m1[i][j] << " ";
        }
        cout << "   ";
        for (int j = 0; j < n; j++) {
            cout << setw(w) << m2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Matrix assemble(Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22) {
    if (a11.size() != a12.size() && a12.size() != a21.size() && a21.size() != a22.size()) {
        cout << "error assemble" << endl;
        exit(1);
    }
    int n = a11.size();
    Matrix ans(n * 2, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = a11[i][j];
        }
        for (int j = n; j < 2 * n; j++) {
            ans[i][j] = a12[i][j - n];
        }
    }
    
    for (int i = n; i < 2 * n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = a21[i - n][j];
        }
        for (int j = n; j < 2 * n; j++) {
            ans[i][j] = a22[i - n][j - n];
        }
    }
    
    return ans;
}

Matrix Strassen(const Matrix& a, const Matrix& b) {
    int n = a.size();
    if (n == STRASS_CONST && n == b.size()) {
        return a * b;
    }
    
    Matrix a11 = a.get11();
    Matrix a12 = a.get12();
    Matrix a21 = a.get21();
    Matrix a22 = a.get22();
    
    Matrix b11 = b.get11();
    Matrix b12 = b.get12();
    Matrix b21 = b.get21();
    Matrix b22 = b.get22();
    
    Matrix d  = Strassen(a11 + a22, b11 + b22);
    Matrix d1 = Strassen(a12 - a22, b21 + b22);
    Matrix d2 = Strassen(a21 - a11, b11 + b12);
    Matrix h1 = Strassen(a11 + a12, b22);
    Matrix h2 = Strassen(a21 + a22, b11);
    Matrix v1 = Strassen(a22, b21 - b11);
    Matrix v2 = Strassen(a11, b12 - b22);

    Matrix ans11 = d + d1 + v1 - h1;
    Matrix ans12 = v2 + h1;
    Matrix ans21 = v1 + h2;
    Matrix ans22 = d + d2 + v2 - h2;
    
    Matrix ans = assemble(ans11, ans12, ans21, ans22);
    //print(ans, 6);
    return ans;
}

int main() {
    std::srand(std::time(nullptr));

    for (int i = 32; i < 513; i *= 2) {
        STRASS_CONST = i;
        std::ofstream file;
        string name = "strass=" + to_string(i) + ".csv";
        cout << name << endl;
        file.open(name);
        for (int n = i; n < 4097; n *= 2) {
            file << n << ",";
            cout << n << ",";
            Matrix x = Matrix(n, true).extend();
            Matrix y = Matrix(n, true).extend();
            //print(x, 3);
            //print(y, 3);
            
            auto start = std::chrono::high_resolution_clock::now();
            Matrix z = x * y;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration1 = end - start;
            file << duration1.count() << ",";
            cout << duration1.count() << ",";
            
            Matrix x1 = x.extend();
            Matrix y1 = y.extend();
            start = std::chrono::high_resolution_clock::now();
            Matrix w = Strassen(x1, y1);
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration2 = end - start;
            file << duration2.count() << ",";
            cout << duration2.count() << ",";
            file << duration2.count() - duration1.count() << ",";
            cout << duration2.count() - duration1.count() << ",";
            Matrix a = z - w;
            file << F(a) << '\n';
            cout << F(a) << endl;
        }
        file.close();
        cout << endl << endl;
    }
    /*
    for (int i = 512; i < 513; i *= 2) {
        STRASS_CONST = i;
        std::ofstream file;
        string name = "2strass=" + to_string(i) + ".csv";
        cout << name << endl;
        file.open(name);
        for (int n = i; n < 1025; n++) {
            file << n << ",";
            cout << n << ",";
            Matrix x = Matrix(n, true);
            Matrix y = Matrix(n, true);
            //print(x, 3);
            //print(y, 3);
            
            auto start = std::chrono::high_resolution_clock::now();
            Matrix z = x * y;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration1 = end - start;
            file << duration1.count() << ",";
            cout << duration1.count() << ",";
            
            Matrix x1 = x.extend();
            Matrix y1 = y.extend();
            start = std::chrono::high_resolution_clock::now();
            Matrix w = Strassen(x1, y1);
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration2 = end - start;
            file << duration2.count() << ",";
            file << duration2.count() - duration1.count() << ",";
            cout << duration2.count() << ",";
            cout << duration2.count() - duration1.count() << ",";
            z = z.extend();
            Matrix a = z - w;
            file << F(a) << '\n';
            cout << F(a) << endl << endl;
        }
        file.close();
    }
    */
    /*
    STRASS_CONST = 16;
    for (int n = 128; n < 15000; n*=2) {
        cout << "n = " << n << endl;
        Matrix x = Matrix(n, true).extend();
        Matrix y = Matrix(n, true).extend();
        //print(x, 3);
        //print(y, 3);
        
        auto start = std::chrono::high_resolution_clock::now();
        Matrix z = x * y;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end - start;
        cout << "   Execution time: " << duration1.count() << " seconds." << endl;
        
        Matrix x1 = x.extend();
        Matrix y1 = y.extend();
        start = std::chrono::high_resolution_clock::now();
        Matrix w = Strassen(x1, y1);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end - start;
        cout << "   Execution time: " << duration2.count() << " seconds." << endl;
        cout << "   Difference : " << duration2.count() - duration1.count() << " seconds." << endl;
        Matrix a = z - w;
        cout << "   Check: " << F(a) << endl;
        STRASS_CONST *= 2;
    }
    */
    return 0;
}






