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

void RN4020_Init(void);


#ifdef	__cplusplus
}
#endif

#endif	/* RN4020_H */

