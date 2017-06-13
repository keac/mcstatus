#ifndef JINGJING_DOMAIN_HPP
#define JINGJING_DOMAIN_HPP

#include <string>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

namespace mc
{
class domain
{
public:
    domain(const std::string& hostname,
           const unsigned short port,
           boost::system::error_code& ec);
    ~domain();

    boost::asio::ip::tcp::endpoint domain2endpoint(void);

protected:
    std::string m_hostname;
    std::string m_port;
    boost::system::error_code* m_ec;

};
}

#endif // !JINGJING_DOMAIN_HPP
