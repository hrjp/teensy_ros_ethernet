

#include <NativeEthernet.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int64MultiArray.h>
#include <RosArrayPublisher.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  //0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  0x04, 0xE9, 0xE5, 0x0C, 0x69, 0x07
  //0xDD, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Enter the IP address of the server you're connecting to:
IPAddress server(192, 168, 1, 100);
const uint16_t serverPort = 11411;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 23 is default for telnet;
// if you're using Processing's ChatServer, use port 10002):
EthernetClient client;

void teensyMAC(uint8_t *mac) {
    for(uint8_t by=0; by<2; by++) mac[by]=(HW_OCOTP_MAC1 >> ((1-by)*8)) & 0xFF;
    for(uint8_t by=0; by<4; by++) mac[by+2]=(HW_OCOTP_MAC0 >> ((3-by)*8)) & 0xFF;
    Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}


class WiFiHardware {
  public:
  WiFiHardware() {
    Ethernet.init(20);
    teensyMAC(mac);
    Ethernet.begin(mac, ip);
    client.connect(server, serverPort);
    Serial.println("init");
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
    //for(int i=0; i<length; i++)
    //  client.write(data[i]);
  }

  unsigned long time() {
     return millis();
  }

  private:
  void teensyMAC(uint8_t *mac) {
    for(uint8_t by=0; by<2; by++) mac[by]=(HW_OCOTP_MAC1 >> ((1-by)*8)) & 0xFF;
    for(uint8_t by=0; by<4; by++) mac[by+2]=(HW_OCOTP_MAC0 >> ((3-by)*8)) & 0xFF;
    //Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  }
};

void messageCb(const std_msgs::Int32& msg) {
  Serial.println(msg.data);
}

ros::NodeHandle_<WiFiHardware> nh;
//ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<std_msgs::Int32> sub("int_topic", &messageCb);
char hello[13] = "hello world!";
RosArrayPublisher<std_msgs::Int64MultiArray> int_pub(nh,"int_sensor_data",50);
//RosArrayPublisher<std_msgs::Int64MultiArray> int_pub2(nh,"int_sensor_data2",50);



void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // start the Ethernet connection:
  //Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
/*
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  while (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    delay(500);
  }
*/
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  /*if (client.connect(server, serverPort)) {
    Serial.println("connected");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }*/
//Serial.println("init2");
  nh.initNode();
  //Serial.println("init3");
  nh.advertise(chatter);
  nh.subscribe(sub);
  delay(10);
  for (int i = 0; i < 10; i++){
    int_pub.array.data[i]=10000000000;
  }
  
}

void loop()
{
  str_msg.data = hello;
  //Serial.println("loop1");
  //chatter.publish( &str_msg );
  int_pub.publish();
  //int_pub2.publish();
  //Serial.println("loop2");
  int sta=nh.spinOnce();
  Serial.println(sta);
  delay(1);
}