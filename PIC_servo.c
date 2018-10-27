#include "main.h"

/*
 * memo:
 *  *required specifications
 *      system clock : 32MHz 
 *      deveice has Timer1
 *  
 */

static uint16_t srv_param = _SERVO_PARAM_MIN;

static volatile uint8_t *SigPort;
static uint8_t SigPin_Mask;

#define Signal_High() *SigPort |= (uint8_t) SigPin_Mask
#define Signal_Low()  *SigPort &= (uint8_t)~SigPin_Mask

void Servo_Init(Servo_Init_PORTTypedef Servo_InitPort,volatile uint8_t *Signal_PORT,uint8_t  Signal_Pin)
{
    Servo_InitPort();
    
    SigPort = Signal_PORT;
    SigPin_Mask = (uint8_t)(1<<Signal_Pin);
    
    Signal_Low();
    
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
}

void Servo_Set_Parameter(uint16_t param)
{
    if(param<_SERVO_PARAM_MIN)
        param = _SERVO_PARAM_MIN;
    else if(param>_SERVO_PARAM_MAX)
        param = _SERVO_PARAM_MAX;
    
    srv_param = param;
}

void Servo_Transmit_Interrupt(void)
{
    if(TMR1IF&&TMR1IE)
    {
        if(((*SigPort)&SigPin_Mask) == SigPin_Mask)
        {
            Signal_Low();                    //toggle signal 
            TMR1 = 0xFFFF-20000+srv_param;   //set time of low pulse width
        }
        else
        {
            Signal_High();                   //toggle signal 
            TMR1 = 0xFFFF-srv_param;         //set time of high pulse width
        }
        TMR1IF = 0;
    }
 }