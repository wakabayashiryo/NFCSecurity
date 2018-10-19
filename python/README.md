# Description of This Library

- ## About this library
    can use only central mode (point to point communication)

- ## Configrations 
    |contents|parameter|
    |:--:|:------|
    |pulse polarity|rise edge|
    |prescaler|1:4|

- ## Required specification
    - must use system clock 32MHz
    - have 2 GPIO pins

- ## Others necessary libary
    - Timer1
    - I2C  

- ## Description of some functions
    1. intialize hoge   
        `uint8_t hoge_Init(uint8_t hoge,uint8_t hage);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|uint8_t|hoge|parameter for initialize|
        |        |uint8_t|hage|hage parameter|
        |return|uint8_t|--|Success or failure|
    
    1. test functioin    
        `uint8_t hoge_Send(uint8_t hoge,uint8_t hage);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|uint8_t|hoge|parameter for initialize|
        |        |uint8_t|hage|hage parameter|
        |return|uint8_t|--|Success or failure|
        

- ## How to use?
    - ### sample code
    ~~~C
    #include "main.h"

    void Basic_Init(void);

    void main(void)
    {
        Basic_Init();

        while(1)
        {
            printf("Hello World");   
        }    
    }

    void Basic_Init(void)
    {
        OSCCON = 0xF0;      //PLL ON: 
                            //internal Oscilltor is 32MHz
                            //clock source is internal one.
        
        TRISA = 0x00;       //All PORTA is output 
        ANSELA = 0x00;      //All PORTA  is digital
        WPUA = 0x00;        

        PORTA = 0x00;       //clear
    }

    void interrupt Handler(void)
    {
        hoge_Interrupt();
    }
    ~~~

- ## History
    |version  |date|contents |
    |:-----:|:-------:|:----------------:|
    |ver1.0 |20xx/1/1|added README for this library|

- ## License information
    This software is released under the MIT License, see LICENSE