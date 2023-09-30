/*
 * Generic functions to hash arbitrary data types.
 *
 * Hash functions must provide an implementation of the call operator to calculate the hash of the argument
 */

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_HASHER_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_HASHER_HPP

#include <cstddef>
#include <functional>

class Hasher
{
public:
    template<typename T>
    std::size_t operator()(const T& key) const noexcept
    {
        return std::hash<T>{}(key);
    }
};

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_HASHER_HPP
