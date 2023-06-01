#include <concepts>
#include <optional>
#include <variant>
#include "Base/utility.hh"

#ifndef NETWORK_H
#define NETWORK_H

namespace Octopus {
namespace Network {

enum NetworkStat {};

template<typename T>
concept NetworkTerminalImpl = requires(T t) {
    { t.send() } -> std::same_as<size_t>;
    { t.recv() } -> std::same_as<size_t>; };

template<NetworkTerminalImpl T>
class NetworkTerminalBase {
public:
    #define NetworkInterfaces(V) \
        V(size_t, send, T) \
        V(size_t, recv, T)
    NetworkInterfaces(CRTP_METHOD_DEFINE)
    #undef NetworkInterfaces
protected:
    NetworkTerminalBase() = default;
private:
    UNCOPYABLE(NetworkTerminalBase);
};

using NetworkTerminal = std::variant<Undefined>;


template<typename T>
concept NetworkImpl = requires(T t) {
    { t.asCoordinatorImpl() } -> std::same_as<std::optional<NetworkTerminal>>;
    { t.asTerminalImpl() } -> std::same_as<std::optional<NetworkTerminal>>;
};

/* An abstraction that represent networks for specific purposes,
 * e.g. monitor network or executor network. Implementations of |Network| should
 * obey following rules:
 *   Each node of |Network| must be able to communicate directly with
 *   each of another nodes within |Network|. */
template<NetworkImpl T>
class NetworkBase {
public:
    #define NetworkInterfaces(V) \
        V(std::optional<NetworkTerminal>, asCoordinator, T) \
        V(std::optional<NetworkTerminal>, asTerminal, T)
    NetworkInterfaces(CRTP_METHOD_DEFINE)
    #undef NetworkInterfaces
protected:
    NetworkBase() = default;
private:
    UNCOPYABLE(NetworkBase);
};

using Network = std::variant<Undefined>;


} // Network
} // Octopus

#endif /* NETWORK_H */
