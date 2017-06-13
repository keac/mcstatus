#include "mcstatus/domain.hpp"

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

namespace mc
{

domain::domain(const std::string& hostname,
            const unsigned short port,
            boost::system::error_code& ec) :
    m_hostname(hostname),
    m_port(std::to_string(port)),
    m_ec(&ec)
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

    auto iter = resolver.resolve(query, *m_ec);
    return iter->endpoint();
}

} // namespace mc
