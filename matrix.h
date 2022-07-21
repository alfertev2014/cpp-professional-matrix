#pragma once

#include <cstdint>
#include <unordered_map>

#include "hashing.h"

template <typename T, T Default = T{}>
class Matrix {
private:
    using internal_key = std::pair<std::size_t, std::size_t>;
    using internal_container = std::unordered_map<internal_key, T, hash_pair>;

    internal_container internalMap;

    static T getElement(const internal_container map, const internal_key &key) {
        auto it = map.find(key);
        if (it != map.end()) {
            return it->second;
        } else {
            return Default;
        }
    }
public:
    Matrix() = default;

    class Cell {
        friend class Matrix;

        internal_container &map;
        const internal_key key;

        Cell(internal_container &map, const internal_key &key)
            : map(map), key(key) {}
    public:
        Cell(const Cell&) = delete;
        Cell(Cell&&) = delete;
        Cell &operator=(const Cell&) = delete;
        Cell &operator=(Cell&&) = delete;

        const Cell &operator=(const T& value) const {
            if (value == Default) {
                map.erase(key);
            } else {
                map[key] = value;
            }
            return *this;
        }

        // We cannot return const reference to an element
        // because it may be Default value
        operator T () {
            return getElement(map, key);
        }
    };

    class ConstCell {
        friend class Matrix;

        const internal_container &map;
        const internal_key key;

        ConstCell(const internal_container &map, const internal_key &key)
            : map(map), key(key) {}
    public:
        ConstCell(const ConstCell&) = delete;
        ConstCell(ConstCell&&) = delete;
        ConstCell &operator=(const Cell&) = delete;
        ConstCell &operator=(Cell&&) = delete;

        // We cannot return const reference to an element
        // because it may be Default value
        operator T () {
            return getElement(map, key);
        }
    };

    class ColumnRef {
        friend class Matrix;
        internal_container &map;
        const std::size_t index;

        ColumnRef(internal_container &matrix, std::size_t index) : map(matrix), index(index) {}
    public:
        ColumnRef(const ColumnRef&) = delete;
        ColumnRef(ColumnRef&&) = delete;
        ColumnRef &operator=(const ColumnRef&) = delete;
        ColumnRef &operator=(ColumnRef&&) = delete;

        Cell operator[](std::size_t rowIndex) const {
            return Cell( map, std::make_pair(index, rowIndex) );
        }
    };

    class ConstColumnRef {
        friend class Matrix;
        const internal_container &map;
        const std::size_t index;

        ConstColumnRef(const internal_container &matrix, std::size_t index) : map(matrix), index(index) {}
    public:

        ConstCell operator[](std::size_t rowIndex) const {
            return ConstCell( map, std::make_pair(index, rowIndex) );
        }
    };

    ColumnRef operator[](std::size_t index) {
        return ColumnRef(internalMap, index);
    }

    ConstColumnRef operator[](std::size_t index) const {
        return ConstColumnRef(internalMap, index);
    }

    using iterator = typename internal_container::iterator;
    using const_iterator = typename internal_container::const_iterator;


    std::size_t size() const { return internalMap.size(); }

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

