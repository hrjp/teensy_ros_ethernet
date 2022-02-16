# teensy_ros_ethernet
Teensy4.1のイーサネットポートを使って，ROS1と通信するPlatfromIOプロジェクトのサンプル

## 1.依存パッケージ
* [NativeEthernet](https://github.com/vjmuzik/NativeEthernet)
* [FNET](https://github.com/vjmuzik/FNET)


## 2.Setup
### ROS PC
#### 1.有線LANの設定
* IPv4 Address 192.168.1.100
* Netmask 255.255.255.0

#### 2.端末を3つ開いて以下のコマンドを実行
```bash
roscore
```

```bash
rosrun rosserial_python serial_node.py tcp
```

```bash
rostopic echo /int_sensor_data
```

### Teensy
```bash
git clone https://github.com/hrjp/teensy_ros_ethernet
```
1. PlatformIOでこのプロジェクトを開く
2. プロジェクトをTeensyに書き込みシリアルモニターを開く
