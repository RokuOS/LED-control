#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> 
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

StaticJsonDocument<100> doc;

WebSocketsClient webSocket;
const char* ssid = "Dinh Van Son"; //Đổi thành wifi của bạn
const char* password = "0912727411"; //Đổi pass luôn
const char* ip_host = "192.168.1.202"; //Đổi luôn IP host của PC nha
const uint16_t port = 3000; //Port thích đổi thì phải đổi ở server nữa
const char *webSocketPath = "/esp8266"; //Path đường dẫn esp8266
const char *data = "Hello Esp8266"; //Path đường dẫn esp8266

const char *switchs; // Khai báo biến switchs

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);
      }
      break;
    case WStype_TEXT:
    {
      Serial.println("Received data: " + String((char *)payload));

        DynamicJsonDocument jsonDocument(1024);
        DeserializationError error = deserializeJson(jsonDocument, payload);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }

        switchs = jsonDocument["switch"];
        Serial.println(switchs);
        if (switchs == "LED1_ON") {
        Serial.println("LED1_ON");
      } else if (switchs == "LED1_OFF") {
        Serial.println("LED1_OFF");
      }else if (switchs == "LED2_ON") {
        Serial.println("LED2_ON");
      }else if (switchs == "LED2_OFF") {
        Serial.println("LED2_OFF");
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  
  Serial.println("ESP8266 Websocket Client");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  webSocket.begin(ip_host, port, webSocketPath);
  webSocket.onEvent(webSocketEvent);
}
void loop() {
    webSocket.loop();

  //Nếu kết nối thành công
    if (webSocket.isConnected()) {
    
      String str = String(data);

      //Gửi dữ liệu lên server
    webSocket.sendTXT(str);

    delay(1000);
  }
}
