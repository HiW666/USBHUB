#include "stm32f10x.h"                  // Device header        
#include "OLED.h"
#include "Key.h" 
#include "warn.h"  
#include "pclcd.h"  

int adb= 0;

void warn ()
{

OLED_ShowCHinese(0,0,0,32,Introduced); //声明在指定位置显示汉字函数
OLED_ShowCHinese(16,0,1,32,Introduced); //声明在指定位置显示汉字函数
OLED_ShowCHinese(32,0,2,32,Introduced); //声明在指定位置显示汉字函数
OLED_ShowCHinese(48,0,3,32,Introduced); //声明在指定位置显示汉字函数
//OLED_ShowChar(0,2,c); //显示字符函数

}



void warnkey (int wk)
{
if (wk==1)
{
  adb=adb+10;
}
if (wk==3)
{
  adb=adb-10;
}

if (adb==130)
{
adb= 0;
}
if(adb == -10)
{
 adb=120;
}
 if(adb == 10)
{
 adb=60;
}
 if(adb ==50)
{
 adb= 0;
}
}

int warnnum () //设定温度
{
return adb;
}

void rewarn ( )
{
if (warnnum ())
{
if( pccpu ()>=warnnum () )
{ 
OLED_ShowCHinese(0,6,0,32,redwen); //红
OLED_ShowCHinese(16,6,1,32,redwen); //温
OLED_ShowCHinese(32,6,2,32,redwen); //啦

}
else {
 OLED_ShowString(0,6,"             ");
}
}

}
