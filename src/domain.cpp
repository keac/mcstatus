#include "mcstatus/domain.hpp"

#include <iostream>
#include <string>

#include <boost/asio.hpp>

namespace mc
{

domain::domain(const std::string& hostname,
            const unsigned short port) :
    m_hostname(hostname),
    m_port(std::to_string(port))
{

}

domain::~domain()
{

}

boost::asio::ip::tcp::endpoint domain::domain2endpoint()
{
    boost::asio::io_service io;
    boost::asio::ip::tcp::resolver resolver(io);
    boost::asio::ip::tcp::resolver::query query(m_hostname, m_port);

    auto iter = resolver.resolve(query);
    return iter->endpoint();
}

}
