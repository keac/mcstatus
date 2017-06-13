#ifndef JINGJING_MCSTATUS_HPP
#define JINGJING_MCSTATUS_HPP

#include <string>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/system/error_code.hpp>

namespace mc
{

typedef struct
{
    std::string description;
    std::string kernel;
    std::string favicon;
    unsigned int ping;
    unsigned int protocol;
    unsigned int players_max;
    unsigned int players_online;
}motd_t;

class status
{
public:

    status(const std::string& hostname,
           uint16_t port);
    status(const std::string& hostname,
           uint16_t port,
           boost::system::error_code& ec);

    ~status();
public:
    motd_t requestMotd();

private:
    void motd();
    void ping();
    int unpack_varint();
    void json2status(const std::string& json);

private:
    std::string ipv4;
    short port;
private:
    motd_t m_motd;
private:
    boost::system::error_code* ec_;
    boost::asio::io_service           service;
    boost::asio::ip::tcp::endpoint    ep;
    boost::asio::ip::tcp::socket      sock;
};

} // namespace mc

#endif // !JINGJING_MCSTATUS_HPP
