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

    SECTION("empty bytes") {
        unsigned char packet_bytes[] = {};
        Packet_test packet{packet_bytes};
    }

    SECTION("zero bytes") {
        unsigned char packet_bytes[] = {0x00, 0x00};
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 0);
        CHECK(packet.get_opcode() == 0);
        CHECK(packet.get_mask() == 0);
        CHECK(packet.get_payload_len() == 0);
    }

    SECTION("hello") {
        unsigned char packet_bytes[] = {0x81, 0x86}; // fin, opcode, mask and payload len
                                        // Без Payload Data и  Masking-Key
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 6);
    }

    SECTION("LevelDB is a high-performance C++ key-value storage library developed by Google."
            "It provides an orderly mapping of string keys str.") {

        unsigned char packet_bytes[] = {0x81, 0xfe, 0x00, 0x83}; // fin, opcode, mask and payload len(126)
                                        // Без Payload Data и  Masking-Key
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 126);
    }

   SECTION("") {

        unsigned char packet_bytes[] = {0x81, 0xFF, 0x00, 0x83 /* +4 байта*/ }; // fin, opcode, mask and payload len(126)

        // Без Payload Data
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 127);
    }

}