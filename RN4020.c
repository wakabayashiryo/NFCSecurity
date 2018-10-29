#include "RN4020.h"
#include "RN4020cmds.h"

static inline void _wait_linefeed(void)
{
    while(UART_Available()==0);
    while((char)UART_Receive()!='\n');
}

static inline void _send_command(const char* cmd)
{    
    UART_Flush();
    
    puts(cmd);
    
    _wait_linefeed();
    
    LED2 = !LED2;
}

/*this function convert serial data that is big-endian order*/
static inline uint32_t _serial2num(uint8_t bytes)
{
    char c;
    uint8_t i,num=0;
    uint8_t getlen = (uint8_t)(bytes * 2);
    uint32_t rsp = 0;
            
    UART_Flush();

    while(UART_Available()<getlen);
    
    for(i = 0; i < getlen; i++)
    {
        c = (char)UART_Receive();
        
        if(('A' <= c) && (c <= 'F'))
            num = c - 'A' + 10;  
        else if(('0' <= c) && (c <= '9'))
            num = c - '0';
        
        rsp = (uint32_t)((rsp << 4) + num);
    }
    return rsp;
}

void RN4020_Init_Peripheral(void)
{    
    _RN4020_WAKE_SW = 1;
    _RN4020_WAKE_HW = 1;

    _send_command(_SF data(1));           //factory reset,
    _send_command(_SB data(4));           //UART baudrate is 115200bps
    _send_command(_SR data(24000000));    //Peripheral and auto advertise,No Direct Advertisement
    _send_command(_SS data(80040001));    //use service DeviceInformation,TX Power,Private service

    _send_command(_R_1);                  //reboot
}

void RN4020_Init_PrivateService(void)
{
    _send_command(_PZ);                   //Claer private service    
    _send_command(_PS _PRIVATE_SERVICE);
    _send_command(_PC _SERVO_UUID  and data(08) and data(02));
    _send_command(_PC _STATUS_UUID and data(02) and data(02));
    
    _send_command(_R_1);                  //reboot
}


void RN4020_Transmit8ByUUID (const char* uuid,uint8_t  data)
{
    printf(_SUW"%s,%02x\n",uuid,data);
    
   _wait_linefeed();
}

void RN4020_Transmit16ByUUID(const char* uuid,uint16_t data)
{
    printf(_SUW"%s,%04x\n",uuid,data);
    
   _wait_linefeed();
}

void RN4020_Transmit32ByUUID(const char* uuid,uint32_t data)
{
    printf(_SUW"%s,%08lx\n",uuid,data);
    
   _wait_linefeed();
}

uint8_t  RN4020_Receive8ByUUID (const char* uuid)
{
    printf(_SUR"%s\n",uuid);
    
    return (uint8_t)_serial2num(1);
}

uint16_t RN4020_Receive16ByUUID(const char* uuid)
{
    printf(_SUR"%s\n",uuid);
    
    return (uint16_t)_serial2num(2);
}

uint32_t RN4020_Receive32ByUUID(const char* uuid)
{
    printf(_SUR"%s\n",uuid);
    
    return (uint32_t)_serial2num(4);
}



void RN4020_Transmit8ByHandle (const char* handle,uint8_t  data)
{
    printf(_SHW"%s,%02x\n",handle,data);
    
   _wait_linefeed();
}

void RN4020_Transmit16ByHandle(const char* handle,uint16_t data)
{
    printf(_SHW"%s,%04x\n",handle,data);
    
   _wait_linefeed();
}

void RN4020_Transmit32ByHandle(const char* handle,uint32_t data)
{
    printf(_SHW"%s,%08lx\n",handle,data);
    
   _wait_linefeed();
}

uint8_t  RN4020_Receive8ByHandle (const char* handle)
{
    printf(_SHR"%s\n",handle);
    
    return (uint8_t)_serial2num(1);
}

uint16_t RN4020_Receive16ByHandle(const char* handle)
{
    printf(_SHR"%s\n",handle);
    
    return (uint16_t)_serial2num(2);
}

uint32_t RN4020_Receive32ByHandle(const char* handle)
{
    printf(_SHR"%s\n",handle);
    
    return (uint32_t)_serial2num(4);
}
