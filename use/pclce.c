#include "stm32f10x.h"                  // Device header
#include "aida64.h"          
#include "OLED.h"

extern uint8_t RxFlag;
extern char Serial_RxPacket_CPU[20];
extern char Serial_RxPacket_Mem[20];
extern char Serial_RxPacket_CPUTemp[20];
	extern char Serial_RxPacket_kai[20];
void pclcd()
{
int oled=0;
   //USART1_IRQHandler();
		if(RxFlag==1){
    OLED_ShowString(64,6,"     ");
     OLED_ShowString(0,0,"CPUtemp    ^C");
		OLED_ShowString(64,0,Serial_RxPacket_CPU);
    OLED_ShowString(0,2,"GPUtemp    ^C");	
		OLED_ShowString(64,2,Serial_RxPacket_Mem);
    OLED_ShowString(0,4,"CPURPM     MHz");
	  OLED_ShowString(56,4,Serial_RxPacket_CPUTemp); 
    OLED_ShowString(0,6,"RAM");	
	   OLED_ShowString(56,6,"%");
     OLED_ShowString(32,6,Serial_RxPacket_kai);
    }
		
else
{
RxFlag=0;
OLED_ShowString(64,6,"error");
}
		

}
int pccpu ()
{

int b = (Serial_RxPacket_CPU[0] - '0')*10; // b = 1;
int c = Serial_RxPacket_CPU[1] - '0'; // b = 1;
//int d = Serial_RxPacket_CPU[2] - '0'; // b = 1;
int bc = b+c;
return bc
;
}