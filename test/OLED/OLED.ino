// Example sketch for testing OLED display

// We need to include Wire.h for I2C communication
#include <Wire.h>
//#include "OLED.h"
#include "DHT.h"

#define DHTPIN 2
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Declare OLED display
// display(SDA, SCL);
// SDA and SCL are the GPIO pins of ESP8266 that are connected to respective pins of display.
//OLED display(2, 14);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
//  display.begin();
//  display.clear();
//  display.print("DHT TEST!", 0, 4);
}

void loop() {
  delay(2000);

  // 读取温度或湿度大约需要250毫秒！
  // 传感器读数也可能长达2秒“旧”（传感器速度非常慢）
  float h = dht.readHumidity();
  // 将温度读取为摄氏温度（默认值）
  float t = dht.readTemperature();
  // 将温度读取为华氏度（isFahrenheit = true）
  float f = dht.readTemperature(true);

  // 检查是否有任何读取失败并提早退出（重试）。
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("无法从DHT传感器读取！"));
    return;
  }
  
  // 计算华氏热量指数（默认值）
  float hif = dht.computeHeatIndex(f, h);
  // 计算摄氏温度指数（isFahreheit = false）
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
//  display.print("湿度: " + h + "%", 3);
//  display.print("温度: " + t + "°C " + f + "°F", 4);
//  display.print("热度指数: " + hic + "°C " + hif + "°F", 5);
}
