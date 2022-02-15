/// @file topic_publisher.ino
/// @brief MultiArray publisher sample
/// @date 2022.2.15
/// @author Shunya Hara

#pragma once

//ros_lib
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>

#include <RosArrayPublisher.h>

//ros NodeHandleの宣言
ros::NodeHandle nh;

//int型で要素が5個の配列を int_array_data というtopic名で送信する場合
RosArrayPublisher<std_msgs::Int32MultiArray> int_pub(nh,"int_array_data",5);

//float型で要素が5個の配列を float_array_data というtopic名で送信する場合
RosArrayPublisher<std_msgs::Float32MultiArray> float_pub(nh,"float_array_data",5);

void setup() {
  Serial.begin(57600);
  //ros node の初期化
  nh.initNode();
}

void loop(){
    //要素の代入
    int_pub.array.data[0]=1;
    int_pub.array.data[1]=10;
    int_pub.array.data[2]=100;
    int_pub.array.data[3]=1000;
    int_pub.array.data[4]=10000;

    //要素の代入
    float_pub.array.data[0]=1.0;
    float_pub.array.data[1]=10.0;
    float_pub.array.data[2]=100.0;
    float_pub.array.data[3]=1000.0;
    float_pub.array.data[4]=10000.0;

    //int配列のpublish
    int_pub.publish();

    //float配列のpublish
    float_pub.publish();
}

