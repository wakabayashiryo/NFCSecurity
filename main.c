/*
 * File:   main.c
 * Author: Ryo Wakabayashi
 *
 * Created on 2018/07/15, 21:26
 */

#include "main.h"

void main(void) 
{
    Device_Startup();
    
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    
    SRV_PWR = SRV_OFF;
    
    Servo_Init(Servo_Init_Pin,&LATA,2);
    
    while(1)
    {

        SRV_PWR = SRV_ON;
        
        for(uint16_t agl = 450;agl<1000;agl++)
        {
            Servo_Set_Parameter(agl);
            __delay_ms(10);
        }
        __delay_ms(500);  
    }       
}

void Device_Startup(void)
{

    OSCCON = 0xF0;      //8MHz(internal),PLL enable ,

    TRISA  = 0x02;      //set RA1 input for sensor 
    ANSELA = 0x00;      //All PORTA  are set digital
    WPUA   = 0x00;
    LATA   = 0x00;      //zero clear
    
    TRISC  = 0x20;      //set RC5 input for UART RX
    ANSELC = 0x00;    
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
}