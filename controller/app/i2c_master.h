#ifndef I2CMASTER
#define I2CMASTER

void i2c_master_init();

void i2c_master_transmit(int address, char* packet, int size);

#endif // HEARTBEAT_H#include "intrinsics.h"