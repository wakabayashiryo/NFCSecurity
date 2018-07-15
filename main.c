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
    
    //peripheral initialize functions etc...
    
    
    while(1)
    {
        
    }       
}

void Device_Startup(void)
{

    OSCCON = 0xF0;      //8MHz(internal),PLL enable ,

    TRISA = 0x00;       //All PORTA are set output 
    ANSELA = 0x00;      //All PORTA  are set digital
    WPUA = 0x00;
    LATA = 0x00;       //zero clear
    
    TRISC = 0x20;       //set RC5 input for UART RX
    ANSELC = 0x00;    
    WPUC = 0x00;
    LATC = 0x00;       //zero clear
}

void interrupt Handler(void)
{
/*
    if(Timer0_CheckFlag())
    {
        process...
    }
 */
    
}