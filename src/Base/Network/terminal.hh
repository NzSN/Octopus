
#ifndef TERMINAL_H
#define TERMINAL_H

#include <concepts>
#include <variant>
#include "Base/utility.hh"

namespace Octopus {
namespace Network {

template<typename T>
concept NetworkTerminalImpl = requires(T t) {
    { t.send() } -> std::same_as<size_t>;
    { t.recv() } -> std::same_as<size_t>; };

template<NetworkTerminalImpl T>
class NetworkTerminalBase {
public:
    #define NetworkInterfaces(V) \
        V(T, size_t, send) \
        V(T, size_t, recv)
    NetworkInterfaces(CRTP_METHOD_DEFINE)
    #undef NetworkInterfaces
protected:
    NetworkTerminalBase() = default;
private:
    UNCOPYABLE(NetworkTerminalBase);
};

using NetworkTerminal = std::variant<ImplPending>;

}
}


#endif /* TERMINAL_H */
