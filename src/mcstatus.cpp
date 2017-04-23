#include "mcstatus/mcstatus.hpp"
#include "mcstatus/packet.hpp"

#include <string>
#include <cstdint>
#include <iostream>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>

namespace mc
{

status::status(const std::string& ipv4,
               uint16_t port) :
    ep(boost::asio::ip::address::from_string(ipv4), port),
    sock(service)
{
    reMotd();
}

status::~status()
{
    sock.shutdown(boost::asio::socket_base::shutdown_both);
    sock.close();
}

int status::unpack_varint()
{
    int d = 0;
    for (int i = 0; i < 5; i++)
    {
        uint8_t b[1] = {0x00};
        sock.read_some(boost::asio::buffer(b, 1));
        d |= (b[0] & 0x7F) << 7*i;
        if (!(b[0] & 0x80))
            break;
    }

    return d;
}

void status::json2status(const std::string& json)
{
    using namespace boost::property_tree;

    std::stringstream ss(json);
    ptree pt;
    try
    {
        read_json(ss, pt);
    }
    catch(ptree_error &e)
    {
        std::clog << e.what() << std::endl;
        exit(1);
    }

    // get description(main motd)
    m_motd.description = pt.get<std::string>("description");
    if (m_motd.description.empty())
    {
        for (auto& description : pt.get_child("description"))
            m_motd.description = description.second.get_value<std::string>();
    }


    // get online and player max
    std::vector<std::string> players_array;
    for (auto& players : pt.get_child("players"))
        players_array.push_back(players.second.get_value<std::string>());

    m_motd.player_max = std::stoi(players_array[0]);
    m_motd.player_online = std::stoi(players_array[1]);
}

motd_t status::getMotd()
{
    return m_motd;
}

void status::reMotd()
{
    try
    {
        sock.open(boost::asio::ip::tcp::v4());
        sock.connect(ep);
    }
    catch (...)
    {
        std::cout << "Can not connect to server :(" << std::endl;
    }

    mc::packet_builder p;
    p.write_varint32(316); // Version number
    p.write_string(sock.remote_endpoint().address().to_string()); // Server IP
    p.write_uint16(sock.remote_endpoint().port()); // port
    p.write_varint32(1); // status

    sock.write_some(boost::asio::buffer(p.completePacket(0))); // Send a handshake
    sock.write_some(boost::asio::buffer(mc::packet_builder().completePacket(0))); // Request the motd
    
    unpack_varint();
    unpack_varint();
    int l = unpack_varint();

    std::string json;
    while (json.size() < l)
    {
        // Do not use buff[1024]
        unsigned char buff[1] = {0x00}; 
        sock.read_some(boost::asio::buffer(buff, 1));
        json += reinterpret_cast<char*>(&buff[0]);
    }

    json2status(json);
    
}

} // namespace mc
