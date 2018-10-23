#include "RN4020.h"
#include "RN4020cmds.h"


static void RN4020_Send_Command(const char* cmd)
{    
    UART_Flush();
    
    puts(cmd);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
    
    LED2 = !LED2;
}

void RN4020_Init(void)
{    
    _RN4020_WAKE_SW = 1;
    _RN4020_WAKE_HW = 1;

    RN4020_Send_Command(_SF data(1));           //factory reset,
    RN4020_Send_Command(_SB data(4));           //UART baudrate is 115200bps
    RN4020_Send_Command(_SR data(24000000));    //Peripheral and auto advertise,No Direct Advertisement
    RN4020_Send_Command(_SS data(80040001));    //use service DeviceInformation,TX Power,Private service

    RN4020_Send_Command(_PZ);                   //Claer private service    
    RN4020_Send_Command(_PS _PRIVATE_SERVICE);
    RN4020_Send_Command(_PC _PRIVATE_UUID1 and data(0A) and data(01));
    RN4020_Send_Command(_PC _PRIVATE_UUID2 and data(0A) and data(01));
    
    RN4020_Send_Command(_R_1);                  //reboot
}

uint8_t RN4020_Get_ServoParameter(void)
{
    char *buff[10];
    char c,j = 0;
    uint8_t tmp,val = 0;
    
    UART_Flush();
    
    printf(_SUR"%s\n",_PRIVATE_UUID2);
    
    while(UART_Available()==0);
    UART_Receive();
    UART_Receive();
//    while(UART_Available()!=0)
//    {
        for(int i = 0; i < (2 * 1); i++)
        {
            c = (char)UART_Receive();

            tmp = 0;
            if((c >= 'A') && (c <= 'F'))
            {
                tmp = c - 'A' + 10;  
            }else if((c >= '0') && (c <= '9'))
            {
                tmp = c - '0';  
            }
            val = ( val << 4 ) + tmp;
        }
//    }
        
//    if(buff=="38")LED1 = LED_ON;
    
//    return (uint8_t)atoi(buff);
    return val;
}   

void RN4020_Set_MagneticSensor(uint8_t data)
{
    UART_Flush();
    
    printf(_SUW"%s,%d\n",_PRIVATE_UUID1,data);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
    LED2 = !LED2;
}

//TODO
/*
 *   void RN4020_TransmitByUUID(const char* uuid,uint8_t data)
 *  void RN4020_TransmitByHandle(const char* handle,uint8_t data)
*/