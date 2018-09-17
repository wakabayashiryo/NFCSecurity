/* 
 * File:   Pin_def.h
 * Author: evaota
 *
 * Created on 2018/07/15, 21:49
 */

#ifndef PIN_DEF_H
#define	PIN_DEF_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAG_SENSOR  LATA1

#define SRV_SIG     LATA2
#define SRV_PWR     LATA0

#define SRV_ON      (uint8_t)1
#define SRV_OFF     (uint8_t)0

#define LED1        LATC0
#define LED2        LATC1

#define LED_ON      (uint8_t)0
#define LED_OFF     (uint8_t)1
    
#define BLE_WAKE_HW LATC2
#define BLE_WAKE_SW LATC3

#ifdef	__cplusplus
}
#endif

#endif	/* PIN_DEF_H */

