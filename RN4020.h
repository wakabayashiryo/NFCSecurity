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
#define _SERVO_UUID         "EB57140A35404A6D8C9740D75DF4CBEF"
#define _STATUS_UUID        "A57CB7123FD340759F92528225EE04BE"
    
void RN4020_Init(void);

void RN4020_TransmitByUUID(const char* uuid,uint16_t data);
uint16_t RN4020_ReceiveByUUID(const char* uuid);
void RN4020_TransmitByHandle(const char* handle,uint16_t data);
uint16_t RN4020_ReceiveByHandle(const char* handle);
#ifdef	__cplusplus
}
#endif

#endif	/* RN4020_H */

