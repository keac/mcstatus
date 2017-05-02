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
    int d = 0; // 最终结果
    for (int i = 0; i < 5; i++) // 最多四个字节
    {
        uint8_t b[1] = {0x00};
        sock.read_some(boost::asio::buffer(b, 1));
        // b 是要解的varint

        d |= (b[0] & 0x7F) << 7*i; // i 是要操作的字节数
        if (!(b[0] & 0x80)) // 负数
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

    m_motd.description = pt.get<std::string>("description");
    m_motd.favicon = pt.get<std::string>("favicon");
    if (m_motd.description.empty())
    {
        for (const auto& description : pt.get_child("description"))
            m_motd.description = description.second.get_value<std::string>();
    }

    std::vector<std::string> players_array;
    for (const auto& players : pt.get_child("players"))
        players_array.push_back(players.second.get_value<std::string>());

    std::vector<std::string> versions_array;
    for (const auto& versions : pt.get_child("version"))
        versions_array.push_back(versions.second.get_value<std::string>());

    
    m_motd.kernel = versions_array.at(0);
    m_motd.protocol = std::stoi(versions_array.at(1));

    m_motd.player_max = std::stoi(players_array.at(0));
    m_motd.player_online = std::stoi(players_array.at(1));
}

motd_t status::getMotd()
{
    return m_motd;
}

void status::motd()
{
    mc::packet_builder p;
    p.write_varint32(316); // Version number
    p.write_string(sock.remote_endpoint().address().to_string()); // Server IP
    p.write_uint16(sock.remote_endpoint().port()); // port
    p.write_varint32(1); // status

    sock.write_some(boost::asio::buffer(p.completePacket(0))); // Send a handshake
    sock.write_some(boost::asio::buffer(mc::packet_builder().completePacket(0))); // Request the motd
    
    unpack_varint(); // lenght
    unpack_varint(); // packet id
    int l = unpack_varint(); // lenght of string(utf-8)

    std::string json;
    while (json.size() < l)
    {
        // Do not use buff[1024]
        unsigned char buff[1] = {0x00}; 
        sock.read_some(boost::asio::buffer(buff, 1));
        json += static_cast<char>(buff[0]);
    }

    json2status(json);
}

void status::ping()
{
    mc::packet_builder p;
    p.write_int64(233333);
    packet_t buffer = p.completePacket(1);
    sock.write_some(boost::asio::buffer(buffer));

    boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
    sock.read_some(boost::asio::buffer(buffer));
    boost::posix_time::ptime mst2 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration msdiff = mst2 - mst1;

    m_motd.ping = msdiff.total_milliseconds();
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
        exit(1);
    }

    motd();
    ping();
    
    
}

} // namespace mc
