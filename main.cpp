#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

const int N = 100000000;

int main() {
    int threads;

    cout << "\tEnter number of threads : ";
    cin >> threads;

    // omp_set_num_threads() - функция, задаёт размер (N) команды потоков (team of threads) для всех последующих параллельных регионов в программе
    // альтернатива : использовать #pragma omp parallel num_threads(Т)
    omp_set_num_threads(threads);

    double pi = 0.0;

    auto start = chrono::high_resolution_clock::now();

#pragma omp parallel for schedule(dynamic, 431509 * 10) reduction(+:pi)
    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) / N;
        pi += 4.0 / (1.0 + x * x);
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start);

    pi /= N;

    cout.precision(25);
    cout << "\t          Calculated pi : " << pi << endl;
    cout.precision(3);
    cout << fixed;
    cout << "\t         Execution time : " << elapsed_ms.count() << " ms" << endl;

    return 0;
}
