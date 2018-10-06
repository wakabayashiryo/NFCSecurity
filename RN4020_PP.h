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

#define _PRIVATE_SERVICE            "3A41CCA5A1F946909D5E11A946BAFCB4"
#define _PRIVATE_CHARACTERISTIC1    "1713453B292E4B1C9515F23DDAC2B2B0"
#define _PRIVATE_CHARACTERISTIC2    "EB57140A35404A6D8C9740D75DF4CBEF"
    
void RN4020_Init_PP(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RN4020_H */

