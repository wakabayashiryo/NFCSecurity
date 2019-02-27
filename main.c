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

static uint16_t srv_pwr_timer;
#define __delay_srv_on(ms)  srv_pwr_timer=ms

void main(void) 
{
    uint16_t open_p;
    uint16_t close_p;
    
    Device_Startup();
    
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    
    UART_Init(UART_Init_Port,BAUD_115_2K);
    
    Timer0_Init(TMR0_PRESCALER64,125);
    
    SRV_PWR = SRV_OFF;
    
    Servo_Init(Servo_Init_Pin,&LATA,2);
    TMR1IE = 0;     //Block transmitting to Servo
    
    RN4020_Init_Peripheral();
    RN4020_Init_PrivateService();
    
    while(1)
    {   
        if(MAG_SENSOR == 0) LED2 = LED_ON;
        else                LED2 = LED_OFF;
        
        switch(RN4020_Receive8ByUUID(_SERVO_COMMAND_UUID))
        {
            case _OPEN:
                if(Servo_Get_Parameter() == close_p)
                {
                    if(MAG_SENSOR == 0)
                    {
                        LED1 = LED_ON;

                        Servo_Set_Parameter(open_p);

                        SRV_PWR = SRV_ON;           
                        __delay_srv_on(1000);                        
                    }
                }    
                RN4020_Transmit16ByUUID(_STATUS_UUID,Servo_Get_Parameter());
                break;
                
            case _CLOSE:
                if(Servo_Get_Parameter() == open_p)
                {
                    if(MAG_SENSOR == 0)
                    {
                        LED1 = LED_ON;

                        Servo_Set_Parameter(close_p);

                        SRV_PWR = SRV_ON;
                        __delay_srv_on(1000);
                    }
                }
                RN4020_Transmit16ByUUID(_STATUS_UUID,Servo_Get_Parameter());
                break;
                
            case _OPEN_PARAM:
                open_p = RN4020_Receive16ByUUID(_SERVO_PARAM_UUID);
                RN4020_Transmit16ByUUID(_STATUS_UUID, open_p);
                break;

            case _CLOSE_PARAM:
                close_p = RN4020_Receive16ByUUID(_SERVO_PARAM_UUID);
                RN4020_Transmit16ByUUID(_STATUS_UUID, close_p);
                Servo_Set_Parameter(close_p);
                TMR1IE = 1;
                break;
                    
            default:
                break;
        }
    }       
}

void interrupt Handler(void)
{
    if(Timer0_CheckFlag())
    {
        if(srv_pwr_timer>0)
            srv_pwr_timer--;
        else
        {   LED1 = LED_OFF; SRV_PWR = SRV_OFF;   }
    }
    Servo_Transmit_Interrupt();
    UART_Interrupt();
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

void UART_Init_Port(void)
{
    TRISC |= (1<<6);      //set RC5 input for UART RX
}