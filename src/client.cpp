#include <iostream>
#include "client.h"


void AsyncServer::start_accept()
{
    acceptor_.async_accept(socket_,
        [this](const asio::error_code& error) {
            if (!error) {
                handle_accept();
            }
            start_accept(); // Continue accepting new connections
        });
}

void AsyncServer::handle_accept()
{
    std::cout << "New connection established" << std::endl;

    // Start reading data from the client
    asio::async_read_until(socket_, receive_buffer_, '\n',
        [this](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                handle_read(bytes_transferred);
            } else {
                std::cerr << "Error reading data: " << error.message() << std::endl;
            }
        });
}

void AsyncServer::handle_read(std::size_t bytes_transferred)
{
    // Extract and print the received data
    std::istream is(&receive_buffer_);
    std::string message;
    std::getline(is, message);
    std::cout << "Received message: " << message << std::endl;

    // Echo the message back to the client (optional)
    asio::async_write(socket_, asio::buffer(message + "\n"),
        [](const asio::error_code& /*error*/, std::size_t /*bytes_transferred*/) {});
    
    // Clear the receive buffer for next message
    receive_buffer_.consume(bytes_transferred);

    // Continue reading data from the client
    handle_accept();
}

DataClient::DataClient()
{
    try {
        std::cout << "Server started. Waiting for incoming connections..." << std::endl;

        // Run the io_context in a detached thread
        std::thread io_thread([=]() {
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
