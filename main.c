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
    
    UART_Init(UART_Init_Port,BAUD_115_2K);
    
    SRV_PWR = SRV_OFF;
    
    Servo_Init(Servo_Init_Pin,&LATA,2);
    
    _RN4020_WAKE_SW = 1;
    _RN4020_WAKE_HW = 1;

    RN4020_Send_Command("SF,","1");         //factory reset,
    RN4020_Send_Command("SB,","4");
    RN4020_Send_Command("SR,","20000000");
    RN4020_Send_Command("SS,","80040001");
    RN4020_Send_Command("PZ,","");
    RN4020_Send_Command("R,","1");
    __delay_ms(1000);
    
    RN4020_Send_Command("PS,",SERVICE_UUID);
    RN4020_Send_Command("PC,",CHARACTERISTIC_UUID);
    
    RN4020_Send_Command("R,","1");
    __delay_ms(1000);
    
//    RN4020_Send_Command("A","");

    while(1)
    {
//        LED2 = LED_ON;
        
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