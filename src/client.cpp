#include <iostream>
#include "client.h"


void AsyncServer::do_receive()
{
    socket_.async_receive(asio::buffer(data_, DATA_SIZE),
        [this](std::error_code ec, std::size_t bytes_received)
        {
            if (!ec && bytes_received > 0) {
                handle_read();
            } else {
                std::cerr << "Receive error" << ec.message() << '\n';
            }
            do_receive();

        }
    );
}

void AsyncServer::handle_read()
{
    float received_value;
    std::memcpy(&received_value, data_.data(), sizeof(float));

    std::cerr << "Received float value: " << received_value << std::endl;

    std::fill(data_.begin(), data_.end(), 0);
}

DataClient::DataClient()
{
    std::cerr << "Server started. Waiting for incoming connections..." << std::endl;
    try {
        std::thread io_thread([&]() {
            io_context.run();
        });
        io_thread.detach();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

DataClient::~DataClient()
{
    io_context.stop();
}
