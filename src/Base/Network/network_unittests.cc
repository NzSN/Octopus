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
  bool Up() final { return true; };
  bool Down() final { return true; };
  bool IsUp() final { return true; }
  TestTerminal GetTerminal() final { return TestTerminal(); };
};


struct GenericNetworkTest: ::testing::Test {
  void SetUp() override {
    network = Network<TestTerminal>::Create(new TestNetworkDelegate());
  }

  void TearDown() override {}

  std::unique_ptr<Network<TestTerminal>> network;
};


TEST_F(GenericNetworkTest, Default) {
}

}
}
