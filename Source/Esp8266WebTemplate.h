/*
  Esp8266.h - Library for wifi connection.
  Created by HSO, March 10, 2016.
  Released into the public domain.
*/

#ifndef ESP8266_WEB_TEMPLATE_H
#define ESP8266_WEB_TEMPLATE_H

#include <WString.h>
#include <avr/pgmspace.h>

namespace WIFI
{
  const char ConfigPage[] PROGMEM = "<!DOCTYPE html> <html lang=\"en\">" 
                                    "<head><meta charset=\"utf-8\">"
                                    "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
                                    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                                    "<meta name=\"description\" content=\"\">"
                                    "<meta name=\"author\" content=\"\">"
                                    "<title>WBox Client Configuration</title>"
                                    "</head>"
                                    "<body>"
                                    "<center>"
                                    "<p>Welcome to WBox config page</p>"
                                    "<form action='http://192.168.4.1/config' method='GET'>"
                                    "SSID:<br>"
                                    "<input type=\"text\" name=\"SSID\" value=\"\"><br><br>"
                                    "PASSWORD:<br>"
                                    "<input type=\"password\" name=\"PSSWD\" value=\"\"><br><br>"
                                    "House ID:<br>"
                                    "<input type=\"text\" name=\"HID\" value=\"\"><br><br>"
                                    "Node ID:<br>"
                                    "<input type=\"text\" name=\"NID\" value=\"\"><br><br>"
                                    "Server Ip:<br>"
                                    "<input type=\"text\" name=\"SIP\" value=\"\"><br><br>"
                                    "<input type=\"submit\" value=\"Submit\">"
                                    "</form>"
                                    "</center>"
                                    "</body>"
                                    "</html>";

  const char SuccessPage[] PROGMEM = "<!DOCTYPE html> <html lang=\"en\">" 
                                     "<head><meta charset=\"utf-8\">"
                                     "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
                                     "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                                     "<meta name=\"description\" content=\"\">"
                                     "<meta name=\"author\" content=\"\">"
                                     "<title>WBox Client Configuration</title>"
                                     "</head>"
                                     "<body>"
                                     "<center>"
                                     "<p>Configuration performed with success!</p>"
                                     "</center>"
                                     "</body>"
                                     "</html>";
}
#endif


