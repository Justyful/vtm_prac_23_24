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
    
    for (int i = 2; i < 513; i *= 2) {
        std::ofstream file;
        string name = "results/strass=" + to_string(i) + ".csv";
        cout << name << endl;
        file.open(name);
        cout << "STRASS_CONST = " << i << endl;
        for (int n = i; n < 4097; n *= 2) {
            file << n << ",";
            cout << setw(5) << n << ",";
            Matrix x(n, true);
            Matrix y(n, true);
            auto start = std::chrono::high_resolution_clock::now();
            Matrix z = x * y;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration1 = end - start;
            file << duration1.count() << ",";
            cout << setw(13) << duration1.count() << ",";
            Matrix w(n);
            start = std::chrono::high_resolution_clock::now();
            Strassen(x, y, w, i);
            //cout << "VSE GOOD" << endl;
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration2 = end - start;
            file << duration2.count() << ",";
            cout << setw(13) << duration2.count() << ",";
            file << duration2.count() - duration1.count() << ",";
            cout << setw(13) << duration2.count() - duration1.count() << ",";
            Matrix a = z - w;
            file << C(a) << "," << F(a) << '\n';
            cout << C(a) << " " << F(a) << endl;
        }
        file.close();
        cout << endl << endl;
    }
    return 0;
}
