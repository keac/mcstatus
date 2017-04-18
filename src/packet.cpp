#include "mcstatus/packet.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

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

packet::packet(const std::string& packet)
{
    from_string(packet);
}

packet::packet()
{
}

packet::~packet()
{
    
}

void packet::setPacket(packet_t pt)
{
    packets = pt;
}

packet_t packet::getPacket() const
{
    return packets;
}

packet packet::from_string(const std::string& packets)
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

    packet packet_new;
    packet_new.setPacket(buffer);

    return packet_new;
}

// packet_builder

packet_builder::packet_builder()
{
}

packet_builder::~packet_builder()
{
}

void packet_builder::write_int8(int8_t v)
{
    //TODO: write int8
}

void packet_builder::write_uint8(uint8_t v)
{
    //TODO: write uint8
}

void packet_builder::write_int16(int16_t v)
{
    //TODO: write int16
}

void packet_builder::write_uint16(uint16_t v)
{
    //TODO: write uint16
}

void packet_builder::write_int32(int32_t v)
{
    //TODO: write int32
}

void packet_builder::write_int64(int64_t v)
{
    //TODO: write int64
}

void packet_builder::write_varint32(int32_t v)
{
    //TODO: write varint
}

void packet_builder::write_varint64(int64_t v)
{
    //TODO: write varlong
}

void packet_builder::write_float(float v)
{
    //TODO: write float
}

void packet_builder::write_double(double v)
{
    //TODO: write double
}

void packet_builder::write_bool(bool v)
{
    //TODO: write bool
}

void packet_builder::write_string(std::string& v)
{
    //TODO: write string
}

}