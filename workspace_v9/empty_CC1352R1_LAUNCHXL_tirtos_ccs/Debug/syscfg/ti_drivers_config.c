/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */

#include <stddef.h>

#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"


/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMACC26XX.h>
#include <ti/devices/cc13x2_cc26x2/driverlib/udma.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>

UDMACC26XX_Object udmaCC26XXObject;

const UDMACC26XX_HWAttrs udmaCC26XXHWAttrs = {
    .baseAddr        = UDMA0_BASE,
    .powerMngrId     = PowerCC26XX_PERIPH_UDMA,
    .intNum          = INT_DMA_ERR,
    .intPriority     = (~0)
};

const UDMACC26XX_Config UDMACC26XX_config[1] = {
    {
        .object         = &udmaCC26XXObject,
        .hwAttrs        = &udmaCC26XXHWAttrs,
    },
};


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* CONFIG_LED_0_GPIO : LaunchPad LED Red */
    GPIOCC26XX_DIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_LED_1_GPIO : LaunchPad LED Green */
    GPIOCC26XX_DIO_07 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_0 : LaunchPad Button BTN-1 (Left) */
    GPIOCC26XX_DIO_15 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,
    /* CONFIG_GPIO_1 : LaunchPad Button BTN-2 (Right) */
    GPIOCC26XX_DIO_14 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *
 *  NOTE: Unused callback entries can be omitted from the callbacks array to
 *  reduce memory usage by enabling callback table optimization
 *  (GPIO.optimizeCallbackTableSize = true)
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    /* CONFIG_LED_0_GPIO : LaunchPad LED Red */
    NULL,
    /* CONFIG_LED_1_GPIO : LaunchPad LED Green */
    NULL,
    /* CONFIG_GPIO_0 : LaunchPad Button BTN-1 (Left) */
    NULL,
    /* CONFIG_GPIO_1 : LaunchPad Button BTN-2 (Right) */
    NULL,
};

/*
 *  ======== GPIOCC26XX_config ========
 */
const GPIOCC26XX_Config GPIOCC26XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = 4,
    .numberOfCallbacks = 4,
    .intPriority = (~0)
};


/*
 *  =============================== I2C ===============================
 */

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>

#define CONFIG_I2C_COUNT 1

/*
 *  ======== i2cCC26xxObjects ========
 */
I2CCC26XX_Object i2cCC26xxObjects[CONFIG_I2C_COUNT];

/*
 *  ======== i2cCC26xxHWAttrs ========
 */
const I2CCC26XX_HWAttrsV1 i2cCC26xxHWAttrs[CONFIG_I2C_COUNT] = {
    /* CONFIG_I2C_0 */
    {
        .baseAddr    = I2C0_BASE,
        .powerMngrId = PowerCC26XX_PERIPH_I2C0,
        .intNum      = INT_I2C_IRQ,
        .intPriority = (~0),
        .swiPriority = 0,
        .sclPin      = IOID_4,
        .sdaPin      = IOID_5
    },
};

/*
 *  ======== I2C_config ========
 */
const I2C_Config I2C_config[CONFIG_I2C_COUNT] = {
    /* CONFIG_I2C_0 */
    {
        .fxnTablePtr = &I2CCC26XX_fxnTable,
        .object      = &i2cCC26xxObjects[CONFIG_I2C_0],
        .hwAttrs     = &i2cCC26xxHWAttrs[CONFIG_I2C_0]
    },
};

const uint_least8_t I2C_count = CONFIG_I2C_COUNT;


/*
 *  =============================== PIN ===============================
 */

#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

