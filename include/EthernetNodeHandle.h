/// @file EthernetNodeHandle.h
/// @brief ros nodehandle using ethernet
/// @date 2022.2.15
/// @author Shunya Hara

#pragma once

#include <NativeEthernet.h>
#include <ros.h>
#include <vector>

#include "EthernetHardware.h"



class EthernetNodeHandle:public ros::NodeHandle_<EthernetHardware>{
    public:

    /// @brief コンストラクタ
    /// @param host_ip ros pcのIPアドレス
    /// @param client_ip マイコンのIPアドレス
    EthernetNodeHandle(const std::vector<int>& host_ip, const std::vector<int>& client_ip);

};



EthernetNodeHandle::EthernetNodeHandle(const std::vector<int>& host_ip, const std::vector<int>& client_ip){
  IPAddress host_ip_(host_ip[0],host_ip[1],host_ip[2],host_ip[3]);
  IPAddress client_ip_(client_ip[0],client_ip[1],client_ip[2],client_ip[3]);
  ros::NodeHandle_<EthernetHardware>::hardware_.init(host_ip_,client_ip_);
}