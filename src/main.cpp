#include <iostream>
#include <future>
#include <vector>
#include <functional>
using namespace std;

// Функция для генерации вектора случайных чисел
void gen_vector(int sz, function<void(vector<int>)> callback) {
    vector<int> vec;
    srand(time(0));
    for (int i = 0; i < sz; i++) {
        vec.push_back(rand() % 100);
    }
    callback(vec);
}

// Функция для вычисления суммы элементов вектора
void summa(const vector<int>& vec, function<void(int)> callback) {
    int sm = 0;
    for (auto i : vec) {
        sm += i;
    }
    callback(sm);
}

// Функция для вычисления произведения элементов вектора
void proizved(const vector<int>& vec, function<void(int)> callback) {
    int pr = 1;
    for (auto i : vec) {
        pr *= i;
    }
    callback(pr);
}

int main() {
    auto task1 = async(launch::async, [](function<void(vector<int>)> callback) {
        gen_vector(10, callback);
    },
    [](vector<int> vec) {
        cout << "Сгенерированный вектор: ";
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;

        auto task2 = async(launch::async, [vec](function<void(int)> callback) {
            summa(vec, callback);
        },
        [](int sm) {
            cout << "Сумма элементов: " << sm << endl;
        });

        auto task3 = async(launch::async, [vec](function<void(int)> callback) {
            proizved(vec, callback);
        },
        [](int pr) {
            cout << "Произведение элементов: " << pr << endl;
        });
    });

    return 0;
}