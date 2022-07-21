
#include "matrix.h"

#include <iostream>
#include <assert.h>

void simpleSmokeTest() {
    // бесконечная матрица int заполнена значениями -1
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны

    int a = matrix[0][0];
    std::cout << a << std::endl;
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    // выведется одна строка
    // 100100314
    for(auto [k, v] : matrix) { // C++17
        auto [x, y] = k; // std::pair
        std::cout << x << y << v << std::endl;
    }


    // !!!!! Ограничения:

    // matrix[123][321].blaBla() - если бы была матрица объектов, мы бы не смогли так делать.
    // matrix[123][321]->blaBla() - и вот так.
    //     Сначала нужно скопировать объект в переменную, а потом вызывать методы.

    // auto cell = matrix[123][321]; // Мы не можем получить ячейки и копировать/перемещать их.
    // int &element = matrix[123][321];  // Мы не можем получать прямые ссылки на элементы, потому что может быть значение Default, которое не хранится нигде
}

void fillAndTraverseTest() {
    // При запуске программы необходимо создать матрицу с пустым значением 0, заполнить главную
    // диагональ матрицы (от [0,0] до [9,9]) значениями от 0 до 9.
    Matrix<int, 0> matrix;

    for (int i = 0; i < 10; ++i) {
        matrix[i][i] = i;
    }


    // Второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0.
    for (int i = 0; i < 10; ++i) {
        matrix[i][9 - i] = 9 - i;
    }


    // Необходимо вывести фрагмент матрицы от [1,1] до [8,8]. Между столбцами пробел. Каждая строка
    // матрицы на новой строке консоли.
    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    // Вывести количество занятых ячеек.
    std::cout << matrix.size() << std::endl;

    // Вывести все занятые ячейки вместе со своими позициями
    for(auto [k, v] : matrix) {
        auto [x, y] = k;
        std::cout << x << ' ' << y << ' '<< v << std::endl;
    }
}

int main() {
    // Сначала тесты из задания
    simpleSmokeTest();

    fillAndTraverseTest();

    return 0;
}
