
#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <concepts>
#include <optional>
#include <variant>
#include "Base/utility.hh"

#include "Base/Network/terminal.hh"

namespace Octopus {
namespace Network {

enum NetworkRole {
    ROLE_MINIMUM,
    COORDINATOR,
    WORKER,
    ROLE_COUNT,
};

enum NetworkStat {
    STAT_MINIMUM,
    UP,
    DOWN,
    STAT_COUNT,
};

/* An abstraction that represent networks for specific purposes,
 * e.g. monitor network or executor network. This abstraction only force all
 * it's implementation to involve two entities:
 *  1. Coordinator
 *  2. Worker */
template<NetworkTerminalIFace N>
class Network {
public:
    Network(N net): delegate_(net) {};

    static Network Create(N impl) {
        Network net {impl};
        net.stat_ = impl.Up() ? NetworkStat::UP : NetworkStat::DOWN;
        return net;
    }

    ~Network() { delegate_->Down(); }

    NetworkStat Stat() {
        return delegate_->IsUp() ? NetworkStat::UP : NetworkStat::DOWN;
    }

    bool IsCoordinator(NetworkTerminal nt) {
        return  coordinator_.has_value() ?
            nt == coordinator_ : false;
    }

    bool IsWorker(NetworkTerminal nt) {
        return !IsCoordinator(nt);
    }

    /* There should only a unique Coordinator within a network. */
    std::optional<NetworkTerminal> AsCoordinator() {
        coordinator_ = delegate_->GetTerminal();
    }

    /* Once a worker created it will broadcast to network to search
     * for the address of Coordinator. */
    std::optional<NetworkTerminal> AsWorker() {
        NetworkTerminal entry = delegate_->GetTerminal();

        workers_.push_back(entry);
    }

    bool Up() {

    }

    bool Down() {}

    class Delegate {
    public:

    };

private:
    Delegate delegate_;
    NetworkStat stat_;

    std::optional<NetworkTerminal> coordinator_;
    std::vector<NetworkTerminal> workers_;

};

} // Network
} // Octopus

#endif /* NETWORK_H */
