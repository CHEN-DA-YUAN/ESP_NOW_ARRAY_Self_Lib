#ifndef ESP_NOW_ARRAY_H
#define ESP_NOW_ARRAY_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <stdint.h>

#define CONTROL_CHANNELS 5  //这个数字要和主程序里int32_t finArray[数字] 一致

void Begin_ESP_NOW();
void sendArray(int32_t data[CONTROL_CHANNELS]);

// ✅ 适配 ESP32 Arduino Core 3.x / ESP-IDF 5.x 的新版回调签名
void onDataSend(const wifi_tx_info_t *tx_info, esp_now_send_status_t status);
void onDataReceive(const esp_now_recv_info *info, const uint8_t *incomingData, int len);

#endif
