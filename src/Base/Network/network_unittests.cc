#include <concepts>
#include <memory>
#include <gtest/gtest.h>
#include "Base/Network/network.hh"

namespace Octopus {
namespace Network {

struct GenericNetworkTest: ::testing::Test {
  void SetUp() override {
    new (&network) GenericNetwork();
  }

  void TearDown() override {}

  Network network;
};


TEST_F(GenericNetworkTest, Default) {

}

}
}
