#include "RN4020.h"

/*TODO
 * 
 * 
*/

void RN4020_Send_Command(const char *cmd,const char *data)
{    
    printf(cmd);
    printf(data);
    printf("\n");
    __delay_ms(100);
}

void RN4020_Init_Central(void)
{    
    _RN4020_WAKE_SW = 1;
    _RN4020_WAKE_HW = 1;

    RN4020_Send_Command("SF,","1");         //factory reset,
    RN4020_Send_Command("SB,","4");
    RN4020_Send_Command("SS,","00000001");
    RN4020_Send_Command("PZ,","");
    RN4020_Send_Command("PS,",SERVICE_UUID);
    RN4020_Send_Command("PC,",CHARACTERISTIC_UUID);
    
    RN4020_Send_Command("R,","1");
    
    __delay_ms(1000);
    
    RN4020_Send_Command("A","");
}
