/**
 ******************************************************************************
 * @file    wlan_hal.c
 * @author  Matthew McGowan
 * @version V1.0.0
 * @date    27-Sept-2014
 * @brief
 ******************************************************************************
  Copyright (c) 2013-14 Spark Labs, Inc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */


#include "wlan_hal.h"

uint32_t SPARK_WLAN_SetNetWatchDog(uint32_t timeOutInMS)
{
    return 0;
}


int wlan_clear_credentials() 
{
    return 1;
}

int wlan_has_credentials()
{
    return 1;    
}

int wlan_connect_init() 
{
    return 0;
}

wlan_result_t wlan_activate() {
    return 0;
}

wlan_result_t wlan_deactivate() {
    return 0;
}

bool wlan_reset_credentials_store_required() 
{
    return false;
}

wlan_result_t wlan_reset_credentials_store()
{
    return 0;
}


/**
 * Do what is needed to finalize the connection. 
 * @return 
 */
wlan_result_t wlan_connect_finalize() 
{
    // enable connection from stored profiles
    return 0;
}


void Set_NetApp_Timeout(void)
{
}

void Clear_NetApp_Dhcp(void)
{
}

wlan_result_t wlan_disconnect_now() 
{
    return 0;
}

wlan_result_t wlan_connected_rssi(char* ssid) 
{        
    return 0;
}

int inet_ping(uint8_t remoteIP[4], uint8_t nTries) {
    return 0;
}


int wlan_set_credentials(const char *ssid, uint16_t ssidLen, const char *password, 
    uint16_t passwordLen, WLanSecurityType security)
{
  return -1;
}

void wlan_smart_config_init() {
    
}

void wlan_smart_config_finalize() {    
}



void wlan_smart_config_cleanup() 
{
}


void wlan_setup()
{    
}
            
            
wlan_result_t wlan_manual_connect() 
{
    return 0;
}

void wlan_clear_error_count() 
{
}

void wlan_set_error_count(uint32_t errorCount) 
{
}

void wlan_fetch_ipconfig(WLanConfig* config) {
}

void SPARK_WLAN_SmartConfigProcess()
{
}

