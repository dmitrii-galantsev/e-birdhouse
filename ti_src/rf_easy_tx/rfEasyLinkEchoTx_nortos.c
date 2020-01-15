/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
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
 *  ======== rfEasyLinkEchoTx_nortos.c ========
 */
 /* Standard C Libraries */
#include <stdlib.h>

/* TI-RTOS Header files */
#include <ti/drivers/I2C.h>
#include <ti/drivers/pin/PINCC26XX.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/devices/DeviceFamily.h>

/* Driverlib APIs */
#include DeviceFamily_constructPath(driverlib/sys_ctrl.h)

/* Board Header files */
#include "ti_drivers_config.h"

/* Application Header files */
#include <ti_radio_config.h>

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* Undefine to not use async mode */
#define RFEASYLINKECHO_ASYNC

#define RFEASYLINKECHO_PAYLOAD_LENGTH   30

#define SI7021_ADDRESS                  0x40

/* Pin driver handle */
static PIN_Handle pinHandle;
static PIN_State pinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config pinTable[] = {
    CONFIG_PIN_GLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    CONFIG_PIN_RLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    CONFIG_PIN_0    | PIN_INPUT_EN       | PIN_PULLDOWN,
    PIN_TERMINATE
};

static uint16_t seqNumber;

/* I2C variables */
static I2C_Handle      i2c;
static I2C_Params      i2cParams;
static I2C_Transaction i2cTransaction;
static uint8_t         txBuffer[1];
static uint8_t         rxBuffer[2];

#ifdef RFEASYLINKECHO_ASYNC
/* GPTimer handle and timeout value */
GPTimerCC26XX_Handle hTimer;
GPTimerCC26XX_Value rxTimeoutVal;

/* GP Timer Callback */
void rxTimeoutCb(GPTimerCC26XX_Handle handle,
                 GPTimerCC26XX_IntMask interruptMask);

static volatile bool rxDoneFlag;
static volatile bool rxTimeoutFlag;
#endif

static volatile bool bEchoDoneFlag;

EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};
/*
 * +---+-------------------------------------------+
 * |   | payload layout                            |
 * +---+-------------------------------------------+
 * | 0 | sequence num MSB                          |
 * | 1 | sequence num LSB                          |
 * | 2 | temperature  MSB                          |
 * | 3 | temperature  LSB                          |
 * | 4 | humidity     MSB                          |
 * | 5 | humidity     LSB                          |
 * | 6+| zeros                                     |
 * +---+-------------------------------------------+
 */

bool isPacketCorrect(EasyLink_RxPacket *rxp, EasyLink_TxPacket *txp)
{
    uint16_t i;
    bool status = true;

    for(i = 0; i < rxp->len; i++)
    {
        if(rxp->payload[i] != txp->payload[i])
        {
            status = false;
            break;
        }
    }
    return(status);
}

#ifdef RFEASYLINKECHO_ASYNC
void echoTxDoneCb(EasyLink_Status status)
{
    if (status == EasyLink_Status_Success)
    {
        /* Toggle GLED to indicate TX */
        PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED,!PIN_getOutputValue(CONFIG_PIN_GLED));
        /* Turn RLED off, in case there was a prior error */
        PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);
    }
    else
    {
        /* Set both GLED and RLED to indicate error */
        PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 1);
        PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);
    }

    bEchoDoneFlag = true;
}

void echoRxDoneCb(EasyLink_RxPacket * rxPacket, EasyLink_Status status)
{
    uint32_t currTimerVal;

    if ((status == EasyLink_Status_Success) &&
            (isPacketCorrect(rxPacket, &txPacket)))
    {
        /* Toggle GLED, clear RLED to indicate Echo RX */
        PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED,!PIN_getOutputValue(CONFIG_PIN_GLED));
        PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);

        /*
         * Stop the Receiver timeout timer, find the current free-running
         * counter value and add it to the existing interval load value
         */
        GPTimerCC26XX_stop(hTimer);
        currTimerVal = GPTimerCC26XX_getValue(hTimer);
        GPTimerCC26XX_setLoadValue(hTimer, rxTimeoutVal + currTimerVal);
    }
    else if (status == EasyLink_Status_Aborted)
    {
        /* Set RLED and clear GLED to indicate Abort */
        PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);
        PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 0);
    }
    else
    {
        /* Set both GLED and RLED to indicate error */
        PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 1);
        PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);

        /*
         * Stop the Receiver timeout timer, find the current free-running
         * counter value and add it to the existing interval load value
         */
        GPTimerCC26XX_stop(hTimer);
        currTimerVal = GPTimerCC26XX_getValue(hTimer);
        GPTimerCC26XX_setLoadValue(hTimer, rxTimeoutVal + currTimerVal);
    }

    bEchoDoneFlag = true;
}
#endif //RFEASYLINKECHO_ASYNC

