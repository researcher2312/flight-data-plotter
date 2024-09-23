#pragma once

#include "data_storage.h"
#include <thread>
#include <asio.hpp>

using asio::ip::udp;

constexpr size_t DATA_NUM = 11;
constexpr size_t DATA_SIZE = DATA_NUM * sizeof(float);

class AsyncServer {
public:
    AsyncServer(asio::io_context& io_context, short port):
        socket_(io_context, udp::endpoint(udp::v4(), port))
        {do_receive();}

    DataStorage* data_storage;
    void do_receive();
    void handle_read();

private:
    udp::socket socket_;
    std::array<char, DATA_SIZE> data_;
};

class DataClient {
public:
    DataClient(DataStorage*);
    ~DataClient();
private:
    asio::io_context io_context;
    AsyncServer server {io_context, 1234};
};
