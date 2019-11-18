
/*
 *  ======== ti_easylink_config.c ========
 *  Configured EasyLink module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */

/***** Includes *****/
#include "easylink/EasyLink.h"
#include <stdint.h>

/* TI Drivers */
#include <ti/drivers/rf/RF.h>

/* RF Studio */
#include <ti_radio_config.h>

EasyLink_RfSetting EasyLink_supportedPhys[] = {
    {
        .EasyLink_phyType = EasyLink_Phy_Custom,
        .RF_pProp = &RF_prop,
        .RF_uCmdPropRadio.RF_pCmdPropRadioDivSetup = &RF_cmdPropRadioDivSetup,
        .RF_pCmdFs = &RF_cmdFs,
        .RF_pCmdPropTx = &RF_cmdPropTx,
        .RF_pCmdPropTxAdv = NULL,
        .RF_pCmdPropRxAdv = &RF_cmdPropRxAdv,
        .RF_pTxPowerTable = txPowerTable,
        .RF_txPowerTableSize = TX_POWER_TABLE_SIZE,
    },
};

const uint8_t EasyLink_numSupportedPhys = sizeof(EasyLink_supportedPhys)/sizeof(EasyLink_RfSetting);
