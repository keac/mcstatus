#ifndef JINGJING_DOMAIN_HPP
#define JINGJING_DOMAIN_HPP

#include <string>

#include <boost/asio.hpp>

namespace mc
{
class domain
{
public:
    domain(const std::string& hostname, const unsigned short port);
    ~domain();

    boost::asio::ip::tcp::endpoint domain2endpoint(void);

protected:
    std::string m_hostname;
    std::string m_port;

};
}

#endif // !JINGJING_DOMAIN_HPP
