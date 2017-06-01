#ifndef JINGJING_PACKET_HPP
#define JINGJING_PACKET_HPP

#include <string>
#include <vector>
#include <deque>

namespace mc
{

using packet_t = std::vector<unsigned char>;

class packet_builder
{
public:
    packet_builder();
    packet_builder(const std::string& packets);
    packet_builder(const char* packets);
    ~packet_builder();
    void write_int8(int8_t v);
    void write_uint8(uint8_t v);
    void write_int16(int16_t v);
    void write_uint16(uint16_t v);
    void write_int32(int32_t v);
    void write_int64(int64_t v);
    void write_varint32(int32_t v);
    void write_varint64(int64_t v);
    void write_float(float v);
    void write_double(double v);
    void write_bool(bool v);
    void write_string(const std::string& v);
    void clear();
    size_t lenght() const;
    packet_t completePacket(int packetID);
    packet_t toRawPacket();

public:
    static packet_builder from_string(const std::string& packets);

protected:
    std::deque<unsigned char> m_packet;
    size_t lenght_; // lenght of completed packet
};

} // namespace mc

#endif // !JINGJING_PACKET_HPP
