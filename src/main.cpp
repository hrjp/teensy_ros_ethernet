#include <NativeEthernet.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int64MultiArray.h>
#include <RosArrayPublisher.h>

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

void messageCb(const std_msgs::Int32& msg) {
  Serial.println(msg.data);
}

ros::NodeHandle_<SoketHardware> nh;
ros::Subscriber<std_msgs::Int32> sub("int_topic", &messageCb);
RosArrayPublisher<std_msgs::Int64MultiArray> int_pub(nh,"int_sensor_data",50);




void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  delay(1000);
  Serial.println("connecting...");

  nh.initNode();
  //nh.advertise(chatter);
  nh.subscribe(sub);
  
  delay(10);
  for (int i = 0; i < 50; i++){
    int_pub.array.data[i]=10000000000;
  }
  
}

void loop(){

  int_pub.publish();
  nh.spinOnce();
  delay(1);
}