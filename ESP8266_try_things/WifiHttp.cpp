#include "WifiHttp.h"

// 连接WIFI
void WifiHttp::join() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(DEFAULT_SSID);
  WiFi.begin(DEFAULT_SSID, DEFAULT_PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WifiHttp::getWebHtml(String hostUrl, int httpPort) {
  WiFiClient client;
  
  if(!client.connect(hostUrl, httpPort)) {
    Serial.println("connection failed");
  }

  // 发送request请求
  client.print(String("GET /") + " HTTP/1.1\r\n" + "Host: " + hostUrl + "\r\n" + "Connection: close\r\n\r\n");
  delay(10);
  
  // 输出
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}