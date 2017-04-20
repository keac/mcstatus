#ifndef JINGJING_PACKET_HPP
#define JINGJING_PACKET_HPP

#include <string>
#include <vector>
#include <deque>

namespace mc
{

typedef std::vector<unsigned char> packet_t;

class packet
{
public:
    packet(const std::string& packets);
    packet();
    ~packet();

public:
    void setPacket(packet_t pt);
    packet_t getPacket() const;
    
    static packet from_string(const std::string& packets);
protected:
    packet_t packets;
}; // class packet

class packet_builder
{
public:
    packet_builder();
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
    packet_t completePacket(int packetID);

  protected:
    std::deque<unsigned char> m_packet;
};

} // namespace mc

#endif // !JINGJING_PACKET_HPP
