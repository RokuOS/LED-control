#include <SoftwareSerial.h>

// Khai báo chân kết nối với ESP8266
const int RX_PIN = 2; // Chân RX của Arduino kết nối với TX của ESP8266
const int TX_PIN = 3; // Chân TX của Arduino kết nối với RX của ESP8266

// Khai báo chân LED
const int LED1_PIN = 4; // Chân điều khiển LED 1
const int LED2_PIN = 5; // Chân điều khiển LED 2

// Tạo đối tượng SoftwareSerial
SoftwareSerial esp8266(RX_PIN, TX_PIN);

void setup() {
  // Khởi tạo Serial
  Serial.begin(115200);
  esp8266.begin(115200); // Baud rate phải trùng với cài đặt của ESP8266
  
  // Cài đặt chân LED là OUTPUT
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  // Kiểm tra xem có dữ liệu từ ESP8266 không
  if (Serial.available()) { // Nếu có dữ liệu trên cổng nối tiếp
    String switchs = Serial.readString(); // Đọc dữ liệu
    
    // So sánh lệnh nhận được và thực hiện hành động tương ứng
    if (switchs == "LED1_ON") {
      digitalWrite(LED1_PIN, HIGH);
    } else if (switchs == "LED1_OFF") {
      digitalWrite(LED1_PIN, LOW);
    } else if (switchs == "LED2_ON") {
      digitalWrite(LED2_PIN, HIGH);
    } else if (switchs == "LED2_OFF") {
      digitalWrite(LED2_PIN, LOW);
    }
  }
  
  // Có thể thêm mã để gửi dữ liệu trở lại server NodeJS nếu cần
}
