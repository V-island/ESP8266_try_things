#ifndef config_h
#define config_h

#define DEFAULT_ESP8266

/* ---------------------------------------------------------- */
/* ===>> !!! Uncomment the board taht you're using: !!! <<=== */
/* ---------------------------------------------------------- */

// ============== CONFIGS ==============//

#if defined(DEFAULT_ESP8266)
 // ===== LED ===== //
  #define LED_DIGITAL 
  #define LED_PIN_R 16 // NodeMCU on-board LED
  #define LED_PIN_B 2  // ESP-12 LED
#endif

// ====== WIFI HTTP ====== //
#ifndef DEFAULT_SSID
  #define DEFAULT_SSID "edt_5g"
#endif

#ifndef DEFAULT_PASSWD
  #define DEFAULT_PASSWD "edt2019.."
#endif /* ifndef DEFAULT_PASSWD */

#ifndef AP_SSID
  #define AP_SSID "esp8266_try"
#endif /* ifndef AP_SSID */

#ifndef AP_PASSWD
  #define AP_PASSWD "things"
#endif /* ifndef AP_PASSWD */

#ifndef AP_HIDDEN
  #define AP_HIDDEN false
#endif /* ifndef AP_HIDDEN */

#ifndef AP_IP_ADDR
  #define AP_IP_ADDR { 192, 168, 1, 1 }
#endif /* ifndef AP_IP_ADDR */

#endif /* ifndef config_h */
