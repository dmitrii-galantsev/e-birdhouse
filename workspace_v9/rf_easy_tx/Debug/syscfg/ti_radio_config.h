/*
 *  ======== ti_radio_config.h ========
 *  Configured RadioConfig module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1F3RGZ
 *  by the SysConfig tool.
 *  
 *  Radio Config module version : 1.3
 *  SmartRF Studio data version : 2.15.0
 */
#ifndef _TI_RADIO_CONFIG_H_
#define _TI_RADIO_CONFIG_H_

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/rf_mailbox.h)
#include DeviceFamily_constructPath(driverlib/rf_common_cmd.h)
#include DeviceFamily_constructPath(driverlib/rf_prop_cmd.h)
#include <ti/drivers/rf/RF.h>


//*********************************************************************************
//  RF Setting:   50 kbps, 2-GFSK, 25 kHz deviation
//
//  PHY:          2gfsk50kbps     
//  Setting file: setting_tc106.json
//*********************************************************************************

// TX Power table size definition
#define TX_POWER_TABLE_SIZE 20

// TX Power Table Object
extern RF_TxPowerTable_Entry txPowerTable[];

// TI-RTOS RF Mode Object
extern RF_Mode RF_prop;

// RF Core API commands
extern rfc_CMD_PROP_RADIO_DIV_SETUP_t RF_cmdPropRadioDivSetup;
extern rfc_CMD_FS_t RF_cmdFs;
extern rfc_CMD_PROP_TX_t RF_cmdPropTx;
extern rfc_CMD_PROP_RX_ADV_t RF_cmdPropRxAdv;

// RF Core API Overrides
extern uint32_t pOverrides[];

#endif // _TI_RADIO_CONFIG_H_
