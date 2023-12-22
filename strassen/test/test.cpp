#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include "matrix.h"
#include "strassen.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::to_string;

int main() {
    std::srand(std::time(nullptr));

    // int n = 1024;
    // Matrix a(n, true);
    // Matrix b(n, true);
    // Matrix c(n);
    // Matrix d(n);
    // Matrix e(n);

    // d = a*b;
    // c.blockMulSubMatrices(a, b, 4);
    // e = c - d;
    // cout << F(e) << " " << C(e) << endl;



    for (int n = 2048; n < 4097; n *= 2) {
        cout << setw(5) << n << ",";
        Matrix x(n, true);
        Matrix y(n, true);
        auto start = std::chrono::high_resolution_clock::now();
        Matrix z = x * y;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end - start;
        cout << setw(13) << duration1.count() << ",";
        Matrix w(n);
        start = std::chrono::high_resolution_clock::now();
        Strassen(x, y, w);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end - start;
        cout << setw(13) << duration2.count() << ",";
        cout << setw(13) << duration2.count() - duration1.count() << ",";
        Matrix a = z - w;
        cout << C(a) << " " << F(a) << endl;
    }
    return 0;
}
