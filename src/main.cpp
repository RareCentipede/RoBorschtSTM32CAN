#include <Arduino.h>
#include "CAN_msg_formatter.h"

struct CAN_id{
  unsigned int id: 11;
};

static CAN_message_t CAN_TX_msg;
static CAN_message_t EnableOperation_msg;
static CAN_message_t start_msg;
static CAN_message_t CAN_RX_msg;
static CAN_message_t shutdown_msg;
static CAN_message_t switch_on_msg;
static CAN_message_t enable_operation_msg;
static CAN_message_t set_pp_mode_msg;
static CAN_message_t setpoint_msg;
static CAN_message_t start_movement_msg;
static CAN_message_t setzero_msg;
static CAN_message_t reset_bit_msg;

STM32_CAN Can(CAN1, DEF);  //Use PA11/12 pins for CAN1.
CAN_msg_formatter formatter;

void setup() {
  // Begin serial and CAN
    Serial.begin(115200);
    Serial.flush();
    Can.begin();
    Can.setBaudRate(50000);  //1000KBPS

  // Send start message to move the nodes from pre-opertation to operational state
    uint32_t id = 0x01;
  
    // ----------------- Create messages ----------------- //
    start_msg = formatter.create_start_node_sdo_msg(id);
    shutdown_msg = formatter.create_shutdown_sdo_msg(id);
    switch_on_msg = formatter.create_switch_on_sdo_msg(id);
    enable_operation_msg = formatter.create_enable_operation_sdo_msg(id);
    set_pp_mode_msg = formatter.create_set_PP_mode_sdo_msg(id);
    setpoint_msg = formatter.create_setpoint_sdo_msg(id, 12000);
    start_movement_msg = formatter.create_start_movement_sdo_msg(id);
    setzero_msg = formatter.create_setpoint_sdo_msg(id, 0);
    reset_bit_msg = formatter.create_reset_bit_sdo_msg(id);
}

void loop() {
  // Enable operation and send setpoint
  // ----------------- Send messages ----------------- //
  // Order of messages is important
  // ----------------- State Control ----------------- //
  // To start and enable the drive: Start message -> Shutdown message -> Switch on message -> Enable operation message
  // If LED on the controller is blinking, then the node is in pre-operational state
  // If LED on the controller is constantly on, then the node is in operational state
  // If the message sent is red in PicoScope, then the message has failed to send
  if (Serial.available()){
    char c = Serial.read();
    if (c == 's'){
      Can.write(start_msg);
    }
    else if (c == 'd'){
      Can.write(shutdown_msg);
    }
    else if (c == 'o'){
      Can.write(switch_on_msg);
    }
    else if (c == 'e'){
      Can.write(enable_operation_msg);
    }
    // ----------------- Position Control ----------------- //
    // Send once: set_pp_mode_msg
    // To send setpoint: setpoint_msg -> start_movement_msg
    // To send another one: reset_bit_msg -> new setpoint_msg -> start_movement_msg
    else if (c == 'p'){
      Can.write(set_pp_mode_msg);
    }
    else if (c == 't'){
      Can.write(setpoint_msg);
    }
    else if (c == 'm'){
      Can.write(start_movement_msg);
    }
    else if (c == 'z'){
      Can.write(setzero_msg);
    }
    else if (c == 'r'){
      Can.write(reset_bit_msg);
    }
  }

  if (Can.read(CAN_RX_msg)) {
    Serial.println("CAN message received");
    Serial.print("ID: ");
    Serial.println(CAN_RX_msg.id, HEX);
    Serial.print("Data: ");
    for (int i = 0; i < CAN_RX_msg.len; i++){
      Serial.print(CAN_RX_msg.buf[i], HEX);
      Serial.print(" ");
    }
  }
}