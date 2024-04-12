
#include "stm32f10x.h"                  // Device header        
#include "OLED.h"
#include "AD.h"


int ad0,ad1;
int ad2;

float AD0, AD1,AD2;
void adc ()
{
OLED_ShowCHinese(0,0,0,32,ADC); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,0,1,32,ADC); //声明在指定位置显示汉字函数
 OLED_ShowString(42,0,".");
ad0 =AD_GetValue(ADC_Channel_0);
AD0 = (float)ad0/ 4095 * 6.6; //电阻分压
//OLED_ShowNum(32,2,ad0,4,16);//电压 
OLED_ShowNum(32,0,AD0,1,16);//电压
OLED_ShowNum(48,0,(int)(AD0 * 100) % 100,2,16);//电压


OLED_ShowCHinese(0,2,2,32,ADC); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,2,3,32,ADC); //声明在指定位置显示汉字函数
OLED_ShowString(42,2,".");
ad1= AD_GetValue(ADC_Channel_1);
AD1 = (((float)ad1/ 4095 * 3.3)-2.5)/0.185; //电阻分压  2.5 + 0.185*Ip ACS712公式
if (AD1<0)
{
AD1=0;
}
OLED_ShowNum(32,2,AD1,1,16);//
OLED_ShowNum(48,2,(int)(AD1 * 100) % 100,2,16);//电压

OLED_ShowCHinese(0,4,4,32,ADC); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,4,5,32,ADC); //声明在指定位置显示汉字函数
AD2=AD1*AD0;
ad2=(int)AD2;
OLED_ShowNum(32,4,ad2,1,16);//
OLED_ShowNum(48,4,(int)(AD2 * 100) % 100,2,16);//电压
}

