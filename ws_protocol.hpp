
#ifndef WEBSOCKET_WS_PROTOCOL_HPP
#define WEBSOCKET_WS_PROTOCOL_HPP

#include <vector>
#include <cstdint>
#include <cstring>
#include <netinet/ip.h>

class Packet {
public:
    uint8_t m_fin;
    uint8_t m_opcode;
    uint8_t m_mask;
    uint8_t m_payload_len;
    uint16_t m_payload_len_16;
    uint64_t m_payload_len_64;
    uint32_t m_masking_key;
    std::vector<uint8_t> m_payload;
public:
    Packet(const unsigned char *data) {
        m_fin = data[0] >> 7;
        m_opcode = data[0] & 0x0f;
        m_mask = data[1] >> 7;
        // TODO: throw exception if mask == 1
        m_payload_len = data[1] & 0x7f;

        if (m_payload_len == 126) {
            m_payload_len_16 = 0;
            memcpy(&m_payload_len_16, &data[2], 2);
            m_payload_len_16 = ntohs(m_payload_len_16);

            m_masking_key = 0;
            memcpy(&m_masking_key, &data[4], 4);
            m_masking_key = ntohl(m_masking_key);

            m_payload.resize(m_payload_len_16, 0);
            memcpy(m_payload.data(), &data[8], m_payload_len_16);
        }
        if (m_payload_len == 127) {
            m_payload_len_64 = 0;
            memcpy(&m_payload_len_64, &data[2], 8);
            m_payload_len_64 = ntohs(m_payload_len_64);

            m_masking_key = 0;
            memcpy(&m_masking_key, &data[10], 4);
            m_masking_key = ntohl(m_masking_key);

            m_payload.resize(m_payload_len_64, 0);
            memcpy(m_payload.data(), &data[14], m_payload_len_64);
        } else {
            m_masking_key = 0;
            memcpy(&m_masking_key, &data[2], 4);

            m_payload.resize(m_payload_len, 0);
            memcpy(m_payload.data(), &data[6], m_payload_len);
            apply_mask();
        }
    }

    void apply_mask() {
        if (m_payload_len < 126) {
            for (int i = 0; i < m_payload_len; ++i) {
                uint8_t curr_mask_byte = (m_masking_key & (0xFF << ((i % 4)*8))) >> i * 8;
                m_payload[i] = m_payload[i] ^ curr_mask_byte;
            }
        }
    }
};


#endif //WEBSOCKET_WS_PROTOCOL_HPP
