#include "RN4020.h"
#include "RN4020cmds.h"


static inline void RN4020_Send_Command(const char* cmd)
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
    RN4020_Send_Command(_PC _SENSOR_UUID and data(02) and data(01));
    RN4020_Send_Command(_PC _SERVO_UUID  and data(08) and data(01));
    RN4020_Send_Command(_PC _STATUS_UUID and data(02) and data(01));
    RN4020_Send_Command(_PC _RELAY_UUID  and data(08) and data(01));
    RN4020_Send_Command(_R_1);                  //reboot
}

static inline uint8_t _serial2num(void)
{
    char c;
    uint8_t i,num=0,rsp;
            
    UART_Flush();

    while(UART_Available()<2);
    for(i = 0; i < 2; i++)
    {
        c = (char)UART_Receive();
        
        if(('A' <= c) && (c <= 'F'))
            num = c - 'A' + 10;  
        else if(('0' <= c) && (c <= '9'))
            num = c - '0';
        
        rsp = (uint8_t)((rsp << 4) | num);
    }
    return rsp;
}

void RN4020_TransmitByUUID(const char* uuid,uint8_t data)
{
    printf(_SUW"%s,%x\n",uuid,data);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
}

uint8_t RN4020_ReceiveByUUID(const char* uuid)
{
    printf(_SUR"%s\n",uuid);
    
    return _serial2num();
}

void RN4020_TransmitByHandle(const char* handle,uint8_t data)
{
    printf(_SHW"%s,%x\n",handle,data);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
}

uint8_t RN4020_ReceiveByHandle(const char* handle)
{
    printf(_SHR"%s\n",handle);
    
    return _serial2num();
}