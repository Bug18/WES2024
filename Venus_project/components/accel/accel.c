#include <stdio.h>
#include "accel.h"

static stmdev_ctx_t ctx;
static spi_device_handle_t hdev;

int32_t accel_init() {
    /*
     spi_bus_config_t bus_config = {
        .miso_io_num = 19,
        .mosi_io_num = 23,
        .sclk_io_num = 18,
        .quadhd_io_num = -1,
        .quadwp_io_num = -1,
        .max_transfer_sz = 32
    };

    if (spi_bus_initialize(VSPI_HOST, &bus_config, SPI_DMA_DISABLED) != ESP_OK) {
        printf("neradi spi init\n");
        return 1;
    }
    */

    spi_device_interface_config_t device_config = {
        .clock_speed_hz = 1000000,
        .mode = 0,
        .spics_io_num = 13,
        .queue_size = 1,
        .flags = 0,
        .pre_cb = NULL,
        .post_cb = NULL,
        .address_bits = 8
    };
    
    if (spi_bus_add_device(VSPI_HOST, &device_config, &hdev) != ESP_OK) {
        printf("neradi spi bus add\n");
        return 2;
    }

    ctx.write_reg = platform_write,
    ctx.read_reg = platform_read,
    ctx.handle = &hdev;

    uint8_t who;
    lis2dh12_device_id_get(&ctx, &who);

    if (who != LIS2DH12_ID) {
        printf("neeeeeeeeeeeeeeee\n");
        return 3;
    }

    printf("Accel ID: %hhu\n", who);

    lis2dh12_block_data_update_set(&ctx, PROPERTY_ENABLE);
    lis2dh12_data_rate_set(&ctx, LIS2DH12_ODR_1Hz);
    lis2dh12_full_scale_set(&ctx, LIS2DH12_8g);
    lis2dh12_operating_mode_set(&ctx, LIS2DH12_HR_12bit);

    return 0;
}

int32_t accel_read_polling(float *acc) {
    int16_t data_raw_acceleration[3];

    lis2dh12_reg_t reg;
    if (lis2dh12_xl_data_ready_get(&ctx, &reg.byte) != 0) {
        printf("Accel read failed\n");
        return 1;
    }

    if (reg.byte) {
        memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
        lis2dh12_acceleration_raw_get(&ctx, data_raw_acceleration);
        acc[0] = lis2dh12_from_fs8_hr_to_mg(data_raw_acceleration[0]) / 1000.f;
        acc[1] = lis2dh12_from_fs8_hr_to_mg(data_raw_acceleration[1]) / 1000.f;
        acc[2] = lis2dh12_from_fs8_hr_to_mg(data_raw_acceleration[2]) / 1000.f;

        return 0;
    }
    else {
        return 2;
    }
}

int32_t platform_write(void *handle, uint8_t Reg, const uint8_t *Bufp, uint16_t len) {
    spi_transaction_t t = {
        .addr = Reg | 0x60,
        .tx_buffer = Bufp,
        .length = 8 * len
    };

    if (spi_device_polling_transmit(*(spi_device_handle_t*) handle, &t) != ESP_OK) {
        printf("failed reg write\n");
        return 1;
    }
    
    return 0;
}

int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp, uint16_t len) {
    spi_transaction_t t = {
        .addr = Reg | 0xC0,
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