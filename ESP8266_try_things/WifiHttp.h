#pragma once
#ifndef WifiHttp_h
#define WifiHttp_h

#include <ESP8266WiFi.h>
#include "config.h"

class WifiHttp {
  public:
    void join();
    void printWifiStatus();

    void getWebHtml(String hostUrl, int httpPort = 80);

  private:
    String url;
};

#endif