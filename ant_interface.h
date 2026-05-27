#ifndef ANT_INTERFACE_H__
#define ANT_INTERFACE_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ANT-Kanaltypen
#define CHANNEL_TYPE_SLAVE              (0x00U)
#define CHANNEL_TYPE_MASTER             (0x10U)

// Kern-Funktionen des SoftDevices für den ANT-Funk
uint32_t sd_ant_channel_assign(uint8_t channel_number, uint8_t channel_type, uint8_t network_number, uint8_t ext_assign);
uint32_t sd_ant_channel_id_set(uint8_t channel_number, uint16_t device_number, uint8_t device_type, uint8_t transmission_type);
uint32_t sd_ant_channel_period_set(uint8_t channel_number, uint16_t channel_period);
uint32_t sd_ant_channel_radio_freq_set(uint8_t channel_number, uint8_t radio_freq);
uint32_t sd_ant_channel_open(uint8_t channel_number);
uint32_t sd_ant_broadcast_message_tx(uint8_t channel_number, uint8_t message_length, uint8_t * p_message_payload);

#ifdef __cplusplus
}
#endif

#endif // ANT_INTERFACE_H__
