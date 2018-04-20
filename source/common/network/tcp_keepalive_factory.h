#pragma once

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#include "envoy/network/listen_socket.h"

#include "common/common/logger.h"

#include "absl/types/optional.h"

namespace Envoy {
namespace Network {

class TcpKeepaliveFactory : Logger::Loggable<Logger::Id::connection> {
 public:
  static void appendKeepaliveOptions(Network::TcpKeepaliveConfig keepalive_config,
                                           Network::ConnectionSocket::OptionsSharedPtr& to);
};
} // namespace Network
} // namespace Envoy
