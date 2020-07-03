#ifndef WifiManager_h
#define WifiManager_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <ESP8266WebServer.h>
// #include <DNSServer.h>
// #include <ESP8266mDNS.h>

#define WIFI_MODE_OFF 0
#define WIFI_MODE_AP 1
#define WIFI_MODE_STATION 2

/*
  主要用于创建和连接wifi的配置
  This file contains all necessary functions for hosting and connecting to an access point.
  For compatibility and simplicity, all those functions are global.
*/

// 默认声明 Important strings
const char W_WEBINTERFACE[] PROGMEM = "/web";  // 默认web访问文件路径 default folder containing the web files
const char W_ERROR_PASSWORD[] PROGMEM = "ERROR: Password must have at least 8 characters!";

// 建立全局的Web服务器并监听端口 Server and other global objects
ESP8266WebServer server(80);
IPAddress local_IP(192,168,4,99);//手动设置的开启的网络的ip地址
IPAddress gateway(192,168,0,1);  //手动设置的网关IP地址
IPAddress subnet(255,255,255,0); //手动设置的子网掩码

// current WiFi mode and config
uint8_t wifiMode = WIFI_MODE_OFF;

bool   wifi_config_hidden        = false;
bool   wifi_config_captivePortal = false;
String wifi_config_ssid;
String wifi_config_password;
String wifi_config_path;
int wifi_channel;

bool isLedTurnOpen = false; // 记录LED状态
bool flag;

void handleRoot() {
  server.send(200, "text/html", String("") +
    "<html>" +
    "<head>" +
    "    <title>ESP8266 Web Server Test</title>" +
    "    <script defer=\"defer\">" +
    "        function ledSwitch() {" +
    "            var xmlhttp;" +
    "            if (window.XMLHttpRequest) {" +
    "                xmlhttp = new XMLHttpRequest();" +
    "            } else {" +
    "                xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");" +
    "            }" +
    "            xmlhttp.onreadystatechange = function () {" +
    "                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {" +
    "                    document.getElementById(\"txtState\").innerHTML = xmlhttp.responseText;" +
    "                }" +
    "            }," +
    "            xmlhttp.open(\"GET\", \"Switch\", true);" +
    "            xmlhttp.send(); " +
    "        }" +
    "    </script>" +
    "</head>" +
    "<body>" +
    "    <div id=\"txtState\">Unkwon</div>" +
    "    <input type=\"button\" value=\"Switch\" onclick=\"ledSwitch()\">" +
    "</body>" +
    "</html>");
    prntln(String("用户访问了主页"));
}

void handleSwitch() {
  if (isLedTurnOpen == false) {
    digitalWrite(LED_BUILTIN, LOW); // 点亮LED
    server.send(200, "text/plain", "LED has been turn on");
    prntln(String("用户开启了LED"));
    isLedTurnOpen = true;
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH); // 熄灭LED
    server.send(200, "text/plain", "LED has been turn off");
    prntln(String("用户关闭了LED"));
    isLedTurnOpen = false;
  }                      
}

void handleNotFound() {
  server.send(404, "text/plain", "嘤嘤嘤！你访问的页面被外星人劫持了哦");
  prntln(String("用户访问了一个不存在的页面"));
}

// 打印连接状态
void printWifiStatus() {
    prnt(String(F("[WiFi] Path: '")));
    prnt(wifi_config_path);
    prnt(String(F("', Mode: '")));

    switch (wifiMode) {
        case WIFI_MODE_OFF:
            prnt(W_MODE_OFF);
            break;

        case WIFI_MODE_AP:
            prnt(W_AP);
            break;

        case WIFI_MODE_STATION:
            prnt(W_STATION);
            break;
    }
    prnt(String(F("', SSID: '")));
    prnt(wifi_config_ssid);
    prnt(String(F("', password: '")));
    prnt(wifi_config_password);
    prnt(String(F("', channel: '")));
    prnt(wifi_channel);
    prnt(String(F("', hidden: ")));
    prnt(b2s(wifi_config_hidden));
    prnt(String(F(", captive-portal: ")));
    prntln(b2s(wifi_config_captivePortal));
}

// 启动无线网络
// path 访问路径
void startAP(String path, String ssid, String password, int channel, bool hidden, bool captivePortal) {
  if(password.length() < 8) {
    prntln(W_ERROR_PASSWORD);
    return;
  }

  //配置接入点的IP，网关IP，子网掩码
  WiFi.softAPConfig(local_IP, gateway, subnet);
  
  //启动AP，并设置账号和密码
  Serial.printf("设置接入点中 ... ");
  
  //启动校验式网络（需要输入账号密码的网络）,通道为3，wifi隐藏，最大连接数=4
  WiFi.softAP(ssid.c_str(), password.c_str(), channel, hidden);

  //初始化WebServer
  server.on("/", handleRoot);
  server.on("/Switch", handleSwitch);
  server.onNotFound(handleNotFound);

  server.begin();
  wifiMode = WIFI_MODE_AP;

  prntln(W_STARTED_AP);

  //监控状态变量result 
  flag = WiFi.softAP(ssid.c_str(), password.c_str()); 
  if(flag){ 
    Serial.println("");              // 通过串口监视器输出信息
    Serial.print("当前工作模式:");     // 告知用户设备当前工作模式
    Serial.println(WiFi.getMode());
    Serial.print("接入点名字:");    
    Serial.println(ssid);            // 告知用户建立的接入点WiFi名
    Serial.print("接入点密码:");        
    Serial.println(password);        // 告知用户建立的接入点WiFi密码   
    Serial.println("网络IP");
    Serial.println(local_IP);     //打印ip地址
    Serial.println("网关IP");
    Serial.println(gateway);        //打印网关IP
    Serial.println("子网掩码：");
    Serial.println(subnet);         //打印子网掩码
  }else{
    //若没有开启成功
    Serial.println("开启失败");
  }
//  printWifiStatus();
}

void startAP() {
  startAP(wifi_config_path.c_str(), wifi_config_ssid.c_str(), wifi_config_password.c_str(), wifi_channel, wifi_config_hidden, wifi_config_captivePortal);
}

// 加载wifi默认配置
void loadWifiConfigDefaults() {
    wifi_config_hidden        = true;
    wifi_config_ssid          = DEFAULT_SSID;
    wifi_config_password      = DEFAULT_PASSWD;
    wifi_channel              = DEFAULT_CHANNEL;
    wifi_config_captivePortal = true;
    wifi_config_path          = str(W_WEBINTERFACE);
}

#endif // ifndef WifiManager_h
