/*
 * File:   main.c
 * Author: Ryo Wakabayashi
 *p
 * Created on 2018/07/15, 21:26
 */

#include "main.h"

void main(void) 
{
    Device_Startup();
    
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    
    UART_Init(UART_Init_Port,BAUD_115_2K);
    
    SRV_PWR = SRV_OFF;
    
    Servo_Init(Servo_Init_Pin,&LATA,2);
    
    RN4020_Init();
    uint8_t i = 0;
    
    while(1)
    {
//        RN4020_ReceiveByUUID(_SERVO_UUID);
//        RN4020_TransmitByUUID(_SENSOR_UUID,127);
//        RN4020_TransmitByUUID(_STATUS_UUID,63);
        SRV_PWR = SRV_ON;
        for(uint16_t agl = 1000;agl<2000;agl++)
        {
            Servo_Set_Parameter(agl);
            __delay_ms(10);
        }
        __delay_ms(50);  
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