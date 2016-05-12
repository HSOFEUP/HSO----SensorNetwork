#include "Esp8266.h"

namespace WIFI
{
  Esp8266::Esp8266()
  {
    m_serial = new SerialDriver::SerialPort;
    
    m_serial->SetupSerial(c_srl_br);
    
    m_serial->SetupSoftwareSerial(c_sw_srl_rx, c_sw_srl_tx, c_sw_srl_br);
    
    m_serial->SetDriverName("Esp8266");

    m_serial->SerialWrite("Constructor");

    // Only in exceptional cases
    //m_serial->CommandLineDebug(); 
  }
  
  Esp8266::~Esp8266()
  {
    delete m_serial;
  }

  void
  Esp8266::Setup()
  {          
    // Reset module
    Reset();

    // Config webserver
    ConfigWebServer();
    
    // Start client
    ConfigClient();
  }

  bool
  Esp8266::Reset()
  {
     // Send reset command
    Esp8266Utils::SendAtCommand(cmd_reset, "",  tplt_reset, dbg_msg_ready, dbg_msg_not_ready, m_serial);
  }

  bool
  Esp8266::ConfigWMode(WifiMode mode)
  {   
    // Send cwmode command
    Esp8266Utils::SendAtCommand(cmd_cwmode, String(mode), tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
  }

  // Config Connections
  // @param - Mode single/multiple
  // @return - bool with op result
  bool
  Esp8266::ConfigConnections(WifiConnections wconnect)
  {
    // Send cipmux command
    Esp8266Utils::SendAtCommand(cmd_cipmux, String(wconnect), tplt_ok, dbg_msg_ok, dbg_msg_not_ok, m_serial);
 }
    
  void
  Esp8266::ConfigWebServer()
  {
    // Config as AP
    ConfigWMode(WM_AP);

    // Reset the module to finish changing the operating mode.
    Reset();

    // Config connections
    ConfigConnections(WC_MULTIPLE);

    // Set parameters of AP
    Esp8266Server::ConfigAP(c_ssid, c_pwd, c_chl, c_encrypt, m_serial);

    // Start server
    Esp8266Server::StartServer(SM_OPEN, c_srv_port, m_serial);

    // Send configuration page
    Esp8266Server::SendWebPage(ConfigPage, m_serial);

    // Receive configuration parameters
    Esp8266Server::ReceiveClientParameters(&client_parameters, m_serial);

    // Stop server
    Esp8266Server::StopServer(SM_CLOSE, m_serial);
  }

  void
  Esp8266::ConfigClient()
  {
    // Config as Station
    ConfigWMode(WM_STA);

    // Reset the module to finish changing the operating mode.
    Reset();

    // Config connections
    ConfigConnections(WC_MULTIPLE);//SINGLE);

    // Connect to AP
    Esp8266Client::ConnectToAp(client_parameters, m_serial);
  }

  void
  Esp8266::SendNodeData(float smoke_level, float h, float t, float hic)
  {
    // Connecto to Server
    // Get http request
    // Send

    while (!Esp8266Client::ConnectToServer(client_parameters, m_serial));
    
    String cmd = "GET http://" + client_parameters.ServerIp + "/Core/IO/Receiver.php?"+
                 "house=" + client_parameters.HouseName + 
                 "&room=" + client_parameters.NodeName + 
                 "&smoke=" + smoke_level + 
                 "&humidity=" + h + 
                 "&temperature=" + t + 
                 "&heatindex=" + hic + 
                 "\r\n\r\n";
                 
    while(!Esp8266Client::GetHttpRequest(cmd, m_serial));
  }
 
}
  

