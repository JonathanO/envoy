#include "common/network/tcp_keepalive_factory.h"
#include "common/network/socket_option_impl.h"

#include "common/api/os_sys_calls_impl.h"
#include "common/network/address_impl.h"

namespace Envoy {
namespace Network {

const Network::ConnectionSocket::OptionsSharedPtr TcpKeepaliveFactory::appendKeepaliveOptions(Network::TcpKeepaliveConfig keepalive_config __attribute__((unused)), Network::ConnectionSocket::OptionsSharedPtr to) {
  return to;
}

}
}