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
    
    uint16_t srv_data;
    while(1)
    {
//        if(MAG_SENSOR==0)
//            RN4020_TransmitByUUID(_SENSOR_UUID,127);
//        else
//            RN4020_TransmitByUUID(_SENSOR_UUID,0);
//
//        
//        if(RN4020_ReceiveByUUID(_RELAY_UUID)==127)
//        {
//            SRV_PWR = SRV_ON;
//            LED1 = LED_ON;
//        }
//        else
//        {
//            LED1 = LED_OFF;
//            SRV_PWR = SRV_OFF;
//        }
        srv_data = RN4020_ReceiveByUUID(_SERVO_UUID);
        if(srv_data == 12000)
            LED1 = LED_ON;
        RN4020_TransmitByUUID(_STATUS_UUID, srv_data);
//        RN4020_TransmitByUUID(_STATUS_UUID,65530);
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