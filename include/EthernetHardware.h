/// @file EthernetHardware.h
/// @brief rosserialでEthernetを使用するためのドライバ
/// @date 2022.2.16
/// @author Shunya Hara
/// @ref https://qiita.com/que9/items/73c3d7c9519041a2b076

#pragma once

#include <NativeEthernet.h>
#include <vector>

class EthernetHardware {
  public:
  EthernetHardware() {
    
  };

  void init() {
    
  }

  void init(IPAddress& host_ip, IPAddress& client_ip){
    Ethernet.init(20);
    getMAC(mac);
    Ethernet.begin(mac, client_ip);
    client.connect(host_ip, serverPort);
  }

  int read() {
    if(client.available()){
      return client.read();
    }
    return -1;
    
  }

  void write(uint8_t* data, int length) {
    client.write(data,length);
  }

  unsigned long time() {
     return millis();
  }

  private:
  const uint16_t serverPort = 11411;
  EthernetClient client;
  byte mac[6];
  void getMAC(uint8_t *mac) {
    for(uint8_t by=0; by<2; by++) mac[by]=(HW_OCOTP_MAC1 >> ((1-by)*8)) & 0xFF;
    for(uint8_t by=0; by<4; by++) mac[by+2]=(HW_OCOTP_MAC0 >> ((3-by)*8)) & 0xFF;
  }
};
