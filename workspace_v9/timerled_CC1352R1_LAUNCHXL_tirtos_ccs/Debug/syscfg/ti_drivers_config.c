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
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* CONFIG_GPIO_LED_0 : LaunchPad LED Red */
    GPIOCC26XX_DIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_PIN_0 */
    GPIOCC26XX_DIO_05 | GPIO_DO_NOT_CONFIG,
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
    /* CONFIG_GPIO_LED_0 : LaunchPad LED Red */
    NULL,
    /* CONFIG_GPIO_PIN_0 */
    NULL,
};

/*
 *  ======== GPIOCC26XX_config ========
 */
const GPIOCC26XX_Config GPIOCC26XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = 2,
    .numberOfCallbacks = 2,
    .intPriority = (~0)
};


/*
 *  =============================== PIN ===============================
 */

#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

const PIN_Config BoardGpioInitTable[] = {
    /* Parent Signal: CONFIG_GPIO_PIN_0 GPIO Pin, (DIO5) */
    CONFIG_PIN_1 | PIN_INPUT_EN | PIN_NOPULL | PIN_IRQ_DIS,
    /* LaunchPad LED Red, Parent Signal: CONFIG_GPIO_LED_0 GPIO Pin, (DIO6) */
    CONFIG_PIN_0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,

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
 *  =============================== Timer ===============================
 */

#include <ti/drivers/Timer.h>
#include <ti/drivers/timer/TimerCC26XX.h>

#define CONFIG_TIMER_COUNT 1

/*
 *  ======== timerCC26XXObjects ========
 */
TimerCC26XX_Object timerCC26XXObjects[CONFIG_TIMER_COUNT];

/*
 *  ======== timerCC26XXHWAttrs ========
 */
const TimerCC26XX_HWAttrs timerCC26XXHWAttrs[CONFIG_TIMER_COUNT] = {
    {
        .gpTimerUnit = CONFIG_GPTIMER_0,
        .subTimer    = TimerCC26XX_timer32

    },
};

/*
 *  ======== Timer_config ========
 */
const Timer_Config Timer_config[CONFIG_TIMER_COUNT] = {
    /* CONFIG_TIMER_0 */
    {
        .fxnTablePtr = &TimerCC26XX_fxnTable,
        .object    = &timerCC26XXObjects[CONFIG_TIMER_0],
        .hwAttrs   = &timerCC26XXHWAttrs[CONFIG_TIMER_0]
    },
};

const uint_least8_t Timer_count = CONFIG_TIMER_COUNT;


/*
 *  =============================== GPTimer ===============================
 */

#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>

#define CONFIG_GPTIMER_COUNT 1

/*
 *  ======== gptimerCC26XXObjects ========
 */
GPTimerCC26XX_Object gptimerCC26XXObjects[CONFIG_GPTIMER_COUNT];

/*
 *  ======== gptimerCC26XXHWAttrs ========
 */
const GPTimerCC26XX_HWAttrs gptimerCC26XXHWAttrs[CONFIG_GPTIMER_COUNT] = {
    /* CONFIG_GPTIMER_0, used by CONFIG_TIMER_0 */
    {
        .baseAddr = GPT0_BASE,
        .intNum      = INT_GPT0A,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT0,
        .pinMux      = GPT_PIN_0A
    },
};

/*
 *  ======== GPTimer_config ========
 */
const GPTimerCC26XX_Config GPTimerCC26XX_config[CONFIG_GPTIMER_COUNT] = {
    /* CONFIG_GPTIMER_0 */
    {
        .object    = &gptimerCC26XXObjects[CONFIG_GPTIMER_0],
        .hwAttrs   = &gptimerCC26XXHWAttrs[CONFIG_GPTIMER_0],
        .timerPart = GPT_A
    },
};

const uint_least8_t GPTimer_count = CONFIG_GPTIMER_COUNT;


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
