#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include <string.h>

#include "lis2dh12_reg.h"
#include "driver/spi_master.h"

int32_t accel_init();
int32_t accel_read_polling(float *acc);
int32_t platform_write(void *handle, uint8_t Reg, const uint8_t *Bufp, uint16_t len);
int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp, uint16_t len);

#endif