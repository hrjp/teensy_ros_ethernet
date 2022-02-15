/// @file EthernetNodeHandle.h
/// @brief ros nodehandle using ethernet
/// @date 2022.2.15
/// @author Shunya Hara

#include <NativeEthernet.h>
#include <ros.h>
#include <vector>

//teensy ip
IPAddress ip(192, 168, 1, 177);

//ros PC IP
IPAddress server(192, 168, 1, 100);

class SoketHardware {
  public:
  SoketHardware() {
    Ethernet.init(20);
    getMAC(mac);
    Ethernet.begin(mac, ip);
    client.connect(server, serverPort);
  };

  void init() {
    
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

class EthernetNodeHandle:ros::NodeHandle_<SoketHardware>{
    public:
    EthernetNodeHandle(const std::vector<int>& host_ip, const std::vector<int>& client_ip);
    private:

};

EthernetNodeHandle::EthernetNodeHandle(const std::vector<int>& host_ip, const std::vector<int>& client_ip){
}