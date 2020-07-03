#include "config.h"
#include "functions.h"

#include "wifi.h"

// 默认Led pin 为 LED_BUILTIN
void setup() {
  // 初始化串口 start serial
  Serial.begin(115200);
  prntln();

  //设置为接入点模式
  WiFi.mode(WIFI_AP);

  // load Wifi settings: SSID, password,...
  loadWifiConfigDefaults();
  
  // 启动web服务 start access point/web interface
  startAP();
}

void loop() {
  // put your main code here, to run repeatedly:
}