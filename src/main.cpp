#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <ctime>
using namespace std;

// Функция для генерации массива случайных чисел
void generateRandomArray(int size, function<void(vector<int>)> callback) {
    vector<int> arr;
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr.push_back(rand() % 100); 
    }
    callback(arr); 
}

// Функция для обработки массива с использованием callback-функции
void processArray(const vector<int>& arr, function<int(int)> processor, function<void(vector<int>)> callback) {
    vector<int> processedArr;
    for (int num : arr) {
        processedArr.push_back(processor(num)); 
    }
    callback(processedArr); 
}

int main() {
    int size = 10;

    generateRandomArray(size, [&](vector<int> originalArray) {
        cout << "Исходный массив: ";
        for (int num : originalArray) {
            cout << num << " ";
        }
        cout << endl;

        processArray(originalArray, [](int num) -> int {
            return num * 2; 
        },
        [&](vector<int> processedArray) {
            cout << "Обработанный массив: ";
            for (int num : processedArray) {
                cout << num << " ";
            }
            cout << endl;
        });
    });

    return 0;
}