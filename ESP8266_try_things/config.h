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
#define DEFAULT_SSID "edt_5gg"
#endif

#ifndef DEFAULT_PASSWD
#define DEFAULT_PASSWD "edt2019.."
#endif /* ifndef DEFAULT_PASSWD */

#ifndef DEFAULT_CHANNEL
#define DEFAULT_CHANNEL 1
#endif /* ifndef DEFAULT_CHANNEL */


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

// ============== language ==============//

extern String str(const char* ptr);
extern String keyword(const char* keywordPtr);
extern bool eqls(const char* str, const char* keywordPtr);
extern bool eqls(String str, const char* keywordPtr);
extern String b2s(bool input);
extern String b2a(bool input);
extern bool s2b(String input);
extern void prnt(const String s);
extern void prnt(const bool b);
extern void prnt(const char c);
extern void prnt(const char* ptr);
extern void prnt(const char* ptr, int len);
extern void prnt(const int i);
extern void prnt(const uint32_t i);
extern void prntln();
extern void prntln(const String s);
extern void prntln(const bool b);
extern void prntln(const char c);
extern void prntln(const char* ptr);
extern void prntln(const char* ptr, int len);
extern void prntln(const int i);
extern void prntln(const uint32_t i);

// ===== GLOBAL STRINGS ===== //

// Often used characters, therefor in the RAM
const char CURSOR              = '|';
const char SPACE               = ' ';
const char DOUBLEPOINT         = ':';
const char EQUALS              = '=';
const char HASHSIGN            = '#';
const char ASTERIX             = '*';
const char PERCENT             = '%';
const char DASH                = '-';
const char QUESTIONMARK        = '?';
const char ZERO                = '0';
const char S                   = 's';
const char M                   = 'm';
const char D                   = 'd';
const char DOUBLEQUOTES        = '\"';
const char SLASH               = '/';
const char NEWLINE             = '\n';
const char CARRIAGERETURN      = '\r';
const char SEMICOLON           = ';';
const char BACKSLASH           = '\\';
const char POINT               = '.';
const char VERTICALBAR         = '|';
const char COMMA               = ',';
const char ENDOFLINE           = '\0';
const char OPEN_BRACKET        = '[';
const char CLOSE_BRACKET       = ']';
const char OPEN_CURLY_BRACKET  = '{';
const char CLOSE_CURLY_BRACKET = '}';

const char STR_TRUE[] PROGMEM = "true";
const char STR_FALSE[] PROGMEM = "false";
const char STR_MIN[] PROGMEM = "min";

// ===== WIFI ===== //
const char W_STOPPED_AP[] PROGMEM = "Stopped Access Point";
const char W_AP_REQUEST[] PROGMEM = "[AP] request: ";
const char W_AP[] PROGMEM = "AP";
const char W_STATION[] PROGMEM = "Station";
const char W_MODE_OFF[] PROGMEM = "OFF";
const char W_MODE_AP[] PROGMEM = "AP";
const char W_MODE_ST[] PROGMEM = "STATION";
const char W_OK[] PROGMEM = " OK";
const char W_NOT_FOUND[] PROGMEM = " NOT FOUND";
const char W_BAD_ARGS[] PROGMEM = "BAD ARGS";
const char W_BAD_PATH[] PROGMEM = "BAD PATH";
const char W_FILE_NOT_FOUND[] PROGMEM = "ERROR 404 File Not Found";
const char W_STARTED_AP[] PROGMEM = "Started AP";

#endif /* ifndef config_h */
