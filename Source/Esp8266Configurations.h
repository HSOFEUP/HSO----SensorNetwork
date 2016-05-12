/*
  Esp8266.h - Library for wifi connection.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef ESP8266_CONFIG_H
#define ESP8266_CONFIG_H

#include <avr/pgmspace.h>

namespace WIFI
{
  // Http request
  struct HttpRequest
  {
   String Id;
   String Ipd;
  };

  // Client parameters
  struct ClientParameters
  {
   String Ssid;
   String Password;
   String HouseName;
   String NodeName;
   String ServerIp;
  };
   
  // Wifi Modes
  enum WifiMode
  {
    WM_STA                                    = 1,
    WM_AP                                     = 2,
    WM_BOTH                                   = 3,
    WM_QUERY                                  = '?'
  };

  // Wifi Encryption
  enum WifiEncryption
  {
    WE_OPEN                                   = 0,
    WE_WEP                                    = 1,
    WE_WAP_PSK                                = 2,
    WE_WAP2_PSK                               = 3,
    WE_WAP_WAP2_PSK                           = 4
  };
  
  // Tcp/Udp Connections
  enum WifiConnections
  {
    WC_SINGLE                                 = 0,
    WC_MULTIPLE                               = 1,
    WC_QUERY                                  = '?'
  };

  // Server Mode
  enum ServerMode
  {
    SM_CLOSE                                  = 0,
    SM_OPEN                                   = 1
  };

  // SoftwareSerial variables
  static uint8_t c_sw_srl_rx                  = 10;
  static uint8_t c_sw_srl_tx                  = 11;
  static uint16_t c_sw_srl_br                 = 9600;
  static uint16_t c_server_read_timeout       = 2000;
  static uint16_t c_client_read_timeout       = 10000;

  // Serial variables
  static long int c_srl_br                    = 57600;

  // Commands - Source: http://www.pridopia.co.uk/pi-doc/ESP8266ATCommandsSet.pdf
  const char cmd_reset[]              PROGMEM = "AT+RST";
  const char cmd_cwmode[]             PROGMEM = "AT+CWMODE=";
  const char cmd_cwsap[]              PROGMEM = "AT+CWSAP=";
  const char cmd_cipmux[]             PROGMEM = "AT+CIPMUX=";
  const char cmd_cipserver[]          PROGMEM = "AT+CIPSERVER=";
  const char cmd_cipsend[]            PROGMEM = "AT+CIPSEND=";
  const char cmd_cipclose[]           PROGMEM = "AT+CIPCLOSE=";
  const char cmd_cwjap[]              PROGMEM = "AT+CWJAP=";
  const char cmd_cipstart[]           PROGMEM = "AT+CIPSTART=";
  //static char * cmd_set_serial              = "AT+UART_DEF=9600,8,1,0,0\r\n";

  // Templates
  const char tplt_reset[]             PROGMEM = "ready";
  const char tplt_ok[]                PROGMEM = "OK";
  const char tplt_ipd[]               PROGMEM = "+IPD";
  const char tplt_grt_thn[]           PROGMEM = ">";
  const char tplt_send_ok[]           PROGMEM = "SEND OK";
  const char tplt_connected[]         PROGMEM = "WIFI CONNECTED";

  // Debug messages
  const char dbg_msg_reset[]          PROGMEM = "Reset";
  const char dbg_msg_ready[]          PROGMEM = "Ready";
  const char dbg_msg_not_ready[]      PROGMEM = "Not Ready";
  const char dbg_msg_ok[]             PROGMEM = "OK";
  const char dbg_msg_not_ok[]         PROGMEM = "Not OK";
  const char dbg_msg_send_ok[]        PROGMEM = "SEND OK";
  const char dbg_msg_send_not_ok[]    PROGMEM = "SEND Not OK";
  const char dbg_msg_grt_th[]         PROGMEM = ">";
  const char dbg_msg_connected[]      PROGMEM = "Connected";
  const char dbg_msg_not_connected[]  PROGMEM = "Not Connected";
  
  // AP parameters
  static char * c_ssid                        = "WBox";
  static char * c_pwd                         = "1234567890";
  static uint8_t c_chl                        = 5;
  static WifiEncryption c_encrypt             = WE_WAP2_PSK;
  static WifiConnections c_connections        = WC_MULTIPLE;
  static uint8_t c_srv_port                   = 80;

  //STA parameters
  static uint8_t tcp_chl                      = 0;
}
#endif


