#include "common/network/tcp_keepalive_factory.h"
#include "common/network/socket_option_impl.h"

namespace Envoy {
namespace Network {

void TcpKeepaliveFactory::appendKeepaliveOptions(Network::TcpKeepaliveConfig keepalive_config, Network::ConnectionSocket::OptionsSharedPtr& to) {
  to->emplace_back(std::make_shared<Network::SocketOptionImpl>(Network::Socket::SocketState::PreBind, ENVOY_SOCKET_SO_KEEPALIVE, 1));

  if (keepalive_config.keepalive_probes_.has_value()) {
    to->emplace_back(std::make_shared<Network::SocketOptionImpl>(Network::Socket::SocketState::PreBind, ENVOY_SOCKET_TCP_KEEPCNT, keepalive_config.keepalive_probes_.value()));
  }
  if (keepalive_config.keepalive_interval_.has_value()) {
    to->emplace_back(std::make_shared<Network::SocketOptionImpl>(Network::Socket::SocketState::PreBind, ENVOY_SOCKET_TCP_KEEPINTVL, keepalive_config.keepalive_interval_.value()));
  }
  if (keepalive_config.keepalive_time_.has_value()) {
    to->emplace_back(std::make_shared<Network::SocketOptionImpl>(Network::Socket::SocketState::PreBind, ENVOY_SOCKET_TCP_KEEPIDLE, keepalive_config.keepalive_time_.value()));
  }
}

}
}