// This code was copied from the Boost docs on ASIO but then altered a bit using
// the Boost Context docs. Source:
// http://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/motivation.html
// The above didn't quite work, so it was merged with this:
// http://www.boost.org/doc/libs/1_57_0/doc/html/boost_asio/example/cpp11/spawn/echo_server.cpp
// So it's a mutt.

#include "precompiled_headers.hpp"

//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket & socket)
    : socket_(std::move(socket)) {
  }

  tcp::socket& socket() {
    return socket_;
  }

  void go(boost::asio::yield_context yield) {
    auto self(shared_from_this());
    const int max_length=1024;
    try{
        for(;;){
            // local data-buffer
            char data[max_length];

            boost::system::error_code ec;

            // read asynchronous data from socket
            // execution context will be suspended until
            // some bytes are read from socket
            std::size_t length=socket_.async_read_some(
                    boost::asio::buffer(data),
                    yield[ec]);
            if (ec==boost::asio::error::eof)
                break; //connection closed cleanly by peer
            else if(ec)
                throw boost::system::system_error(ec); //some other error

            // write some bytes asynchronously
            boost::asio::async_write(
                socket_,
                boost::asio::buffer(data,length),
                yield[ec]);
            if (ec==boost::asio::error::eof)
                break; //connection closed cleanly by peer
            else if(ec)
                throw boost::system::system_error(ec); //some other error
        }
    } catch(std::exception const& e){
        std::cerr<<"Exception: "<<e.what()<<"\n";
    }
  }

private:
  tcp::socket socket_;
};


class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      port_(port)
  {
  }

  void run(boost::asio::yield_context yield) {
      tcp::acceptor acceptor_(io_service_,
                              tcp::endpoint(tcp::v4(), port_));
      for (;;)
      {
        boost::system::error_code ec;
        tcp::socket socket(io_service_);
        acceptor_.async_accept(socket, yield[ec]);
        if (!ec) {
          auto s = std::make_shared<session>(std::move(socket));
          session * sp = s.get();
          auto pee = boost::bind(&session::go, sp, _1);
          boost::asio::spawn(io_service_, pee);
        }
      }
  }

private:
  boost::asio::io_service& io_service_;
  short port_;
};


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    using namespace std; // For atoi.
    server s(io_service, atoi(argv[1]));
    boost::asio::spawn(io_service, boost::bind(&server::run, s, _1));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
