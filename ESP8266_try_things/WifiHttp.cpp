#include "WifiHttp.h"

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
