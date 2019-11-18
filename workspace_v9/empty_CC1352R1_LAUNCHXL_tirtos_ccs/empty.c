/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/apps/Button.h>
#include <ti/drivers/I2C.h>
//#include "DHT-sensors-library-master/DHT.h"
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Driver configuration */
#include "ti_drivers_config.h"

void toggleLed0()
{
    GPIO_toggle(CONFIG_LED_0);
}

void toggleLed1()
{
    GPIO_toggle(CONFIG_LED_1);
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* 1 second delay */
    uint32_t time = 1;

    /* Call driver init functions */
    GPIO_init();
    Button_init();
    I2C_init();
    // SPI_init();
    // UART_init();
    // Watchdog_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    Button_Params params;

    Button_Params_init(&params);

    Button_open(CONFIG_BUTTON_0, toggleLed0, &params);
    Button_open(CONFIG_BUTTON_1, toggleLed1, &params);

    /* Configure the BUTTON pin */
//    GPIO_setConfig(CONFIG_BUTTON_0, GPIO_CFG_INPUT);
//    GPIO_setConfig(CONFIG_BUTTON_1, GPIO_CFG_INPUT);

    /* Turn on user LED */
    GPIO_write(CONFIG_LED_0, CONFIG_GPIO_LED_OFF);
    GPIO_write(CONFIG_LED_1, CONFIG_GPIO_LED_ON);
//    int btn = 0;

    I2C_Params i2c_params;
    I2C_Params_init(&i2c_params);
    i2c_params.bitRate = I2C_100kHz;

    // Open I2C bus for usage
    I2C_Handle i2cHandle = I2C_open(0, &i2c_params);

    // Initialize slave address of transaction
    I2C_Transaction transaction = {0};
    transaction.slaveAddress = 0x39;

    char * data = (char *) calloc(1, sizeof(char));

    // Read from I2C slave device
    transaction.readBuf = data;
    transaction.readCount = 1;
    transaction.writeCount = 0;
    I2C_transfer(i2cHandle, &transaction);


    while (1) {
//        sleep(time);
//        btn = GPIO_read(CONFIG_BUTTON_0) | GPIO_read(CONFIG_BUTTON_1);
//        if (!btn)
//            GPIO_toggle(CONFIG_LED_0);
//        if (btn)
//            GPIO_toggle(CONFIG_LED_1);
        I2C_transfer(i2cHandle, &transaction);
        sleep(2);
    }
}
