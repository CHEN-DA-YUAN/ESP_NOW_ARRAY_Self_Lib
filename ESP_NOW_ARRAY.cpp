#include "ESP_NOW_ARRAY.h"
#include <string.h>

extern uint8_t robotMacAddress[];     //接收器的Mac码
extern uint8_t broadcastAddress[];    //发射器的Mac码
extern int32_t finArray[CONTROL_CHANNELS];  //专门用来转运receivedArray[]数据的数组

int32_t receivedArray[CONTROL_CHANNELS];
bool peerAdded = false;

// 发送回调
void onDataSend(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
    Serial.print("发送状态: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "成功" : "失败");
}

// 接收回调
void onDataReceive(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
    // 长度校验
    if (len != sizeof(int32_t) * CONTROL_CHANNELS) {
        Serial.printf("警告: 收到错误长度数据 (%d bytes)，已丢弃\n", len);
        return;
    }

    memcpy(receivedArray, incomingData, sizeof(receivedArray));
    //ESP-NOW 底层接收到的是 20 个连续的字节（incomingData），这行代码的作用就是把这 20 个字节，
    //以“内存搬家”的方式，完整地拷贝到你定义好的 receivedArray 数组中。
    //拷贝完成后，receivedArray 到 receivedArray 就拥有了与发送端完全相同的数值
    Serial.print("ReceivedArray:[");
       
    for (int i = 0; i < CONTROL_CHANNELS; i++) {
      finArray[i]=receivedArray[i];   //转运receivedArray[]数据的数组供主程序调用
      Serial.print(receivedArray[i]);
      if (i < (CONTROL_CHANNELS-1)) Serial.print(", "); 
     }
    Serial.println("]");
    
}

void Begin_ESP_NOW() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(500);

    Serial.print("本机MAC地址: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW初始化失败!");
        return;
    }

    esp_now_register_send_cb(onDataSend);
    esp_now_register_recv_cb(onDataReceive);

    Serial.println("=== ESP-NOW已启动 ===");
}

void sendArray(int32_t data[CONTROL_CHANNELS]) {
    if (!peerAdded) {
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, robotMacAddress, 6); //使用 esp_now_add_peer() 添加白名单。
        peerInfo.ifidx = WIFI_IF_STA;
        peerInfo.channel = 0;
        peerInfo.encrypt = false;

        if (esp_now_add_peer(&peerInfo) == ESP_OK) {
            peerAdded = true;
            Serial.println("对端添加成功!");
        } else {
            Serial.println("对端添加失败!");
            return;
        }
    }

    esp_err_t result = esp_now_send(
                       robotMacAddress,
                       (uint8_t *)data,
                       sizeof(int32_t) * CONTROL_CHANNELS
    );

    if (result == ESP_OK) {
      Serial.print("SendArray:[");
      for (int i = 0; i<CONTROL_CHANNELS; i++) {
                 Serial.print(data[i]);
                 if (i <(CONTROL_CHANNELS-1)) Serial.print(", "); 
      }
    Serial.println("]");
    } else {
        Serial.println("发送错误!");
        peerAdded = false;
    }
}