uint16_t get_temperature()
{
    uint16_t temperature;

    // get temperature HOLD master mode
    txBuffer[0] = 0xE3;
    if (I2C_transfer(i2c, &i2cTransaction)) {

        /*
         * Extract degrees C from the received data
         * see Si7021 datasheet
         */
        temperature = (rxBuffer[0] << 8) | (rxBuffer[1]);
        temperature *= 0.00268127;
        temperature -= 46.85;
    }
    else {
        // I2C Bus fault
        temperature = 0;
    }

    return temperature;
}

uint16_t get_humidity()
{
    uint16_t humidity;

    // get humidity HOLD master mode
    txBuffer[0] = 0xE5;
    if (I2C_transfer(i2c, &i2cTransaction)) {

        /*
         * Extract relative humidity
         * see Si7021 datasheet
         */
        humidity = (rxBuffer[0] << 8) | (rxBuffer[1]);
        humidity *= 0.001907348;
        humidity -= 6;
    }
    else {
        // I2C Bus fault
        humidity = 0;
    }

    return humidity;
}

void *mainThread(void *arg0)
{
    uint32_t absTime;

    uint16_t temperature;
    uint16_t humidity;

    /* Open LED pins */
    while ((pinHandle = PIN_open(&pinState, pinTable)) == NULL);

    /* Clear LED pins */
    PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 0);
    PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);

    /* Init I2C */
    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    while ((i2c = I2C_open(CONFIG_I2C_TMP, &i2cParams)) == NULL);

    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf    = rxBuffer;
    i2cTransaction.readCount  = 2;

    /*
     * Determine which I2C sensor is present.
     */

    i2cTransaction.slaveAddress = SI7021_ADDRESS;


    // set write length to 1 byte
    i2cTransaction.writeCount = 1;
    // reset byte 0 and 1
    txBuffer[0] = 0x00;
    txBuffer[1] = 0x00;

#ifdef RFEASYLINKECHO_ASYNC
    /* Reset the timeout flag */
    rxTimeoutFlag = false;
    /* Set the echo flag to its default state */
    bEchoDoneFlag = false;

    /* Open the GPTimer driver */
    GPTimerCC26XX_Params params;
    GPTimerCC26XX_Params_init(&params);
    params.width          = GPT_CONFIG_32BIT;
    params.mode           = GPT_MODE_ONESHOT;
    params.direction      = GPTimerCC26XX_DIRECTION_UP;
    params.debugStallMode = GPTimerCC26XX_DEBUG_STALL_OFF;
    while ((hTimer = GPTimerCC26XX_open(CONFIG_TIMER_0, &params)) == NULL)
    {
        sleep(1);
    }

    /* Set Timeout value to 500ms */
    rxTimeoutVal = (SysCtrlClockGet()*5UL)/10UL - 1UL;
    GPTimerCC26XX_setLoadValue(hTimer, rxTimeoutVal);


    /* Register the GPTimer interrupt */
    GPTimerCC26XX_registerInterrupt(hTimer, rxTimeoutCb, GPT_INT_TIMEOUT);
#else
    EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};
