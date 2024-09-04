#include <iostream>
#include "client.h"

constexpr size_t DATA_SIZE = sizeof(float);

void AsyncServer::set_options()
{
    acceptor_.set_option(asio::socket_base::reuse_address(true));
}

void AsyncServer::start_accept()
{
    std::cerr << "start_accept\n"; 
    acceptor_.async_accept(socket_,
        [this](const asio::error_code& error) {
            if (!error) {
                handle_accept();
            }
            else {
                std::cerr << "Error accepting data: " << error.message() << std::endl;
            }
            //socket_.close();
            //start_accept(); // Continue accepting new connections
        });
}

void AsyncServer::handle_accept()
{
    std::cout << "New connection established" << std::endl;

    // Start reading the integer and ten floats (4 bytes for int, 40 bytes for floats)
    asio::async_read(socket_, asio::buffer(receive_buffer),
        [&](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                handle_read(bytes_transferred);
            } else {
                std::cerr << "Error reading data: " << error.message() << std::endl;
            }
        });
}

void AsyncServer::handle_read(std::size_t bytes_transferred)
{
   if (bytes_transferred == sizeof(float)) {
        // Convert the received bytes into a float
        float received_value;
        std::memcpy(&received_value, receive_buffer.data(), sizeof(float));

        std::cout << "Received float value: " << received_value << std::endl;
    } else {
        std::cerr << "Received unexpected number of bytes: " << bytes_transferred << std::endl;
    }

    // Clear the buffer and continue reading from the client
    std::fill(receive_buffer.begin(), receive_buffer.end(), 0);
    handle_accept();
}

DataClient::DataClient()
{
    server.set_options();
    std::cerr << "Server started. Waiting for incoming connections..." << std::endl;
    try {
        // Run the io_context in a detached thread
        std::thread io_thread([this]() {
            this->io_context.run();
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
