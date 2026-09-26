#include "ESP_NOW_Array.h"

int32_t finArray[CONTROL_CHANNELS]; //不管是发射端和接收端都要有这一句
int32_t A[CONTROL_CHANNELS] = {100, 200, 300, 400, 500};

uint8_t robotMacAddress[]  = {0x00, 0x4B, 0x12, 0xEB, 0xC2, 0x88};  //接收器的Mac码，通过串口获知
//uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void setup() {
    Serial.begin(115200);
    while (!Serial) {;}
    Begin_ESP_NOW();
}

void loop() {
    sendArray(A);  // 传数组名
    delay(2000);
}
