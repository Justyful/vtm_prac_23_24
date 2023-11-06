#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include "matrix.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::to_string;

int STRASS_CONST =  32;
Matrix Strassen(const Matrix& a, const Matrix& b) {
    int n = a.size();
    if (n == STRASS_CONST && n == b.size()) {
        return a * b;
    }
    int halfn = n/2;

    Matrix a11(halfn, false, false);
    Matrix a12(halfn, false, false);
    Matrix a21(halfn, false, false);
    Matrix a22(halfn, false, false);

    for (int i = 0; i < halfn; i++) {
        for (int j = 0; j < halfn; j++) {
            a11[i * halfn + j] = a[i * n + j];
        }
        for (int j = halfn; j < n; j++) {
            a12[i * halfn + j - halfn] = a[i * n + j];
        }
    }

    for (int i = halfn; i < n; i++) {
        for (int j = 0; j < halfn; j++) {
            a21[(i - halfn) * halfn + j] = a[i * n + j];
        }
        for (int j = halfn; j < n; j++) {
            a22[(i - halfn) * halfn + j - halfn] = a[i * n + j];
        }
    }

    Matrix b11(halfn, false, false);
    Matrix b12(halfn, false, false);
    Matrix b21(halfn, false, false);
    Matrix b22(halfn, false, false);

    for (int i = 0; i < halfn; i++) {
        for (int j = 0; j < halfn; j++) {
            b11[i * halfn + j] = b[i * n + j];
        }
        for (int j = halfn; j < n; j++) {
            b12[i * halfn + j - halfn] = b[i * n + j];
        }
    }

    for (int i = halfn; i < n; i++) {
        for (int j = 0; j < halfn; j++) {
            b21[(i - halfn) * halfn + j] = b[i * n + j];
        }
        for (int j = halfn; j < n; j++) {
            b22[(i - halfn) * halfn + j - halfn] = b[i * n + j];
        }
    }
    
    Matrix d  = Strassen(a11 + a22, b11 + b22);
    Matrix d1 = Strassen(a12 - a22, b21 + b22);
    Matrix d2 = Strassen(a21 - a11, b11 + b12);
    Matrix h1 = Strassen(a11 + a12, b22);
    Matrix h2 = Strassen(a21 + a22, b11);
    Matrix v1 = Strassen(a22, b21 - b11);
    Matrix v2 = Strassen(a11, b12 - b22);

    Matrix ans(n, false, false);

    for (int i = 0; i < halfn; i++) {
        for (int j = 0; j < halfn; j++) {
            ans[i * n + j] = d[i * halfn + j] + d1[i * halfn + j] + v1[i * halfn + j] - h1[i * halfn + j];
        }
        for (int j = halfn; j < n; j++) {
            ans[i * n + j] = v2[i * halfn + j - halfn] + h1[i * halfn + j - halfn];
        }
    }

    for (int i = halfn; i < n; i++) {
        for (int j = 0; j < halfn; j++) {
            ans[i * n + j] = v1[(i - halfn) * halfn + j] + h2[(i - halfn) * halfn + j];
        }
        for (int j = halfn; j < n; j++) {
            ans[i * n + j] = d[(i - halfn) * halfn + j - halfn] + d2[(i - halfn) * halfn + j - halfn] + 
                            v2[(i - halfn) * halfn + j - halfn] - h2[(i - halfn) * halfn + j - halfn];
        }
    }
    return ans;
}

int main() {
    std::srand(std::time(nullptr));
    
    for (int i = 2; i < 513; i *= 2) {
        std::ofstream file;
        string name = "../tests/strass=" + to_string(i) + ".csv";
        cout << name << endl;
        file.open(name);
        STRASS_CONST = i;
        cout << "STRASS_CONST = " << i << endl;
        file << "STRASS_CONST = " << i << endl;
        for (int n = i; n < 4097; n *= 2) {
            file << n << ",";
            cout << setw(5) << n << ",";
            Matrix x = Matrix(n, true);
            Matrix y = Matrix(n, true);
            //print(x, 3);
            //print(y, 3);
            
            auto start = std::chrono::high_resolution_clock::now();
            Matrix z = x * y;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration1 = end - start;
            file << duration1.count() << ",";
            cout << setw(13) << duration1.count() << ",";
            
            Matrix x1 = x.extend();
            Matrix y1 = y.extend();
            start = std::chrono::high_resolution_clock::now();
            Matrix w = Strassen(x1, y1);
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration2 = end - start;
            file << duration2.count() << ",";
            cout << setw(13) << duration2.count() << ",";
            file << duration2.count() - duration1.count() << ",";
            cout << setw(13) << duration2.count() - duration1.count() << ",";
            Matrix a = z - w;
            file << C(a) << " " << F(a) << '\n';
            cout << C(a) << " " << F(a) << endl;
        }
        file.close();
        cout << endl << endl;
    }
    return 0;
}
