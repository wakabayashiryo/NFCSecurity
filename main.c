/*
 * File:   main.c
 * Author: Ryo Wakabayashi
 *p
 * Created on 2018/07/15, 21:26
 */

#include "main.h"

#define _CLOSE          0
#define _OPEN           1
#define _CLOSE_PARAM    2
#define _OPEN_PARAM     3

void main(void) 
{
    Device_Startup();
    
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    
    UART_Init(UART_Init_Port,BAUD_115_2K);
    
    SRV_PWR = SRV_OFF;
    
    Servo_Init(Servo_Init_Pin,&LATA,2);
    
    RN4020_Init_Peripheral();
    RN4020_Init_PrivateService();
    
    uint16_t srv_open,srv_close;
    while(1)
    {
        switch(RN4020_Receive8ByUUID(_SWITCH_SERVO_UUID))
        {
            case _CLOSE:
                break;
            case _OPEN:
                break;
            case _CLOSE_PARAM:
                srv_open = RN4020_Receive16ByUUID(_SERVO_PARAM_UUID);
                RN4020_Transmit16ByUUID(_STATUS_UUID, srv_open);
                break;
            case _OPEN_PARAM:
                srv_close = RN4020_Receive16ByUUID(_SERVO_PARAM_UUID);
                RN4020_Transmit16ByUUID(_STATUS_UUID, srv_close);
                break;
            default:
                break;
        }
    }       
}

void Device_Startup(void)
{

    OSCCON = 0xF0;      //8MHz(internal),PLL enable ,

    TRISA  = 0x02;      //set RA1 input for sensor.others pin is output 
    ANSELA = 0x00;      //All PORTA  are set digital
    WPUA   = 0x00;
    LATA   = 0x00;      //zero clear
    
    TRISC  = 0x00;      //All pin is set output
    ANSELC = 0x00;      //All PORTC are set digital
    WPUC   = 0x00;
    LATC   = 0x00;      //zero clear
}

void Servo_Init_Pin(void)
{
    TRISA  &= ~(1<<2);
    ANSELA &= ~(1<<2);
}

void interrupt Handler(void)
{
    Servo_Transmit_Interrupt();
    UART_Interrupt();
}

void UART_Init_Port(void)
{
    TRISC |= (1<<6);      //set RC5 input for UART RX
}