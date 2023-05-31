#include <concepts>
#include <variant>
#include "Base/utility.hh"

#ifndef NETWORK_H
#define NETWORK_H

namespace Octopus {
namespace Network {

enum NetworkStat {};

template<typename T>
concept NetworkImpl = requires(T a) {
    { a.asCoordinatorImpl() } -> std::convertible_to<NetworkStat>;
    { a.asTerminalImpl() } -> std::convertible_to<NetworkStat>;
};

/* An abstraction that represent networks for specific purposes,
 * e.g. monitor network or executor network. Implementations of |Network| should
 * obey following rules:
 *   Each node of |Network| must be able to communicate directly with
 *   each of another nodes within |Network|. */
template<NetworkImpl T>
class Network {
public:
    #define NetworkInterfaces(V) \
        V(NetworkStat, asCoordinator, T) \
        V(NetworkStat, asTerminal, T) \
    NetworkInterfaces(CRTP_METHOD_DEFINE)
    #undef NetworkInterfaces
protected:
    Network() = default;
private:
    UNCOPYABLE(Network);
};

} // Network
} // Octopus

#endif /* NETWORK_H */
