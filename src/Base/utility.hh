#include <stdexcept>

#ifndef UTILITY_H
#define UTILITY_H

#define UNCOPYABLE(T) \
    T(T&) = delete; \
    T(T&&) = delete; \
    T& operator=(T&) = delete; \
    T& operator=(T&&) = delete;

#define CRTP_METHOD_DEFINE(R, NAME, T) \
    R NAME() {\
        return static_cast<T*>(this)->NAME##Impl(); \
    }

struct Undefined {
    Undefined() { throw std::runtime_error("Undefined"); }
};

#endif /* UTILITY_H */
