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
            cout << duration2.count() << ",";
            file << duration2.count() - duration1.count() << ",";
            cout << duration2.count() - duration1.count() << ",";
            Matrix a = z - w;
            file << C(a) << " " << F(a) << '\n';
            cout << C(a) << " " << F(a) << endl;
        }
        file.close();
        cout << endl << endl;
    }
    return 0;
}
