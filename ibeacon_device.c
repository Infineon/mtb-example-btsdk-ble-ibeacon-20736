/*
 * Copyright 2016-2021, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */


/** @file
*
* Bluetooth LE iBeacon sample
*
* During initialization the app configures stack to send advertisement
* packets.  Non-connectable undirected advertisements are used.
*
* To build the application optional iBeacon library need to be included
* in the make file.  Please note that the library can be distributed only
* to the companies members of the Apple's iBeacon program.
*
* Features demonstrated
*  - iBeacon advertisements
*
* To demonstrate the app, work through the following steps.
* 1. Plug the WICED eval board into your computer
* 2. Build and download the application (to the WICED board)
* 3. Monitor advertisement packets on over the air sniffer
*
*/
#include "spar_utils.h"
#include "bleprofile.h"
#include "bleapp.h"
#include "platform.h"
#include "ibeacon.h"
#include "sparcommon.h"

/******************************************************
 *               Function Prototypes
 ******************************************************/
static void ibeacon_create(void);

/******************************************************
 *               Variables Definitions
 ******************************************************/
const UINT8  ibeacon_company_uuid[16] = {0x87, 0xf8, 0xac, 0xb5, 0x9a, 0xd0, 0x29, 0xa7, 0x20, 0x4c, 0xf0, 0x80, 0xe2, 0xb5, 0x5c, 0x0e};
const UINT16 ibeacon_major = 0x11;
const UINT16 ibeacon_minor = 0x0001;
const INT8   ibeacon_measured_power = -50;

// Following structure defines UART configuration
const BLE_PROFILE_PUART_CFG ibeacon_puart_cfg =
{
    /*.baudrate   =*/ 115200,
    /*.txpin      =*/ PUARTENABLE | GPIO_PIN_UART_TX,
    /*.rxpin      =*/ PUARTENABLE | GPIO_PIN_UART_RX,
};

/******************************************************
 *               Function Definitions
 ******************************************************/
// Application initialization
APPLICATION_INIT()
{
    bleapp_set_cfg(NULL,
                   0,
                   NULL,
                   (void *)&ibeacon_puart_cfg,
                   NULL,
                   ibeacon_create);
    BLE_APP_ENABLE_TRACING_ON_PUART();
}

// Create iBeacon device
void ibeacon_create(void)
{
    ble_trace0("\ribeacon_create()");
    ble_trace0(bleprofile_p_cfg->ver);

    ibeacon_start((UINT8 *) ibeacon_company_uuid, ibeacon_major, ibeacon_minor, ibeacon_measured_power);
}
