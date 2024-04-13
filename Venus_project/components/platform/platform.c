#include <stdio.h>
#include "platform.h"

int32_t platform_write(void *handle, uint8_t Reg, const uint8_t *Bufp, uint16_t len) {
    spi_transaction_t t = {
        .tx_buffer = &Reg,
        .length = 1,
    };

    if (spi_device_polling_transmit(*(spi_device_handle_t*) handle, &t) != ESP_OK) {
        printf("failed reg write\n");
        return 1;
    }

    t.tx_buffer = Bufp;
    t.length = len;

    if (spi_device_polling_transmit(*(spi_device_handle_t*) handle, &t) != ESP_OK) {
        printf("failed data write\n");
        return 2;
    }
    
    return 0;
}

int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp, uint16_t len) {
    spi_transaction_t t = {
        .addr = Reg | 0x80,
        .rx_buffer = Bufp,
        .rxlength = 0,
        .length = 8 * len
    };

    if (spi_device_polling_transmit(*(spi_device_handle_t*) handle, &t) != ESP_OK) {
        printf("failed data read\n");
        return 1;
    }
    
    return 0;
}