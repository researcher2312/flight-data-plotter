#include <iostream>
#include "data_storage.h"
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
    std::array<float, 3> acceleration;
    std::array<float, 3> rotation;
    std::array<float, 3> magnetic;
    float time_frame = 0;

    std::memcpy(&time_frame, data_.data(), sizeof(float));
    std::memcpy(acceleration.data(), data_.data()+1*sizeof(float), 3*sizeof(float));
    std::memcpy(rotation.data(), data_.data()+4*sizeof(float), 3*sizeof(float));
    std::memcpy(magnetic.data(), data_.data()+7*sizeof(float), 3*sizeof(float));

    data_storage->add_point(time_frame, acceleration, rotation, magnetic);

    std::fill(data_.begin(), data_.end(), 0);
}

DataClient::DataClient(DataStorage* data_storage)
{
    server.data_storage = data_storage;
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
