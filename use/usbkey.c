#include "stm32f10x.h"                  // Device header        
#include "OLED.h"
#include "Key.h"  

int u1=1,u2=1,u3=1,u4=1,u5=1,u6=1;
int ks;
int ux=1;
int uu;
void usb()
{
OLED_ShowString(0,6,"1=ON,4=OFF");
OLED_ShowString(0,0,"USB1 ");
OLED_ShowNum(40,0,u1,1,16);//温度
if(u1==1)
{
GPIO_WriteBit(GPIOB, GPIO_Pin_13, 1);
}
else
{
GPIO_WriteBit(GPIOB, GPIO_Pin_13, 0);
}


OLED_ShowString(60,0,"USB2 ");
OLED_ShowNum(100,0,u2,1,16);//温度
if(u2==1)
{
GPIO_WriteBit(GPIOB, GPIO_Pin_14, 1);
}
else
{
GPIO_WriteBit(GPIOB, GPIO_Pin_14, 0);
}

OLED_ShowString(0,2,"USB3 ");
OLED_ShowNum(40,2,u3,1,16);//温度
if(u3==1)
{
GPIO_WriteBit(GPIOB, GPIO_Pin_5, 1);
}
else
{
GPIO_WriteBit(GPIOB, GPIO_Pin_5, 0);
}

OLED_ShowString(60,2,"USB4 ");
OLED_ShowNum(100,2,u4,1,16);//温度
if(u4==1)
{
GPIO_WriteBit(GPIOB, GPIO_Pin_6, 1);
}
else{
GPIO_WriteBit(GPIOB, GPIO_Pin_6, 0);
}

OLED_ShowString(0,4,"USB5 ");
OLED_ShowNum(40,4,u5,1,16);//温度
if(u5==1)
{
GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1);
}
else
{
GPIO_WriteBit(GPIOB, GPIO_Pin_7, 0);
}
}

void usbs ()
{
usb();
 
switch(ux)
   {
   case 0 :
   ux=5;
   break;
  
   case 1 :  
     OLED_ShowString(50,0,"+");
   if(uu==1)
    {
     u1=-(u1+1);
     uu=0;
     }
      break;


   case 2 : 
     OLED_ShowString(110,0,"+");
    if(uu==1)
    {
     u2=-(u2+1);
     uu=0;
     }
      break;

   case 3 :
    OLED_ShowString(50,2,"+");
    if(uu==1)
    {
     u3=-(u3+1);
     uu=0;
     }
      break;

    case 4:
   OLED_ShowString(110,2,"+");
   if(uu==1)
    {
     u4=-(u4+1);
     uu=0;
     }
      break;

   case 5:   
OLED_ShowString(50,4,"+");
if(uu==1)
    {
     u5= -(u5+1);
     uu=0;
     }
      break;

case 6:
      ux=1;
      break;
	 }
}

int usbkeys (int kk)
{
ks=Key_GetNum();

if(ks==3)
{
ux++;
OLED_Clear(); 
}
else if(ks==1)
{
ux--;
OLED_Clear(); 
}
else if (ks==2)
{
uu=1;
OLED_Clear();
}
else if (ks==4)
{
kk=4;
}
return kk;
}
