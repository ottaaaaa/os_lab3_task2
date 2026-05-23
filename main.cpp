#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

const int N = 100000000;

int main() {
    int threads;

    cout << "Enter number of threads: ";
    cin >> threads;

    // omp_set_num_threads() - функция, задаёт размер (N) команды потоков (team of threads) для всех последующих параллельных регионов в программе
    // альтернатива : использовать #pragma omp parallel num_threads(Т)
    omp_set_num_threads(threads);

    double pi = 0.0;

// #pragma omp - начало директивы
// parallel for - объявляет параллельный регион 
           // !!! объединяет создание потоков (parallel) и распределение итераций цикла (for)
           // !!! OpenMP сам разбивает диапазон 0 ... N-1 между потоками
// schedule(dynamic, 4315090) - использует динамическое планирование
                         // !!! потоки берут блоки по 431509 * 10 итераций по мере освобождения
// reduction(+:pi) - в данном случае, создаёт приватную копию pi=0 для каждого потока, суммирует локальные результаты внутри потока, а в конце региона автоматически складывает все приватные копии в глобальную pi
// общий ситаксис : reduction(operator : var1, var2, ...) - одна операция на 1+ переменных
                 // reduction(operator1 : var1, var2, ...) reduction(operator2 : var3, var4, ...) - если нужно задействовать несколько операторов
                 // !!! на одну переменную не может действовать несколько операторов, но один оператор может действовать на несколько переменных
                 // !!! когда создаются копии переменной, им присваивается значение нейтрального элемента по операции : + => 0, * => 1 ...
#pragma omp parallel for schedule(dynamic, 431509 * 10) reduction(+:pi)
    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) / N;
        pi += 4.0 / (1.0 + x * x);
    }

    pi /= N;

    cout.precision(25);
    cout << "Calculated pi = " << pi << endl;

    return 0;
}
