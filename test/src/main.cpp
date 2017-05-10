#include <cassert>
#include <mcstatus/packet.hpp>

void test_packetbuilder()
{
    mc::packet_builder pb;
    pb.write_int32(23333);
    for (unsigned char x : pb.completePacket(0))
        printf("0x%x\n", x);
}

void runall()
{
    test_packetbuilder();
}

int main()
{
    runall();
}
