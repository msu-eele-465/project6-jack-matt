#ifndef I2CMASTER
#define I2CMASTER

void i2c_master_init();

void i2c_master_transmit(int address, char* packet, int size);

void i2c_master_recieve(int address, char reg_addr[1], int size, char* return_data);

#endif // HEARTBEAT_H#include "intrinsics.h"