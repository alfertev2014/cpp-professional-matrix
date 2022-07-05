
#include "matrix.h"

#include <iostream>
#include <assert.h>

int main() {
    // бесконечная матрица int заполнена значениями -1
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    std::cout << a << std::endl;
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    // выведется одна строка
    // 100100314
    for(auto [k, v] : matrix) {
        auto [x, y] = k;
        std::cout << x << y << v << std::endl;
    }

    return 0;
}
