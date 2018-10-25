/* 
 * File:   PIC_servo.h
 * Author: evaota
 *
 * Created on 2018/09/04, 15:36
 */

#ifndef PIC_SERVO_H
#define	PIC_SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _SERVO_PARAM_MIN    500
#define _SERVO_PARAM_MAX    10000
    

typedef void (*Servo_Init_PORTTypedef)(void);


void Servo_Init(Servo_Init_PORTTypedef Servo_InitPort,volatile uint8_t *Signal_PORT,uint8_t  Signal_Pin);

void Servo_Set_Parameter(uint16_t param);

void Servo_Transmit_Interrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC_SERVO_H */

