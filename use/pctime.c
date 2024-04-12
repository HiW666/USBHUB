#include "stm32f10x.h"                  // Device header
#include "aida64.h"          
#include "OLED.h"

extern  uint8_t RxFlag;
extern char Serial_RxPacket_time[20];
//extern char Serial_RxPacket_GPUTemp[20];
// extern char Serial_RxPacket_week [20];

void pctime()
{
		if(RxFlag==1){
    // OLED_ShowString(56,6,"     ");
		//OLED_ShowString(0,0,"CPUtemp   ^C");
		OLED_ShowString(32,4,Serial_RxPacket_time);
	//	OLED_ShowString(0,2,"GPUtemp   ^C");
	//	OLED_ShowString(0,4,"CPURPM     MHz");
	 //OLED_ShowString(0,4,Serial_RxPacket_kai);
  //  OLED_ShowString(0,6,"RAM");
	//OLED_ShowString(32,6,Serial_RxPacket_GPUTemp);
		}
    else
      {
      RxFlag=0;
      OLED_ShowString(32,4,"error");
      }
}
		