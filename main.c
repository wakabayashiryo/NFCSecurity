/*
 * File:   main.c
 * Author: Ryo Wakabayashi
 *
 * Created on 2018/07/15, 21:26
 */

#include "main.h"

uint16_t srv_param = 200;

void main(void) 
{
    Device_Startup();
    
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    
    SRV_PWR = SRV_OFF;
    SRV_SIG = 0;
    
    T1CON  = 0x00;
    T1CON &= ~(3<<6);   //clock source is instruction clock (fosc/4)
    T1CON |= (3<<4);    //input prescaler is 1:8 (1count per 1us)
    
    T1GCON = 0x00;      //not use gate
    
    TMR1H  = 0x00;
    TMR1L  = 0x00;
    
    TMR1   = 0xFFFF-srv_param;
    
    TMR1IE = 1;
    TMR1IF = 0;
    PEIE   = 1;
    GIE    = 1;
    
    T1CON |= (1<<0);    //Timer1 on

    //peripheral initialize functions etc...
    
    
    while(1)
    {
        SRV_PWR = SRV_ON;
        
        for(uint16_t agl = 200;agl<2000;agl++)
        {
            srv_param = agl;
            __delay_ms(10);
        }
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

void interrupt Handler(void)
{

    if(TMR1IF&&TMR1IE)
    {
        if(SRV_SIG == 1)
        {
            SRV_SIG = 0;                    //toggle signal 
            TMR1 = 0xFFFF-10000-srv_param;   //set time of low pulse width
        }
        else
        {
            SRV_SIG = 1;                    //toggle signal 
            TMR1 = 0xFFFF-srv_param;         //set time of high pulse width
        }
        TMR1IF = 0;
    }
}