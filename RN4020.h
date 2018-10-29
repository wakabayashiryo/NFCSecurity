/* 
 * File:   RN4020.h
 * Author: evaota
 *
 * Created on 2018/09/21, 20:27
 */

#ifndef RN4020_H
#define	RN4020_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "main.h"

    
#define _RN4020_WAKE_HW     LATC2
#define _RN4020_WAKE_SW     LATC3

#define _PRIVATE_SERVICE    "3A41CCA5A1F946909D5E11A946BAFCB4"
#define _SWITCH_SERVO_UUID  "E3C8A26203AC447F9FDBF8FED75EE00F"
#define _SERVO_PARAM_UUID   "EB57140A35404A6D8C9740D75DF4CBEF"
#define _STATUS_UUID        "A57CB7123FD340759F92528225EE04BE"

    
void RN4020_Init_Peripheral(void);
void RN4020_Init_PrivateService(void);


void RN4020_Transmit8ByUUID (const char* uuid,uint8_t  data);
void RN4020_Transmit16ByUUID(const char* uuid,uint16_t data);
void RN4020_Transmit32ByUUID(const char* uuid,uint32_t data);

uint8_t  RN4020_Receive8ByUUID (const char* uuid);
uint16_t RN4020_Receive16ByUUID(const char* uuid);
uint32_t RN4020_Receive32ByUUID(const char* uuid);


void RN4020_Transmit8ByHandle (const char* handle,uint8_t  data);
void RN4020_Transmit16ByHandle(const char* handle,uint16_t data);
void RN4020_Transmit32ByHandle(const char* handle,uint32_t data);

uint8_t  RN4020_Receive8ByHandle (const char* handle);
uint16_t RN4020_Receive16ByHandle(const char* handle);
uint32_t RN4020_Receive32ByHandle(const char* handle);

#ifdef	__cplusplus
}
#endif

#endif	/* RN4020_H */

