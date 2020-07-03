/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : softAPConfig()演示
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : 小黑
日期/Date（YYYYMMDD）     : 20200319
程序目的/Purpose          : 
此程序使用ESP8266WiFiAP库来演示softAPConfig()函数可用于配置网络信息.在wifi初始化
时可配置接入点IP地址，网关IP地址，子网掩码和默认的IP地址.

注意：在不同的网络环境中，子网掩码，网关IP等信息各不相同，所以您在使用本示例程序时要根
据您网络环境的网关IP、设备IP、子网掩码进行相应设置而不要照搬示例程序中的IP地址，否则
可能会造成例程无法正常运行。
-----------------------------------------------------------------------
本示例程序为太极创客团队制作的《零基础入门学用物联网》中示例程序。
该教程为对物联网开发感兴趣的朋友所设计和制作。如需了解更多该教程的信息，请参考以下网页：
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
***********************************************************************/
#include <ESP8266WiFi.h>
 
#define AP_ssid   "TaichiMaker_WIFI" //这里改成你的设备当前环境下接入点名字
#define password  "12345678"          //这里改成你的设备当前环境下接入点密码

IPAddress local_IP(192,168,4,22);//手动设置的开启的网络的ip地址
IPAddress gateway(192,168,4,9);  //手动设置的网关IP地址
IPAddress subnet(255,255,255,0); //手动设置的子网掩码

bool flag;

void setup() {
  // 启动串口通讯
  Serial.begin(9600); 
  Serial.println();
  
  //设置为接入点模式
  WiFi.mode(WIFI_AP);
  
  //配置接入点的IP，网关IP，子网掩码
  WiFi.softAPConfig(local_IP, gateway, subnet);
  
  //启动AP，并设置账号和密码
  Serial.printf("设置接入点中 ... ");
  
  //启动校验式网络（需要输入账号密码的网络）,通道为3，wifi隐藏，最大连接数=4
  WiFi.softAP(AP_ssid, password,3,1);
  
  //监控状态变量result 
  flag = WiFi.softAP(AP_ssid, password); 
  if(flag){ 
  Serial.println("");              // 通过串口监视器输出信息
  Serial.print("当前工作模式:");     // 告知用户设备当前工作模式
  Serial.println(WiFi.getMode());
  Serial.print("接入点名字:");    
  Serial.println(AP_ssid);            // 告知用户建立的接入点WiFi名
  Serial.print("接入点密码:");        
  Serial.println(password);        // 告知用户建立的接入点WiFi密码   
  Serial.println("网络IP");
  Serial.println("local_IP");     //打印ip地址
  Serial.println("网关IP");
  Serial.println(gateway);        //打印网关IP
  Serial.println("子网掩码：");
  Serial.println(subnet);         //打印子网掩码
  }else{
    //若没有开启成功
    Serial.println("开启失败");
  }
  
  Serial.println("初始化结束");
}

void loop() {}