#include <concepts>
#include <memory>
#include <gtest/gtest.h>
#include "Base/Network/network.h"

namespace Octopus {
namespace Network {

struct TestTerminal {
  bool send(std::string m);
  std::string recv();
};

struct TestNetworkDelegate: public Network<TestTerminal>::Delegate {
  std::unique_ptr<TestTerminal> GetTerminal() final {
    return std::make_unique<TestTerminal>();
  };
};


struct GenericNetworkTest: ::testing::Test {
  void SetUp() override {
    network = Network<TestTerminal>::Create(
      std::make_unique<TestNetworkDelegate>());
  }

  void TearDown() override {}

  std::unique_ptr<Network<TestTerminal>> network;
};


TEST_F(GenericNetworkTest, Default) {


}

}
}
