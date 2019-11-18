/*
 * Copyright (c) 2018-2019, Texas Instruments Incorporated
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
 *  ======== i2ctmp116.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/display/Display.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#define TASKSTACKSIZE       640

/*
 *  ======== TMP Registers ========
 */
#define TMP006_REG          0xF3  /* Die Temp Result Register for TMP006 */

#define TMP006_ADDR         0x40
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    uint16_t        sample;
    uint16_t        temperature;
    uint16_t        humidity;
    uint8_t         txBuffer[1];
    uint8_t         rxBuffer[2];
    I2C_Handle      i2c;
    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction;

    /* Call driver init functions */
//    Display_init();
    GPIO_init();
    I2C_init();

    /* Configure the LED and if applicable, the TMP116_EN pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
#ifdef CONFIG_GPIO_TMP116_EN
    GPIO_setConfig(CONFIG_GPIO_TMP116_EN, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);
    /* 1.5 ms reset time for the TMP116 */
    sleep(1);
#endif

    /* Open the HOST display for output */
//    display = Display_open(Display_Type_UART, NULL);
//    if (display == NULL) {
//        while (1);
//    }

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
    /* Starting the i2ctmp example */

    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(CONFIG_I2C_TMP, &i2cParams);
    if (i2c == NULL) {
        /* Error Initializing I2C */
        while (1);
    }
    else {
        /* I2C Initialized! */
    }

    /* Common I2C transaction setup */
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf    = rxBuffer;
    i2cTransaction.readCount  = 2;

    /*
     * Determine which I2C sensor is present.
     * We will prefer sensors in this order: TMP116 (on BoosterPacks),
     * TMP116 (on-board CC32XX LaunchPads), and last TMP006
     * (on older CC32XX LaunchPads).
     */

    // get board id LSB
    txBuffer[0] = 0xFA;
    txBuffer[1] = 0x0F;
    i2cTransaction.slaveAddress = TMP006_ADDR;
    if (!I2C_transfer(i2c, &i2cTransaction)) {
        /* Could not resolve a sensor, error */
        while(1);
    }

    // get board id MSB
    txBuffer[0] = 0xFC;
    txBuffer[1] = 0xC9;
    if (!I2C_transfer(i2c, &i2cTransaction)) {
        /* Could not resolve a sensor, error */
        while(1);
    }

    // set write length to 1 byte
    i2cTransaction.writeCount = 1;

    // get temperature HOLD master mode
    txBuffer[0] = 0xE3;
    txBuffer[1] = 0x00;
    if (!I2C_transfer(i2c, &i2cTransaction)) {
        /* Could not resolve a sensor, error */
        while(1);
    }

    /* Take 20 samples and print them out onto the console */
    for (sample = 0; sample < 20; sample++) {

        // get temperature HOLD master mode
        txBuffer[0] = 0xE3;
        if (I2C_transfer(i2c, &i2cTransaction)) {

            /*
             * Extract degrees C from the received data;
             * see Si7021 datasheet
             */
            temperature = (rxBuffer[0] << 8) | (rxBuffer[1]);
            temperature *= 175.72;
            temperature /= 65536;
            temperature -= 46.85;
        }
        else {
            // I2C Bus fault
            temperature = 0;
        }

        // get humidity HOLD master mode
        txBuffer[0] = 0xE5;
        if (I2C_transfer(i2c, &i2cTransaction)) {

            /*
             * Extract relative humidity
             * see Si7021 datasheet
             */
            humidity = (rxBuffer[0] << 8) | (rxBuffer[1]);
            humidity *= 125;
            humidity /= 65536;
            humidity -= 6;
        }
        else {
            // I2C Bus fault
            humidity = 0;
        }

        /* Sleep for 1 second */
        sleep(1);
    }

    I2C_close(i2c);
//    Display_printf(display, 0, 0, "I2C closed!");

    return (NULL);
}