#endif //RFEASYLINKECHO_ASYNC

    // Initialize the EasyLink parameters to their default values
    EasyLink_Params easyLink_params;
    EasyLink_Params_init(&easyLink_params);

    /*
     * Initialize EasyLink with the settings found in ti_easylink_config.h
     * Modify EASYLINK_PARAM_CONFIG in ti_easylink_config.h to change the default
     * PHY
     */
    while (EasyLink_init(&easyLink_params) != EasyLink_Status_Success){
        sleep(1);
    }

    /*
     * Initialize temp and humidity to 0's
     */
    temperature = 0;
    humidity = 0;

    /*
     * If you wish to use a frequency other than the default, use
     * the following API:
     * EasyLink_setFrequency(868000000);
     */

    // Packet Originator
    while(1) {
        /* Create packet with incrementing sequence number and random payload */
        txPacket.payload[0] = (uint8_t)(seqNumber >> 8);
        txPacket.payload[1] = (uint8_t)(seqNumber++);
        uint8_t i;

        // add temp
        temperature = get_temperature();
        txPacket.payload[2] = (uint8_t)(temperature >> 8);
        txPacket.payload[3] = (uint8_t)(temperature);

        // add humidity
        humidity = get_humidity();
        txPacket.payload[4] = (uint8_t)(humidity >> 8);
        txPacket.payload[5] = (uint8_t)(humidity);

        // add movement detection
        txPacket.payload[6] = PIN_getInputValue(CONFIG_PIN_0);

        // set the rest to 0
        for (i = 7; i < RFEASYLINKECHO_PAYLOAD_LENGTH; i++)
        {
            txPacket.payload[i] = 0;
        }

        txPacket.len = RFEASYLINKECHO_PAYLOAD_LENGTH;

        /*
         * Address filtering is enabled by default on the Rx device with the
         * an address of 0xAA. This device must set the dstAddr accordingly.
         */
        txPacket.dstAddr[0] = 0xaa;

        /* Set Tx absolute time to current time + 1000ms */
        if(EasyLink_getAbsTime(&absTime) != EasyLink_Status_Success)
        {
            // Problem getting absolute time
        }
        txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(1000);

#ifdef RFEASYLINKECHO_ASYNC
        /* Set Echo flag to false, TX Cb should set it to true */
        bEchoDoneFlag = false;
        EasyLink_transmitAsync(&txPacket, echoTxDoneCb);

        /* Wait for Tx to complete. A Successful TX will cause the echoTxDoneCb
         * to be called and the echoDoneSem to be released, so we must
         * consume the echoDoneSem
         */
        while(bEchoDoneFlag == false){};

        /* Switch to Receiver */
        bEchoDoneFlag = false;
        EasyLink_receiveAsync(echoRxDoneCb, 0);

        /*
         * Start the Receiver timeout timer (500ms) before
         * EasyLink_receiveAsync enables the power policy
         */
        GPTimerCC26XX_start(hTimer);

        while(bEchoDoneFlag == false){
            bool previousHwiState = IntMasterDisable();
            /*
             * Tricky IntMasterDisable():
             * true  : Interrupts were already disabled when the function was
             *         called.
             * false : Interrupts were enabled and are now disabled.
             */
            IntMasterEnable();
            Power_idleFunc();
            IntMasterDisable();

            if(!previousHwiState)
            {
                IntMasterEnable();
            }

            /* Break if timeout flag is set */
            if(rxTimeoutFlag == true){
                /* Reset the timeout flag */
                rxTimeoutFlag = false;
                /* RX timed out, abort */
                if(EasyLink_abort() == EasyLink_Status_Success)
                {
                    /* Wait for the abort */
                    while(bEchoDoneFlag == false){};
                }
                break;
            }
        }
#else
        EasyLink_Status result = EasyLink_transmit(&txPacket);

        if (result == EasyLink_Status_Success)
        {
            /* Toggle GLED to indicate TX */
            PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED,!PIN_getOutputValue(CONFIG_PIN_GLED));
            /* Turn RLED off, in case there was a prior error */
            PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);
        }
        else
        {
            /* Set both GLED and RLED to indicate error */
            PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 1);
            PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);
        }

        /* Switch to Receiver, set a timeout interval of 500ms */
        rxPacket.absTime = 0;
        rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(500);
        result = EasyLink_receive(&rxPacket);

        /* Check Received packet against what was sent, it should be identical
         * to the transmitted packet
         */
        if (result == EasyLink_Status_Success &&
                isPacketCorrect(&rxPacket, &txPacket))
        {
            /* Toggle GLED, clear RLED to indicate Echo RX */
            PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED,!PIN_getOutputValue(CONFIG_PIN_GLED));
            PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);
        }
        else if (result == EasyLink_Status_Rx_Timeout)
        {
            /* Set RLED and clear GLED to indicate Rx Timeout */
            PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);
            PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 0);
        }
        else
        {
            /* Set both GLED and RLED to indicate error */
            PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 1);
            PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);
        }
#endif //RFEASYLINKECHO_ASYNC
    }
}

#ifdef RFEASYLINKECHO_ASYNC
/* GP Timer Callback Function */
void rxTimeoutCb(GPTimerCC26XX_Handle handle,
                 GPTimerCC26XX_IntMask interruptMask)
{
    /* Set the Timeout Flag */
    rxTimeoutFlag = true;

    /*
     * Timer is automatically stopped in one-shot mode and needs to be reset by
     * loading the interval load value
     */
    GPTimerCC26XX_setLoadValue(hTimer, rxTimeoutVal);
}
#endif // RFEASYLINKECHO_ASYNC
