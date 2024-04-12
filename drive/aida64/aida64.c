#include "stm32f10x.h"


uint8_t RxFlag; //中断标志位
char Serial_RxPacket_CPU[20];   //第一行信息
char Serial_RxPacket_Mem[20];   //第二行信息
char Serial_RxPacket_CPUTemp[20];   //第三行信息
char Serial_RxPacket_GPUTemp[20];   //第四行信息
char Serial_RxPacket_time[20];   //时间
char Serial_RxPacket_week[20];   //日期
char Serial_RxPacket_kai[20];   //开机时间

void Serial_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;   //串口输出端口初始化
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //串口输入端口初始化
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;          //串口初始化
    USART_InitStructure.USART_BaudRate=9600;        //波特率9600
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;   //无硬件流控制
    USART_InitStructure.USART_Mode=USART_Mode_Rx;   //串口模式为接收模式
    USART_InitStructure.USART_Parity=USART_Parity_No;   //无校验
    USART_InitStructure.USART_StopBits=USART_StopBits_1;    //停止位1位
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;   //串口字长8位
    USART_Init(USART1,&USART_InitStructure);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断配置
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1,ENABLE);
}

void USART1_IRQHandler()
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET){
        static uint8_t RxState=0;   //状态机的状态，初始状态为0
        static uint8_t RxDataNum=0; //字符串下标
        uint8_t RxData=USART_ReceiveData(USART1);//当前接收到的字节
        
        switch(RxState){    //根据当前状态机的状态选择处理方式
            case 0:
                if(RxData==0xFE){   //每一行信息，即每一个数据包的起始字节
                    RxState=1;      //变更状态为1，同时设置下标为0
                    RxDataNum=0;
                }
                else if(RxData==0x23)
                    {
                    RxState=1;      //变更状态为1，同时设置下标为0
                    RxDataNum=0;
                        }
                break;
            case 1:
                if(RxData==0x80)    //若第二个字节为0x80，则为第一行数据，转为状态2
                RxState=2;
                else if(RxData==0xC0)   //若第二个字节为0xC0，则为第二行数据，转为状态3
                    RxState=3;
                else if(RxData==0x94)   //若第二个字节为0x94，则为第三行数据，转为状态4
                    RxState=4;
                else if(RxData==0xD4)   //若第二个字节为0xD4，则为第一行数据，转为状态5
                    RxState=5;
                 else if(RxData==0x31)  //
                     RxState=10;
                  else if(RxData==0x32)  //
                     RxState=11;
                 else if(RxData==0x20)  //
                     RxState=12;

                break;
            case 2:
                if(RxData==0x40)    //如果接收到0x40，则表示当前行的信息接收完毕，转为状态6
                    RxState=6;
                else                //否则将当前数据添加至字符串
                    Serial_RxPacket_CPU[RxDataNum++]=RxData;
                break;
            case 3:
                if(RxData==0x40)    //如果接收到0x40，则表示当前行的信息接收完毕，转为状态7
                    RxState=7;
                else
                    Serial_RxPacket_Mem[RxDataNum++]=RxData;
                break;
            case 4:
                if(RxData==0x40)    //如果接收到0x40，则表示当前行的信息接收完毕，转为状态8
                    RxState=8;
                else
                    Serial_RxPacket_CPUTemp[RxDataNum++]=RxData;
                break;
            case 5:
                if(RxData==0x40)    
                    RxState=9;
                else
                    Serial_RxPacket_GPUTemp[RxDataNum++]=RxData;
                break;
            case 6:
                Serial_RxPacket_CPU[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break;    //在字符串末尾添'\0'表示结束，同时恢复状态为0，并变更中断标志位          
            case 7:
                Serial_RxPacket_Mem[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break; 
            case 8:
                Serial_RxPacket_CPUTemp[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break; 
            case 9:
                Serial_RxPacket_GPUTemp[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break; 
           case 10:
                  if(RxData==0x23)    //
                    RxState=13;
             else  
                   Serial_RxPacket_time[RxDataNum++]=RxData;break;
              case 11:
                  if(RxData==0x23)    //
                    RxState=14;
                else
                    Serial_RxPacket_week[RxDataNum++]=RxData;break;
              case 12:
                  if(RxData==0x23)    //
                    RxState=15;
                else
                    Serial_RxPacket_kai[RxDataNum++]=RxData;break;
              case 13:
               Serial_RxPacket_time[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break;    //在字符串末尾添'\0'表示结束，同时恢复状态为0，并变更中断标志位          
            case 14:
                Serial_RxPacket_week[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break; 
            case 15:
                Serial_RxPacket_kai[RxDataNum]='\0';    RxState=0;  RxFlag=1;   break; 
                  
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}
