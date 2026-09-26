#include "WiFi.h"
const int ledPin = 8; // 板载蓝色LED引脚

void setup() {
  pinMode(ledPin, OUTPUT);
  // 1. 初始化串口，波特率设置为 115200
  Serial.begin(115200);
  
  // 等待串口初始化完成（防止漏掉启动时的打印信息）
  delay(1000); 
  WiFi.mode(WIFI_STA); 
  // 2. 读取并打印 ESP32-C3 的 Wi-Fi MAC 地址
  Serial.println("\n--- ESP32-C3 MAC Address Info ---");
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("---------------------------------");
}

void loop() {
 Serial.println("\n--- ESP32-C3 MAC Address Info ---");
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(ledPin, brightness);
    delay(30);
  }
  // 从亮到暗
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(ledPin, brightness);
    delay(30);
  }
   Serial.println(WiFi.macAddress());
}
