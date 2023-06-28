#include <string>
#include <stdexcept>
#include <concepts>

#ifndef UTILITY_H
#define UTILITY_H

#define UNCOPYABLE(T) \
    T(T&) = delete; \
    T(T&&) = delete; \
    T& operator=(T&) = delete; \
    T& operator=(T&&) = delete;

#define CRTP_METHOD_DEFINE(T, R, NAME, args...) \
    R NAME(args) {\
        return static_cast<T*>(this)->NAME(args); \
    }

struct Bottom { Bottom(std::string s) { throw std::runtime_error(s); }};
struct Undefined: public Bottom {
    Undefined(): Bottom("Undefined...") {}
};
struct ImplPending: public Bottom {
    ImplPending(): Bottom("Pending to implement...") {}
};

template<typename T>
concept SerializableT = requires(T t) {
    { t.serialize() } -> std::same_as<std::string>;
};

#endif /* UTILITY_H */
