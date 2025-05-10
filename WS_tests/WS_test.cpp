#include <catch2/catch_all.hpp>
#include "ws_protocol.h"
#include "numeric"

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
    uint16_t get_payload_len_16() const {
        return m_payload_len_16;

    }
    uint64_t get_payload_len_64() const {
        return m_payload_len_64;

    }
    std::string get_payload() {
         std::vector<uint8_t> vec = m_payload;
         std::string str_payload{};
         for (int i = 0; i < vec.size() - 1; ++i) str_payload += vec[i];
         return str_payload;
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
        CHECK(packet.get_payload() == "hello");
    }

    SECTION("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890") {

        unsigned char packet_bytes[] = {0x81, 0xfe, 0x00, 0x83,
                                        0xfc, 0x0e, 0x51, 0xd0,
                                        0xcd, 0x3c, 0x62, 0xe4, 0xc9, 0x38, 0x66, 0xe8,
                                        0xc5, 0x3e, 0x60, 0xe2, 0xcf, 0x3a, 0x64, 0xe6,
                                        0xcb, 0x36, 0x68, 0xe0, 0xcd, 0x3c, 0x62, 0xe4,
                                        0xc9, 0x38, 0x66, 0xe8, 0xc5, 0x3e, 0x60, 0xe2,
                                        0xcf, 0x3a, 0x64, 0xe6, 0xcb, 0x36, 0x68, 0xe0,
                                        0xcd, 0x3c, 0x62, 0xe4, 0xc9, 0x38, 0x66, 0xe8,
                                        0xc5, 0x3e, 0x60, 0xe2, 0xcf, 0x3a, 0x64, 0xe6,
                                        0xcb, 0x36, 0x68, 0xe0, 0xcd, 0x3c, 0x62, 0xe4,
                                        0xc9, 0x38, 0x66, 0xe8, 0xc5, 0x3e, 0x60, 0xe2,
                                        0xcf, 0x3a, 0x64, 0xe6, 0xcb, 0x36, 0x68, 0xe0,
                                        0xcd, 0x3c, 0x62, 0xe4, 0xc9, 0x38, 0x66, 0xe8,
                                        0xc5, 0x3e, 0x60, 0xe2, 0xcf, 0x3a, 0x64, 0xe6,
                                        0xcb, 0x36, 0x68, 0xe0, 0xcd, 0x3c, 0x62, 0xe4,
                                        0xc9, 0x38, 0x66, 0xe8, 0xc5, 0x3e, 0x60, 0xe2,
                                        0xcf, 0x3a, 0x64, 0xe6, 0xcb, 0x36, 0x68, 0xe0,
                                        0xcd, 0x3c, 0x62, 0xe4, 0xc9, 0x38, 0x66, 0xe8,
                                        0xc5, 0x3e, 0x5b};

        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 126);
        CHECK(packet.get_payload_len_16() == 131);
        CHECK(packet.get_payload() == "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");

    }

   SECTION("Текст") {

        unsigned char packet_bytes[] = {0x81, 0xFF, 0x00, 0x83 /* +4 байта#1# */}; // fin, opcode, mask and payload len(126)
                                            // Без Payload Data
        Packet_test packet{packet_bytes};

        CHECK(packet.get_fin() == 1);
        CHECK(packet.get_opcode() == 1);
        CHECK(packet.get_mask() == 1);
        CHECK(packet.get_payload_len() == 127);
        CHECK(packet.get_payload_len_64() == 131);
    }

}
int q;