const PIN_Config BoardGpioInitTable[] = {
    /* Parent Signal: CONFIG_I2C_0 SDA, (DIO5) */
    CONFIG_PIN_7 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_DIS,
    /* Parent Signal: CONFIG_I2C_0 SCL, (DIO4) */
    CONFIG_PIN_8 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,
    /* LaunchPad LED Red, Parent Signal: CONFIG_LED_0_GPIO GPIO Pin, (DIO6) */
    CONFIG_PIN_1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,
    /* LaunchPad LED Green, Parent Signal: CONFIG_LED_1_GPIO GPIO Pin, (DIO7) */
    CONFIG_PIN_2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,
    /* LaunchPad Button BTN-1 (Left), Parent Signal: CONFIG_GPIO_0 GPIO Pin, (DIO15) */
    CONFIG_PIN_0 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_DIS,
    /* LaunchPad Button BTN-2 (Right), Parent Signal: CONFIG_GPIO_1 GPIO Pin, (DIO14) */
    CONFIG_PIN_3 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_DIS,

    PIN_TERMINATE
};

const PINCC26XX_HWAttrs PINCC26XX_hwAttrs = {
    .intPriority = (~0),
    .swiPriority = 0
};


/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26X2.h>
#include "ti_drivers_config.h"

extern void PowerCC26XX_standbyPolicy(void);
extern bool PowerCC26XX_calibrate(unsigned int);

const PowerCC26X2_Config PowerCC26X2_config = {
    .enablePolicy             = true,
    .policyInitFxn            = NULL,
    .policyFxn                = PowerCC26XX_standbyPolicy,
    .calibrateFxn             = PowerCC26XX_calibrate,
    .calibrateRCOSC_LF        = true,
    .calibrateRCOSC_HF        = true,
    .enableTCXOFxn            = NULL
};


/*
 *  =============================== Button ===============================
 */
#include <ti/drivers/apps/Button.h>

Button_Object ButtonObjects[2];

static const Button_HWAttrs ButtonHWAttrs[2] = {
    /* CONFIG_BUTTON_0 */
    /* LaunchPad Button BTN-1 (Left) */
    {
        .gpioIndex = CONFIG_GPIO_0
    },
    /* CONFIG_BUTTON_1 */
    /* LaunchPad Button BTN-2 (Right) */
    {
        .gpioIndex = CONFIG_GPIO_1
    },
};

const Button_Config Button_config[2] = {
    /* CONFIG_BUTTON_0 */
    /* LaunchPad Button BTN-1 (Left) */
    {
        .object = &ButtonObjects[CONFIG_BUTTON_0],
        .hwAttrs = &ButtonHWAttrs[CONFIG_BUTTON_0]
    },
    /* CONFIG_BUTTON_1 */
    /* LaunchPad Button BTN-2 (Right) */
    {
        .object = &ButtonObjects[CONFIG_BUTTON_1],
        .hwAttrs = &ButtonHWAttrs[CONFIG_BUTTON_1]
    },
};

const uint_least8_t Button_count = 2;


/*
 *  =============================== LED ===============================
 */
#include <ti/drivers/apps/LED.h>

LED_Object LEDObjects[2];

static const LED_HWAttrs LEDHWAttrs[2] = {
    /* CONFIG_LED_0 */
    /* LaunchPad LED Red */
    {
        .type = LED_GPIO_CONTROLLED,
        .index = CONFIG_LED_0_GPIO,
    },
    /* CONFIG_LED_1 */
    /* LaunchPad LED Green */
    {
        .type = LED_GPIO_CONTROLLED,
        .index = CONFIG_LED_1_GPIO,
    },
};

const LED_Config LED_config[2] = {
    /* CONFIG_LED_0 */
    /* LaunchPad LED Red */
    {
        .object = &LEDObjects[CONFIG_LED_0],
        .hwAttrs = &LEDHWAttrs[CONFIG_LED_0]
    },
    /* CONFIG_LED_1 */
    /* LaunchPad LED Green */
    {
        .object = &LEDObjects[CONFIG_LED_1],
        .hwAttrs = &LEDHWAttrs[CONFIG_LED_1]
    },
};

const uint_least8_t LED_count = 2;


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    /* ==== /ti/drivers/PIN initialization ==== */
    if (PIN_init(BoardGpioInitTable) != PIN_SUCCESS) {
        /* Error with PIN_init */
        while (1);
    }
    Board_initHook();
}
