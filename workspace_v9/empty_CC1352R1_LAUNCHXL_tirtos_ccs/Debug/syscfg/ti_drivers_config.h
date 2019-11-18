/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_CC1352R1_LAUNCHXL

#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== GPIO ========
 */

/* DIO6, LaunchPad LED Red */
#define CONFIG_LED_0_GPIO           0
/* DIO7, LaunchPad LED Green */
#define CONFIG_LED_1_GPIO           1
/* DIO15, LaunchPad Button BTN-1 (Left) */
#define CONFIG_GPIO_0               2
/* DIO14, LaunchPad Button BTN-2 (Right) */
#define CONFIG_GPIO_1               3

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== I2C ========
 */

/*
 *  SCL: DIO4
 *  SDA: DIO5
 */
#define CONFIG_I2C_0                0

/* ======== I2C Addresses and Speeds ======== */
#include <ti/drivers/I2C.h>

/* ---- CONFIG_I2C_0 I2C bus components ---- */

/* no components connected to CONFIG_I2C_0 */

/* max speed unspecified, defaulting to 100 Kbps */
#define CONFIG_I2C_0_MAXSPEED   (100U) /* Kbps */
#define CONFIG_I2C_0_MAXBITRATE ((I2C_BitRate)I2C_100kHz)


/*
 *  ======== PIN ========
 */

/* Includes */
#include <ti/drivers/PIN.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Parent Signal: CONFIG_I2C_0 SDA, (DIO5) */
#define CONFIG_PIN_7    0x00000005
/* Parent Signal: CONFIG_I2C_0 SCL, (DIO4) */
#define CONFIG_PIN_8    0x00000004
/* LaunchPad LED Red, Parent Signal: CONFIG_LED_0_GPIO GPIO Pin, (DIO6) */
#define CONFIG_PIN_1    0x00000006
/* LaunchPad LED Green, Parent Signal: CONFIG_LED_1_GPIO GPIO Pin, (DIO7) */
#define CONFIG_PIN_2    0x00000007
/* LaunchPad Button BTN-1 (Left), Parent Signal: CONFIG_GPIO_0 GPIO Pin, (DIO15) */
#define CONFIG_PIN_0    0x0000000f
/* LaunchPad Button BTN-2 (Right), Parent Signal: CONFIG_GPIO_1 GPIO Pin, (DIO14) */
#define CONFIG_PIN_3    0x0000000e


/*
 *  ======== Button ========
 */

/* DIO15, LaunchPad Button BTN-1 (Left) */
#define CONFIG_BUTTON_0             0
/* DIO14, LaunchPad Button BTN-2 (Right) */
#define CONFIG_BUTTON_1             1


/*
 *  ======== LED ========
 */

/* DIO6, LaunchPad LED Red */
#define CONFIG_LED_0                0
/* DIO7, LaunchPad LED Green */
#define CONFIG_LED_1                1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
