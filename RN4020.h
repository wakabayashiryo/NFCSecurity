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

#define SERVICE_UUID        "3A41CCA5A1F946909D5E11A946BAFCB4"
#define CHARACTERISTIC_UUID "3A41CCA5A1F946909D5E11A946BAFCB4,1A,08"

void RN4020_Send_Command(const char *cmd,const char *data);
void RN4020_Init_Central(void);


#ifdef	__cplusplus
}
#endif

#endif	/* RN4020_H */

