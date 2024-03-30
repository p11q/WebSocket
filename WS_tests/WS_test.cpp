#include <catch2/catch_all.hpp>
#include "ws_protocol.hpp"

class Packet_test: public Packet{
public:
    uint8_t get_fin() const {
        return m_fin;
    }

    uint8_t get_opcode() const {
        return m_opcode;
    }

    uint8_t get_mask() const {
        return m_mask;
    }

    uint8_t get_payload_len() const {
        return m_payload_len;
    }

};
TEST_CASE("Packet from bytes array", "[WSProtocol][Packet][Ctor]") {

    SECTION("hello") {
        unsigned char packet_bytes[] = {0x81, 0x86,
                                        0x58, 0x6e, 0x24, 0xaf,
                                        0x30, 0x0b, 0x48, 0xc3, 0x37, 0x64};
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 6);
    }

    SECTION("zero bytes") {
        unsigned char packet_bytes[] = {0x00, 0x00};
        Packet_test packet{packet_bytes};
    }

    SECTION("empty bytes") {
        unsigned char packet_bytes[] = {};
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 6);

    }
}