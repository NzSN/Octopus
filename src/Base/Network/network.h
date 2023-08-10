
#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <memory>
#include <vector>
#include <concepts>
#include <optional>
#include <variant>
#include "Base/utility.h"

#include "Base/Network/terminal.h"
#include "Base/Network/Message/Message.h"

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
template<Terminal N>
class Network {
public:
  struct Delegate {
    virtual std::unique_ptr<N> GetTerminal() = 0;
    virtual ~Delegate() {}
  };

  Network() = default;
  Network(std::unique_ptr<Delegate> const& net): delegate_(std::move(net)) {};

  static std::unique_ptr<Network> Create(std::unique_ptr<Delegate> const& impl) {
    std::unique_ptr<Network> net = std::make_unique<Network>(impl);
    net->stat_ = impl->Up() ? NetworkStat::UP : NetworkStat::DOWN;
    return net;
  }

  ~Network() { delegate_->Down(); }

  NetworkStat Stat() {
    return delegate_->IsUp() ? NetworkStat::UP : NetworkStat::DOWN;
  }

  bool IsCoordinator(N nt) {
    return coordinator_ != nullptr;
  }

  bool IsWorker(N nt) {
    return !IsCoordinator(nt);
  }

  /* There should only a unique Coordinator within a network. */
  std::optional<N&> AsCoordinator() {
    coordinator_ = delegate_->GetTerminal();
    return coordinator_;
  }

  /* Once a worker created it will broadcast to network to search
   * for the address of Coordinator. */
  std::optional<N&> AsWorker() {
    N entry = delegate_->GetTerminal();
    workers_.push_back(entry);

    return entry;
  }

  bool Up() {

    return true;
  }

  bool Down() {
    return false;
  }

private:
  std::unique_ptr<Delegate> delegate_;
  NetworkStat stat_;

  std::unique_ptr<N> coordinator_;
  std::vector<std::unique_ptr<N>> workers_;
};

} // Network
} // Octopus

#endif /* NETWORK_H */
