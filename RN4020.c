#include "RN4020.h"
#include "RN4020_Cmds.h"


static void RN4020_Send_Command(const char* cmd)
{    
    UART_Flush();
    
    puts(cmd);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
    
    LED2 = !LED2;
}

void RN4020_Init_PP(void)
{    
    _RN4020_WAKE_SW = 1;
    _RN4020_WAKE_HW = 1;

    RN4020_Send_Command(_SF data(1));           //factory reset,
    RN4020_Send_Command(_SB data(4));           //UART baudrate is 115200bps
    RN4020_Send_Command(_SR data(24000000));    //Peripheral and auto advertise,No Direct Advertisement
    RN4020_Send_Command(_SS data(80040001));    //use service DeviceInformation,TX Power,Private service

    RN4020_Send_Command(_PZ);                   //Claer private service    
    RN4020_Send_Command(_PS _PRIVATE_SERVICE);
    RN4020_Send_Command(_PC _PRIVATE_UUID1 and data(02) and data(08));
    RN4020_Send_Command(_PC _PRIVATE_UUID2 and data(08) and data(08));
    
    RN4020_Send_Command(_R_1);                  //reboot
}

uint8_t RN4020_Get_ServoParameter(void)
{
    printf(_SUR"%s\n",_PRIVATE_UUID1);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='R');
    while((char)UART_Receive()!=',');
    
    return UART_Receive();
}   

void RN4020_Set_MagneticSensor(uint8_t data)
{
    printf(_SUW"%s,%0x\n",_PRIVATE_UUID2,data);
    
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
}
