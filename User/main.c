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

int cx=5;//������Ŀ
int a=0;
int key=1;//��ҳ������־λ
int k;//��ȡ��ֵ
void keyread ();
void warncx();
void usbcx ();
void kaiji ();
void wenduio ();

int main(void)
{
OLED_Init();//oled����
kaiji ();//��������
Key_Init();//��������
Serial_Init();//����֡����
AD_Init( );
usbKey_Init();
OLED_Clear(); //�����Ļ
	while (1)
	{
 wenduio();//cpu�¶ȸ������b15����ߵ�ƽ
keyread ();//��������
switch(key)
   {
   case 0 :
   key= 5;
   break;

   case 1 :  //����1 
      adc();//���ʼ��
      break;


   case 2 : //����2
   usbcx();//usb����
      break;

   case 3 ://����3
     wendu (); //��ȡ��ʪ��
      break;

    case 4://����4
     rewarn ();//������ʾ
     //OLED_ShowNum(80,4, pccpu (),2,16);//�����¶�
      warncx();
      break;

   case 5://����5
      pclcd ();//��ȡ�����¶�
      break;

case 6:
      key=1;
      break;
	 }
  }
}


void keyread ()//��������
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

void warncx()//cpu���¾������
{

warn ();//���ú����¶�
     OLED_ShowNum(0,2,warnnum(),3,16);//�¶�
     while(a)
      {
      k=Key_GetNum();
      warnkey(k);
       OLED_ShowNum(0,2,warnnum(),3,16);//�¶�
     OLED_ShowString(40,4,"setup");
          if (k==4)
          {
           a=0;
            OLED_Clear(); 
           }
        }

}

void usbcx ()//usb���Ƴ���
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

void kaiji ()//��������
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

void wenduio ()//cpu�¶Ⱦ���
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