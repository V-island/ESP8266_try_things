#include "WifiHttp.h"

// Run-Time Variables //
WifiHttp wifihttp;

// 默认Led pin 为 LED_BUILTIN
void setup() {
  Serial.begin(115200);
  wifihttp.join();
}

void loop() {
  // put your main code here, to run repeatedly:
}
