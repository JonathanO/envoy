#include "common/network/address_impl.h"
#include "common/network/socket_option_impl.h"

#include "test/mocks/api/mocks.h"
#include "test/mocks/network/mocks.h"
#include "test/test_common/logging.h"
#include "test/test_common/threadsafe_singleton_injector.h"

#include "gtest/gtest.h"

using testing::Invoke;
using testing::NiceMock;
using testing::Return;
using testing::_;

namespace Envoy {
namespace Network {
namespace {

class SocketOptionImplTest : public testing::Test {
public:
  SocketOptionImplTest() { socket_.local_address_.reset(); }

  NiceMock<MockListenSocket> socket_;
  Api::MockOsSysCalls os_sys_calls_;
  TestThreadsafeSingletonInjector<Api::OsSysCallsImpl> os_calls{&os_sys_calls_};
};

TEST_F(SocketOptionImplTest, BadFd) {
  EXPECT_EQ(-1, SocketOptionImpl::setSocketOption(socket_, {}, 0));
  EXPECT_EQ(ENOTSUP, errno);
}

TEST_F(SocketOptionImplTest, SetOptionTransparentSuccessTrue) {
  SocketOptionImpl socket_option{Socket::SocketState::PreBind, Network::SocketOptionName(std::make_pair(5, 10)), 1};
  //const int fd = address.socket(Address::SocketType::Stream);
  //EXPECT_CALL(socket_, fd()).WillRepeatedly(Return(fd));
  EXPECT_CALL(os_sys_calls_,
              setsockopt_(_, 5, 10, _, sizeof(int)))
      .WillOnce(Invoke([](int, int, int, const void* optval, socklen_t) -> int {
        EXPECT_EQ(1, *static_cast<const int*>(optval));
        return 0;
      }));
  EXPECT_TRUE(socket_option.setOption(socket_, Socket::SocketState::PreBind));
}

} // namespace
} // namespace Network
} // namespace Envoy
