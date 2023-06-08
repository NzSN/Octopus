
#ifndef TERMINAL_H
#define TERMINAL_H

#include <concepts>
#include <variant>
#include "Base/utility.hh"

namespace Octopus {
namespace Network {

template<typename T>
concept NetworkTerminalIFace = requires(T t) {
    { t.send() } -> std::same_as<size_t>;
    { t.recv() } -> std::same_as<size_t>; };

class NetworkTerminalBase {
public:

protected:
    NetworkTerminalBase() = default;
};

using NetworkTerminal = std::variant<ImplPending>;

}
}


#endif /* TERMINAL_H */
