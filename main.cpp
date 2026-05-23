#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

const int N = 100000000;

int main() {
    int threads;

    cout << "Enter number of threads: ";
    cin >> threads;

    omp_set_num_threads(threads);

    return 0;
}
