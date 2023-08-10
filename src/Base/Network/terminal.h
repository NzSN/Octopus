
#ifndef TERMINAL_H
#define TERMINAL_H

#include <concepts>
#include <variant>
#include <string>

#include "Base/utility.h"

namespace Octopus {
namespace Network {

template<typename T>
concept NetworkTerminalT = requires(T t, std::string m) {
    { t.send(m) } -> std::same_as<bool>;
    { t.recv() } -> std::same_as<std::string>; };

using NetworkTerminal = std::variant<ImplPending>;

}
}


#endif /* TERMINAL_H */
