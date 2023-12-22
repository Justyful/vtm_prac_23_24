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
    for (int n = 256; n < 4097; n *= 2) {
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
