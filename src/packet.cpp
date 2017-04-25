#include "mcstatus/packet.hpp"

#include <string>
#include <cassert>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace
{

unsigned char convert(const std::string& s)
{
    unsigned char x;
    sscanf(s.c_str(), "%hhx", &x);
    return x;
}

} // namespace 

namespace mc
{

packet_builder::packet_builder()
{
}

packet_builder::packet_builder(const std::string& packets)
{
    from_string(packets);
}

packet_builder::packet_builder(const char* packets)
{
    from_string(packets);
}

packet_builder::~packet_builder()
{
}

packet_builder packet_builder::from_string(const std::string& packets)
{
    assert((packets.size() >= 2));

    packet_t buffer;

    if (packets.size() != 2)
    {
        std::vector<std::string> packets_split;
        boost::split(packets_split, packets, boost::is_any_of(" "));

        for (auto&& x : packets_split)
            buffer.push_back(convert(x));
    } else
    {
        buffer.push_back(convert(packets));
    }

    packet_builder packet_new;
    packet_new.m_packet = std::deque<unsigned char>(buffer.begin(), buffer.end());

    return packet_new;
}


void packet_builder::write_int8(int8_t v)
{
    m_packet.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_uint8(uint8_t v)
{
    m_packet.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_int16(int16_t v)
{
    uint8_t l = static_cast<uint8_t>(v & 0x00FF);
    uint8_t h = static_cast<uint8_t>((v & 0xFF00) >> 8);

    m_packet.push_back(h); // higt
    m_packet.push_back(l); // low

}
void packet_builder::write_uint16(uint16_t v)
{
    uint8_t l = static_cast<uint8_t>(v & 0x00FF);
    uint8_t h = static_cast<uint8_t>((v & 0xFF00) >> 8);

    m_packet.push_back(h); // higt
    m_packet.push_back(l); // low
}

void packet_builder::write_int32(int32_t v)
{
    m_packet.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_int64(int64_t v)
{
    auto buff = new unsigned char[8];
    int point=56;
    for(int i=7;i>=0;i--)
    {
        long long tmp = v<<point;
        buff[i] = tmp >> 56;
        point-=8;
    }
    for (int i = 0; i < 7; i++)
        m_packet.push_back(buff[i]);
}

void packet_builder::write_varint32(int32_t v)
{
    while (v > 127)
    {
        m_packet.push_back(static_cast<unsigned char>(v & 127) | 128);
        v >>= 7;
    }
    m_packet.push_back(static_cast<unsigned char>(v & 127));
}

void packet_builder::write_varint64(int64_t v)
{
    while (v > 127)
    {
        m_packet.push_back(static_cast<unsigned char>(v & 127) | 128);
        v >>= 7;
    }
    m_packet.push_back(static_cast<unsigned char>(v & 127));
}

void packet_builder::write_float(float v)
{
    m_packet.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_double(double v)
{
    m_packet.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_bool(bool v)
{
    m_packet.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_string(const std::string& v)
{
    assert(!v.empty());

    write_varint32(v.size());
    for (auto&& x : v) m_packet.push_back(x);
}

void packet_builder::clear()
{
    m_packet.clear();
}

packet_t packet_builder::completePacket(int packetID)
{
    m_packet.push_front(static_cast<unsigned char>(packetID));
    m_packet.push_front(static_cast<unsigned char>(m_packet.size())); // FIXME: use varint instead of unsigned char (ugly LOL
    
    return packet_t(m_packet.begin(), m_packet.end());
}

packet_t packet_builder::toRawPacket()
{
    return packet_t(m_packet.begin(), m_packet.end());
}

} // namespace mc
