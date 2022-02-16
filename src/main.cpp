#include <NativeEthernet.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int64MultiArray.h>
#include <RosArrayPublisher.h>
#include <vector>
#include "EthernetNodeHandle.h"


void messageCb(const std_msgs::Int32& msg) {
  Serial.println(msg.data);
}

std::vector<int> host_ip{192,168,1,100}; //pc
std::vector<int> client_ip{192,168,1,177}; //teensy


EthernetNodeHandle nh(host_ip,client_ip);
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