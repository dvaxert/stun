#include <boost/asio.hpp>  //! TODO  заменить на необходимые инклуды
#include <memory>

#include "stun/log_utils.h"
#include "stun/network/udp_client.h"

using namespace boost::asio;
using udp = ip::udp;
using socket_t = basic_stream_socket<udp>;

namespace stun {

class UdpClient::Pimpl {
 public:
  Pimpl();
  Pimpl(const std::string_view local_address, const uint16_t local_port);
  ~Pimpl();

  void Connect(const Endpoint& endpoint);
  void Disconnect();

  void Send(const std::vector<uint8_t>& raw_data);

  std::vector<uint8_t> Reseive(const uint64_t timeout_ms);

  udp::resolver::results_type ResolveHost(const Endpoint& endpoint);

  Endpoint RemoteEndpoint() const;
  Endpoint LocalEndpoint() const;

  bool Connected() const;

 private:
  io_context context_;
  socket_t socket_;
};

//------------------------------------------------------------------------------

UdpClient::Pimpl::Pimpl() : context_(), socket_(context_) {}

//------------------------------------------------------------------------------

UdpClient::Pimpl::Pimpl(const std::string_view local_address, const uint16_t local_port)
    : context_(), socket_(context_, udp::endpoint(ip::address::from_string(local_address.data()), local_port)) {}

//------------------------------------------------------------------------------

UdpClient::Pimpl::~Pimpl() {
  if (Connected()) {
    Disconnect();
  }
}

//------------------------------------------------------------------------------

void UdpClient::Pimpl::Connect(const Endpoint& endpoint) {
  if (Connected()) {
    Disconnect();
  }

  const auto endpoints = ResolveHost(endpoint);
  boost::asio::connect(socket_, endpoints);
}

//------------------------------------------------------------------------------

void UdpClient::Pimpl::Disconnect() {
  try {
    socket_.cancel();
    socket_.close();
  } catch (std::exception& ex) {
    LOG_ERROR(fmt::format("Error while close connection: {}", ex.what()));
  }
}

//------------------------------------------------------------------------------

udp::resolver::results_type UdpClient::Pimpl::ResolveHost(const Endpoint& endpoint) {
  boost::system::error_code error;
  auto res = udp::resolver(context_);

  std::string host, service;

  if (endpoint.host.index() == typeid(std::string).hash_code()) {
    host = std::get<std::string>(endpoint.host);
  } else {
    host = std::get<IpAddress>(endpoint.host).to_string();
  }

  if (endpoint.service.index() == typeid(std::string).hash_code()) {
    service = std::get<std::string>(endpoint.service);
  } else {
    service = std::to_string(std::get<uint16_t>(endpoint.host));
  }

  auto endpoints = res.resolve(socket_.local_endpoint().protocol(), host, service, error);

  if (error || endpoints.empty()) {
    throw std::runtime_error(fmt::format("Can`t resolve host {}. ", endpoint.ToString()) +
                             (error ? error.message() : ""));
  }

  return endpoints;
}

//------------------------------------------------------------------------------

Endpoint UdpClient::Pimpl::RemoteEndpoint() const {
  if (!Connected()) {
    return {};
  }

  Endpoint result{};
  auto remote_endpoint = socket_.remote_endpoint();
  result.host = remote_endpoint.address();
  result.service = remote_endpoint.port();
  return result;
}

//------------------------------------------------------------------------------

Endpoint UdpClient::Pimpl::LocalEndpoint() const {
  if (!Connected()) {
    return {};
  }

  Endpoint result{};
  auto local_endpoint = socket_.local_endpoint();
  result.host = local_endpoint.address();
  result.service = local_endpoint.port();
  return result;
}

//------------------------------------------------------------------------------

void UdpClient::Pimpl::Send(const std::vector<uint8_t>& raw_data) {
  if (!Connected()) {
    throw std::logic_error("No connection to the server");
  }

  socket_.send(buffer(raw_data.data(), raw_data.size()));
}

//------------------------------------------------------------------------------

std::vector<uint8_t> UdpClient::Pimpl::Reseive(const uint64_t timeout_ms) {
  std::array<uint8_t, 1024> buf{};
  boost::system::error_code error;
  uint64_t reseived_len = 0;

  if (!Connected()) {
    throw std::logic_error("No connection to the server");
  }

  LOG_INFO(fmt::format("Waiting for messages. Waiting timeout {}ms", timeout_ms));

  socket_.async_receive(buffer(buf.data(), buf.size()),
                        [&](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                          reseived_len = bytes_transferred;
                          error = ec;
                        });

  context_.restart();
  context_.run_for(std::chrono::milliseconds(timeout_ms));

  if (error && error.value() != error::operation_aborted) {
    throw std::runtime_error(fmt::format("Receive error: {}", error.message()));

  } else if (reseived_len == 0) {
    throw std::runtime_error("Reseived empty message");
  }

  return std::vector<uint8_t>(buf.begin(), buf.begin() + reseived_len);
}

//------------------------------------------------------------------------------

bool UdpClient::Pimpl::Connected() const { return socket_.is_open(); }

//------------------------------------------------------------------------------

UdpClient::UdpClient() : pimpl_(new Pimpl()) { TRACE_LOG(); }

//------------------------------------------------------------------------------

UdpClient::UdpClient(const std::string_view local_address, const uint16_t local_port)
    : pimpl_(new Pimpl(local_address, local_port)) {
  TRACE_LOG_P(local_address, local_port);
}

//------------------------------------------------------------------------------

UdpClient::~UdpClient() {}

//------------------------------------------------------------------------------

ProtocolType UdpClient::Type() const {
  TRACE_LOG();
  return ProtocolType::Udp;
}

//------------------------------------------------------------------------------

void UdpClient::Connect(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  pimpl_->Connect(Endpoint(host.data(), service.data()));
}

//------------------------------------------------------------------------------

void UdpClient::Connect(const std::string_view host, const uint16_t port) {
  TRACE_LOG_P(host, port);
  pimpl_->Connect(Endpoint(host.data(), port));
}

//------------------------------------------------------------------------------

void UdpClient::Connect(const IpAddress& address, const uint16_t port) {
  TRACE_LOG_P(address, port);
  pimpl_->Connect(Endpoint(address, port));
}

//------------------------------------------------------------------------------

void UdpClient::Connect(const Endpoint& endpoint) {
  TRACE_LOG_P(endpoint);
  pimpl_->Connect(endpoint);
}

//------------------------------------------------------------------------------

void UdpClient::Disconnect() {
  TRACE_LOG();
  pimpl_->Disconnect();
}

//------------------------------------------------------------------------------

std::vector<Endpoint> FromResolveResult(const udp::resolver::results_type& values) {
  if (values.empty()) {
    return {};
  }

  std::vector<Endpoint> result{};
  result.reserve(values.size());
  for (const auto& val : values) {
    result.emplace_back(Endpoint(val.host_name(), val.service_name()));
  }
  return result;
}

//------------------------------------------------------------------------------

std::vector<Endpoint> UdpClient::ResolveHost(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  return FromResolveResult(pimpl_->ResolveHost(Endpoint(host.data(), service.data())));
}

//------------------------------------------------------------------------------

std::vector<Endpoint> UdpClient::ResolveHost(const std::string_view host, const uint16_t port) {
  TRACE_LOG_P(host, port);
  return FromResolveResult(pimpl_->ResolveHost(Endpoint(host.data(), port)));
}

//------------------------------------------------------------------------------

std::vector<Endpoint> UdpClient::ResolveHost(const IpAddress& address, const uint16_t port) {
  TRACE_LOG_P(address, port);
  return FromResolveResult(pimpl_->ResolveHost(Endpoint(address, port)));
}

//------------------------------------------------------------------------------

std::vector<Endpoint> UdpClient::ResolveHost(const Endpoint& endpoint) {
  TRACE_LOG_P(endpoint);
  return FromResolveResult(pimpl_->ResolveHost(endpoint));
}

//------------------------------------------------------------------------------

bool UdpClient::CanResolveHost(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  return !pimpl_->ResolveHost(Endpoint(host.data(), service.data())).empty();
}

//------------------------------------------------------------------------------

bool UdpClient::CanResolveHost(const std::string_view host, const uint16_t port) {
  TRACE_LOG_P(host, port);
  return !pimpl_->ResolveHost(Endpoint(host.data(), port)).empty();
}

//------------------------------------------------------------------------------

bool UdpClient::CanResolveHost(const IpAddress& address, const uint16_t port) {
  TRACE_LOG_P(address, port);
  return !pimpl_->ResolveHost(Endpoint(address, port)).empty();
}

//------------------------------------------------------------------------------

bool UdpClient::CanResolveHost(const Endpoint& endpoint) {
  TRACE_LOG_P(endpoint);
  return !pimpl_->ResolveHost(endpoint).empty();
}

//------------------------------------------------------------------------------

void UdpClient::Send(const std::vector<uint8_t>& raw_data) {
  TRACE_LOG_P(raw_data.size());
  pimpl_->Send(raw_data);
}

//------------------------------------------------------------------------------

void UdpClient::Send(const std::string_view str) {
  TRACE_LOG_P(str);
  pimpl_->Send({str.begin(), str.end()});
}

//------------------------------------------------------------------------------

std::vector<uint8_t> UdpClient::Reseive(const uint64_t timeout_ms) {
  TRACE_LOG_P(timeout_ms);
  return pimpl_->Reseive(timeout_ms);
}

//------------------------------------------------------------------------------

Endpoint UdpClient::RemoteEndpoint() const {
  TRACE_LOG();
  return pimpl_->RemoteEndpoint();
}

//------------------------------------------------------------------------------

Endpoint UdpClient::LocalEndpoint() const {
  TRACE_LOG();
  return pimpl_->LocalEndpoint();
}

//------------------------------------------------------------------------------

bool UdpClient::Connected() const {
  TRACE_LOG();
  return pimpl_->Connected();
}

}  // namespace stun
