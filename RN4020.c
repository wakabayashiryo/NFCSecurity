#include "RN4020.h"

#define SERVICE_UUID        "3A41CCA5A1F946909D5E11A946BAFCB4"
#define CHARACTERISTIC_UUID "A90FE7491FA44ACAB87ADFD81ACE6EC8"


static void RN4020_Send_Command(const char *cmd,const char *data)
{
    printf(cmd);
    printf(data);
    printf("\n");
}

void RN4020_Init(void)
{    
    _RN4020_WAKE_SW = 1;
    _RN4020_WAKE_HW = 1;

    RN4020_Send_Command("SF,","1");
    RN4020_Send_Command("SB,","4");
    RN4020_Send_Command("SS,","00000001");
    RN4020_Send_Command("PZ,","");
    RN4020_Send_Command("PS,",SERVICE_UUID);
    RN4020_Send_Command("PC,",CHARACTERISTIC_UUID);
    
    RN4020_Send_Command("R,","1");
    
    __delay_ms(1000);
    
    RN4020_Send_Command("A","");
}
