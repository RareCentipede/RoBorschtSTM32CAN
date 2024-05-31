#pragma once
#ifndef CAN_MSG_FORMATTER_H
#define CAN_MSG_FORMATTER_H

#include <vector>
#include <cstdint>
#include "STM32_CAN.h"

class CAN_msg_formatter {
    private:
        // Initialize all message templates
        // Service Data Object (SDO) message
        // Write OD entries
        // Format: 11-bit identifier, 8 bytes user data: CS, index LB, index HB, Subindex, LLB, LHB, HLB, HHB
        // Lower byte is the smaller numerical byte, not the left byte
        uint32_t sdo_write_id = 0x600;
        uint8_t sdo_write_dlc = 8;

        // Start remote-node
        uint32_t start_node_id = 0x00;
        uint8_t start_node_dlc = 2;

        // Shutdown message
        uint32_t shutdown_id = 0x200;
        uint8_t shutdown_dlc = 2;

        // Switch On message
        uint32_t switch_on_id = 0x200;
        uint8_t switch_on_dlc = 2;

        // Enable Operation message
        uint32_t enable_operation_id = 0x200;
        uint8_t enable_operation_dlc = 2;

    public:
        // Construct the messages
        CAN_message_t create_start_node_sdo_msg(uint32_t id);
        CAN_message_t create_shutdown_sdo_msg(uint32_t id);
        CAN_message_t create_switch_on_sdo_msg(uint32_t id);
        CAN_message_t create_enable_operation_sdo_msg(uint32_t id);
        CAN_message_t create_set_PP_mode_sdo_msg(uint32_t id);
        CAN_message_t create_setpoint_sdo_msg(uint32_t id, int32_t setpoint);
        CAN_message_t create_start_movement_sdo_msg(uint32_t id);
        CAN_message_t create_reset_bit_sdo_msg(uint32_t id);
};

#endif