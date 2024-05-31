#include "../include/CAN_msg_formatter.h"

CAN_message_t CAN_msg_formatter::create_start_node_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = 0x00;
    msg.len = start_node_dlc;
    msg.buf[0] = 0x01; // Node ID or 0 for all
    msg.buf[1] = 0x00; // CS
    return msg;
}

CAN_message_t CAN_msg_formatter::create_shutdown_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x2B; // CS
    msg.buf[1] = 0x40; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = 0x06; // LLB
    msg.buf[5] = 0x00; // LHB
    msg.buf[6] = 0x00; // HLB
    msg.buf[7] = 0x00; // HHB
    return msg;
}

CAN_message_t CAN_msg_formatter::create_switch_on_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x2B; // CS
    msg.buf[1] = 0x40; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = 0x07; // LLB
    msg.buf[5] = 0x00; // LHB
    msg.buf[6] = 0x00; // HLB
    msg.buf[7] = 0x00; // HHB
    return msg;
}

CAN_message_t CAN_msg_formatter::create_enable_operation_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x2B; // CS
    msg.buf[1] = 0x40; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = 0x0F; // LLB
    msg.buf[5] = 0x00; // LHB
    msg.buf[6] = 0x00; // HLB
    msg.buf[7] = 0x00; // HHB
    return msg;
}

CAN_message_t CAN_msg_formatter::create_set_PP_mode_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x2B; // CS
    msg.buf[1] = 0x60; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = 0x01; // LLB
    msg.buf[5] = 0x00; // LHB
    msg.buf[6] = 0x00; // HLB
    msg.buf[7] = 0x00; // HHB
    return msg;
}

CAN_message_t CAN_msg_formatter::create_setpoint_sdo_msg(uint32_t id, int32_t setpoint){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x23; // CS
    msg.buf[1] = 0x7A; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = setpoint & 0xFF; // LLB
    msg.buf[5] = (setpoint >> 8) & 0xFF; // LHB
    msg.buf[6] = (setpoint >> 16) & 0xFF; // HLB
    msg.buf[7] = (setpoint >> 24) & 0xFF; // HHB
    return msg;
}

CAN_message_t CAN_msg_formatter::create_start_movement_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x2B; // CS
    msg.buf[1] = 0x40; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = 0x1F; // LLB
    msg.buf[5] = 0x00; // LHB
    msg.buf[6] = 0x00; // HLB
    msg.buf[7] = 0x00; // HHB
    return msg;
}

CAN_message_t CAN_msg_formatter::create_reset_bit_sdo_msg(uint32_t id){
    CAN_message_t msg;
    msg.id = sdo_write_id + id;
    msg.len = 8;
    msg.buf[0] = 0x2B; // CS
    msg.buf[1] = 0x40; // Index LB
    msg.buf[2] = 0x60; // Index HB
    msg.buf[3] = 0x00; // Subindex
    msg.buf[4] = 0x0F; // LLB
    msg.buf[5] = 0x00; // LHB
    msg.buf[6] = 0x00; // HLB
    msg.buf[7] = 0x00; // HHB
    return msg;
}