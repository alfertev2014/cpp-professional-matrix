#pragma once

#include <cstdint>
#include <functional>

inline std::size_t hash_combine(std::size_t lhs, std::size_t rhs) {
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2); // snatched from boost
    return lhs;
}

struct hash_pair {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        return hash_combine(hash1, hash2);
    }
};
