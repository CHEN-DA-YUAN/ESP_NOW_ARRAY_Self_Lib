//-----ESP_NOW_ARRAY示例----//

#include "ESP_NOW_Array.h" 
// ESP-NOW配置
//uint8_t robotMacAddress[] =  {0x44, 0x17, 0x93, 0x76, 0x21, 0x94};
            //接收器的Mac码，通过串口获知
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
             //发射器的Mac码
           //{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}意味任何 ESP-NOW 设备发的数据它都会收。
          //如果你只想接收特定遥控器的数据，把 broadcastAddress 换成具体的 MAC 地址，并使用 esp_now_add_peer() 添加白名单。
int32_t finArray[5]; //接收数据的数组，数组名finArray不能改，后面的数字要和h文件里的#define CONTROL_CHANNELS 一致

void setup() {
  Serial.begin(115200);
  while (!Serial) {;}
  Begin_ESP_NOW(); //启动ESP_NOW
}

void loop() {
              Serial.print("finArray:[");
              for (int i = 0; i <CONTROL_CHANNELS; i++) {
                 Serial.print(finArray[i]);
                 if (i < (CONTROL_CHANNELS-1)) Serial.print(", "); 
              }
              Serial.println("]");   
              delay(5000);
  
              }
