#pragma once

#include <thread>
#include <asio.hpp>

using asio::ip::tcp;


class AsyncServer {
public:
    AsyncServer(asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
          socket_(io_context) {start_accept();}
    void start_accept();
    void handle_accept();
    void handle_read(std::size_t bytes_transferred);
    void set_options();

private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::array<char, sizeof(float)> receive_buffer;
};

class DataClient {
public:
    DataClient();
    ~DataClient();
private:
    asio::io_context io_context;
    AsyncServer server {io_context, 1234};
};
