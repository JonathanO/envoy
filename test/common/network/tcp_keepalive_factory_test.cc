#include "common/network/address_impl.h"
#include "common/network/socket_option_impl.h"
#include "common/network/tcp_keepalive_factory.h"

#include "test/mocks/api/mocks.h"
#include "test/mocks/network/mocks.h"
#include "test/test_common/threadsafe_singleton_injector.h"

#include "gtest/gtest.h"

using testing::Invoke;
using testing::NiceMock;
using testing::Return;
using testing::_;

namespace Envoy {
namespace Network {
namespace {

class TcpKeepaliveFactoryTest : public testing::Test {
public:
  TcpKeepaliveFactoryTest() { socket_.local_address_.reset(); }

  NiceMock<MockListenSocket> socket_;
  Api::MockOsSysCalls os_sys_calls_;
  TestThreadsafeSingletonInjector<Api::OsSysCallsImpl> os_calls{&os_sys_calls_};
};

TEST_F(TcpKeepaliveFactoryTest, EnableWithProbes) {
  if (ENVOY_SOCKET_SO_KEEPALIVE.has_value()) {
    Network::TcpKeepaliveConfig config = Network::TcpKeepaliveConfig{{1}, {}, {}};

    Network::ConnectionSocket::OptionsSharedPtr cluster_options =
        std::make_shared<Network::ConnectionSocket::Options>();
    Network::TcpKeepaliveFactory::appendKeepaliveOptions(config, cluster_options);
  }
}

} // namespace
} // namespace Network
} // namespace Envoy
