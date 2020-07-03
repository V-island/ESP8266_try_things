#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//网页
String myhtmlPage =
    String("") +
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
    "</html>";

bool isLedTurnOpen = false; // 记录LED状态

const char* ssid = "edt_5g";
const char* password = "edt2019..";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", myhtmlPage); //！！！注意返回网页需要用"text/html" ！！！
  Serial.println("用户访问了主页");
}

void handleSwitch() {
  if (isLedTurnOpen == false) {
    digitalWrite(LED_BUILTIN, LOW); // 点亮LED
    server.send(200, "text/plain", "LED has been turn on");
    Serial.println("用户开启了LED");
    isLedTurnOpen = true;
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH); // 熄灭LED
    server.send(200, "text/plain", "LED has been turn off");
    Serial.println("用户关闭了LED");
    isLedTurnOpen = false;
  }                      
}

void handleNotFound() {
  server.send(404, "text/plain", "嘤嘤嘤！你访问的页面被外星人劫持了哦");
  Serial.println("用户访问了一个不存在的页面");
}
void setup(void) {
  //初始化LED
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  //初始化串口
  Serial.begin(115200);
  Serial.println("");

  //初始化网络
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  //初始化WebServer
  server.on("/", handleRoot);
  server.on("/Switch", handleSwitch);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  //监听客户请求并处理
  server.handleClient();
}
