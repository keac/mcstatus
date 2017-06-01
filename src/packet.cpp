#include "mcstatus/packet.hpp"

#include <string>
#include <cassert>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/endian/conversion.hpp>

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
    packet_new.packet_ = std::deque<unsigned char>(buffer.begin(), buffer.end());

    return packet_new;
}


void packet_builder::write_int8(int8_t v)
{
    packet_.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_uint8(uint8_t v)
{
    packet_.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_int16(int16_t v)
{
    std::vector<unsigned char> buffer; buffer.resize(sizeof(v));
    *reinterpret_cast<int*>(buffer.data()) = boost::endian::native_to_big<decltype(v)>(v);
    packet_.insert(packet_.end(), buffer.begin(), buffer.end());
}
void packet_builder::write_uint16(uint16_t v)
{
    std::vector<unsigned char> buffer; buffer.resize(sizeof(v));
    *reinterpret_cast<int*>(buffer.data()) = boost::endian::native_to_big<decltype(v)>(v);
    packet_.insert(packet_.end(), buffer.begin(), buffer.end());
}

void packet_builder::write_int32(int32_t v)
{
    std::vector<unsigned char> buffer; buffer.resize(sizeof(v));
    *reinterpret_cast<int*>(buffer.data()) = boost::endian::native_to_big<decltype(v)>(v);
    packet_.insert(packet_.end(), buffer.begin(), buffer.end());
}

void packet_builder::write_int64(int64_t v)
{
    std::vector<unsigned char> buffer; buffer.resize(sizeof(v));
    *reinterpret_cast<int*>(buffer.data()) = boost::endian::native_to_big<decltype(v)>(v);
    packet_.insert(packet_.end(), buffer.begin(), buffer.end());
}

void packet_builder::write_varint32(int32_t v)
{
    while (v > 127)
    {
        packet_.push_back(static_cast<unsigned char>(v & 127) | 128);
        v >>= 7;
    }
    packet_.push_back(static_cast<unsigned char>(v & 127));
}

void packet_builder::write_varint64(int64_t v)
{
    while (v > 127)
    {
        packet_.push_back(static_cast<unsigned char>(v & 127) | 128);
        v >>= 7;
    }
    packet_.push_back(static_cast<unsigned char>(v & 127));
}

void packet_builder::write_float(float v)
{
    std::vector<unsigned char> buffer; buffer.resize(sizeof(v));
    *reinterpret_cast<int*>(buffer.data()) = boost::endian::native_to_big<decltype(v)>(v);
    packet_.insert(packet_.end(), buffer.begin(), buffer.end());
}

void packet_builder::write_double(double v)
{
    std::vector<unsigned char> buffer; buffer.resize(sizeof(v));
    *reinterpret_cast<int*>(buffer.data()) = boost::endian::native_to_big<decltype(v)>(v);
    packet_.insert(packet_.end(), buffer.begin(), buffer.end());
}

void packet_builder::write_bool(bool v)
{
    packet_.push_back(static_cast<unsigned char>(v));
}

void packet_builder::write_string(const std::string& v)
{
    assert(!v.empty());

    write_varint32(v.size());
    for (auto&& x : v) packet_.push_back(x);
}

void packet_builder::clear()
{
    packet_.clear();
}

size_t packet_builder::lenght() const
{
    return lenght_;
}

packet_t packet_builder::completePacket(int packetID)
{
    packet_.push_front(static_cast<unsigned char>(packetID));
    packet_.push_front(static_cast<unsigned char>(packet_.size())); // FIXME: use varint instead of unsigned char (ugly LOL
    
    return packet_t(packet_.begin(), packet_.end());
}

packet_t packet_builder::toRawPacket()
{
    return packet_t(packet_.begin(), packet_.end());
}

} // namespace mc
