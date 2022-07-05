#pragma once

#include <cstdint>
#include <unordered_map>

#include "hashing.h"

template <typename T, T Default = T{}>
class Matrix {
public:
    Matrix() = default;

    std::size_t size() const { return internalMap.size(); }

    struct Cell {
        Matrix &matrix;
        const std::size_t column;
        const std::size_t row;

        Cell(Matrix &matrix, const std::size_t column, const std::size_t row)
            : matrix(matrix), column(column), row(row) {}

        const Cell &operator=(const T& value) const {
            if (value == Default) {
                matrix.internalMap.erase(std::make_pair(column, row));
            } else {
                matrix.internalMap[std::make_pair(column, row)] = value;
            }
            return *this;
        }

        operator T () {
            auto it = matrix.internalMap.find(std::make_pair(row, column));
            if (it != matrix.internalMap.end()) {
                return it->second;
            } else {
                return Default;
            }
        }
    };

    class ColumnRef {
        Matrix &matrix;
        const std::size_t index;
    public:
        ColumnRef(Matrix &matrix, std::size_t index) : matrix(matrix), index(index) {}
        Cell operator[](std::size_t rowIndex) const {
            return Cell( matrix, index, rowIndex );
        }
    };

    class ConstColumnRef {
        const Matrix &matrix;
        const std::size_t index;
    public:
        ConstColumnRef(const Matrix &matrix, std::size_t index) : matrix(matrix), index(index) {}

        const T &operator[](std::size_t rowIndex) const {
            auto it = matrix.internalMap.find(std::make_pair(index, rowIndex));
            if (it != matrix.internalMap.end()) {
                return it->second;
            } else {
                return Default;
            }
        }
    };

    ColumnRef operator[](std::size_t index) {
        return ColumnRef(*this, index);
    }

    ConstColumnRef operator[](std::size_t index) const {
        return ConstColumnRef(*this, index);
    }

private:
    using internal_container = std::unordered_map<std::pair<std::size_t, std::size_t>, T, hash_pair>;

    internal_container internalMap;
public:
    using iterator = typename internal_container::iterator;
    using const_iterator = typename internal_container::const_iterator;

    iterator begin() {
        return internalMap.begin();
    }

    iterator end() {
        return internalMap.end();
    }

    const_iterator cbegin() const {
        return Iterator(internalMap.cbegin());
    }

    const_iterator cend() {
        return Iterator(internalMap.cend());
    }
};

