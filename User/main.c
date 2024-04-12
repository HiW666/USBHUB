#include "stm32f10x.h"                  // Device header
#include "oled.h"                 
#include "Key.h"  
#include  "dht11.h"
#include  "wendu.h"
#include "aida64.h"          
#include "pclcd.h"  
#include "warn.h"  
#include "pctime.h"  
#include "AD.h"  
#include "adc.h"  
#include "usbinit.h"  
#include "usbkey.h" 

int cx=5;//程序数目
int a=0;
int key=1;//主页按键标志位
int k;//读取键值
void keyread ();
void warncx();
void usbcx ();
void kaiji ();
void wenduio ();

int main(void)
{
OLED_Init();//oled驱动
kaiji ();//开机动画
Key_Init();//按键驱动
Serial_Init();//数据帧驱动
AD_Init( );
usbKey_Init();
OLED_Clear(); //清除屏幕
	while (1)
	{
 wenduio();//cpu温度高于设计b15输出高电平
keyread ();//按键处理
switch(key)
   {
   case 0 :
   key= 5;
   break;

   case 1 :  //程序1 
      adc();//功率监控
      break;


   case 2 : //程序2
   usbcx();//usb控制
      break;

   case 3 ://程序3
     wendu (); //读取温湿度
      break;

    case 4://程序4
     rewarn ();//红温显示
     //OLED_ShowNum(80,4, pccpu (),2,16);//现在温度
      warncx();
      break;

   case 5://程序5
      pclcd ();//读取电脑温度
      break;

case 6:
      key=1;
      break;
	 }
  }
}


void keyread ()//按键处理
{
k=Key_GetNum();

if(k==3)
{
key++;
OLED_Clear(); 
}
else if(k==1)
{
key--;
OLED_Clear(); 
}
else if (k==2)
{
a=1;
}
else if (k==4)
{

}
}

void warncx()//cpu高温警告程序
{

warn ();//设置红温温度
     OLED_ShowNum(0,2,warnnum(),3,16);//温度
     while(a)
      {
      k=Key_GetNum();
      warnkey(k);
       OLED_ShowNum(0,2,warnnum(),3,16);//温度
     OLED_ShowString(40,4,"setup");
          if (k==4)
          {
           a=0;
            OLED_Clear(); 
           }
        }

}

void usbcx ()//usb控制程序
{
usb();
 while(a)
      {
   usbs ();
 k=usbkeys(k);
          if (k==4)
          {
           a=0;
            OLED_Clear(); 
           }
        }
}

void kaiji ()//开机动画
{
OLED_DrawBMP(30,0,90,8,gImage_cl);
//OLED_ShowString(,6,"Ciallo");
Delay_ms(1000);
OLED_Clear(); 
OLED_DrawBMP(0,0,60,8,gImage_cl);
OLED_ShowString(80,0,"Ciallo");
OLED_ShowString(80,4,"V1.0");
OLED_ShowString(80,6,"Apaha");
Delay_ms(2000);
}

void wenduio ()//cpu温度警告
{
if (warnnum ())
{
if( pccpu ()>=warnnum () )
{ 
GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_SET);
}
else {
GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_RESET);
}

}
}