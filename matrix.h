#pragma once

#include <cstdint>
#include <unordered_map>

inline size_t hash_combine( size_t lhs, size_t rhs ) {
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2); // snatched from boost
    return lhs;
}

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        return hash_combine(hash1, hash2);
    }
};

template <typename T, T Default = T{}>
class Matrix {
public:
    Matrix() = default;

    std::size_t size() const { return internalMap.size(); }

    class ColumnRef {
        Matrix &matrix;
        const std::size_t index;
    public:
        ColumnRef(Matrix &matrix, std::size_t index) : matrix(matrix), index(index) {}
        T &operator[](std::size_t rowIndex) const {
            auto it = matrix.internalMap.find(std::make_pair(index, rowIndex));
            if (it == matrix.internalMap.end()) {
                it->second = Default;
            }
            return it->second;
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

    std::unordered_map<std::pair<std::size_t, std::size_t>, T, hash_pair> internalMap;
};

