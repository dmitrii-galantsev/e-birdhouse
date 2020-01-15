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
 *  ======== pinInterrupt.c ========
 */
#include <unistd.h>

/* Driver Header files */
#include <ti/drivers/PIN.h>

/* TI-Drivers Configuration */
#include "ti_drivers_config.h"

/*
 * Device specific header file containing CPUdelay()
 */
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/cpu.h)

/* Pin driver handles */
static PIN_Handle buttonPinHandle;
static PIN_Handle ledPinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State buttonPinState;
static PIN_State ledPinState;

/*
 * Initial LED pin configuration table
 *   - LEDs CONFIG_PIN_LED_0 is on.
 *   - LEDs CONFIG_PIN_LED_1 is off.
 */
PIN_Config ledPinTable[] = {
    CONFIG_PIN_LED_0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    CONFIG_PIN_LED_1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW  | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
PIN_Config buttonPinTable[] = {
    CONFIG_PIN_BUTTON_0  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    CONFIG_PIN_BUTTON_1  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    CONFIG_PIN_0         | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

/*
 *  ======== buttonCallbackFxn ========
 *  Push buttons callback function.
 */
void buttonCallbackFxn(PIN_Handle handle, PIN_Id pinId) {
    uint32_t currVal = 0;

    /* Debounce logic, only toggle if the button is still pushed (low) */
    CPUdelay(8000 * 50);
    if (!PIN_getInputValue(pinId)) {
        /* Toggle LED based on the button pressed */
        switch (pinId) {
            case CONFIG_PIN_BUTTON_0:
                currVal =  PIN_getOutputValue(CONFIG_PIN_LED_0);
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_LED_0, !currVal);
                break;

            case CONFIG_PIN_BUTTON_1:
                currVal =  PIN_getOutputValue(CONFIG_PIN_LED_1);
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_LED_1, !currVal);
                break;

            case CONFIG_PIN_0:
                currVal =  PIN_getOutputValue(CONFIG_PIN_LED_0);
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_LED_0, !currVal);
                break;

            default:
                /* Do nothing */
                break;
        }
    }
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
    if(!ledPinHandle) {
        /* Error initializing LED pins */
        while(1);
    }

    buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
    if(!buttonPinHandle) {
        /* Error initializing button pins */
        while(1);
    }

    /* Setup callback for button pins */
    if (PIN_registerIntCb(buttonPinHandle, &buttonCallbackFxn) != 0) {
        /* Error registering button callback function */
        while(1);
    }

    /* Loop forever */
    while(1) {
        sleep(1000);
    }
}
