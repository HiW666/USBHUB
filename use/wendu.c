#include "stm32f10x.h"                  // Device header        
#include "OLED.h"
#include  "dht11.h"
#include  "wendu.h"

extern unsigned int rec_data[4];

void wendu ()
{

DHT11_REC_Data(); //接收温度和湿度的数据
 OLED_ShowString(80,0,"^C");
 OLED_ShowString(80,2,"%");
OLED_ShowCHinese(0,0,0,32,Welcome); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,0,1,32,Welcome); //声明在指定位置显示汉字函数
OLED_ShowCHinese(0,2,2,32,Welcome); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,2,3,32,Welcome); //声明在指定位置显示汉字函数
OLED_ShowNum(48,0,rec_data[2],2,32);//温度
 //OLED_ShowNum(24,0,rec_data[3],2,32);//温度小数位
OLED_ShowNum(48,2,rec_data[0],2,32);//湿度
//OLED_ShowNum(24,2,rec_data[1],2,32);//湿度小数位
OLED_ShowCHinese(0,4,0,32,time); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,4,1,32,time); //声明在指定位置显示汉字函数

pctime();
}