#include "RN4020.h"

const uint8_t * const Setting_command[] = 
{
    "S,",
    "SB,",
    "SDF,",
    "SDH,",
    "SDM,",
    "SDN,",
    "SDR,",
    "SDS,",
    "SF,",
    "SM,",
    "SN,",
    "SR,",
    "SS,",
    "ST",
};

extern const uint8_t * const Action_command[] = 
{
    "A,",
    "B,",
    "D",
    "E,",
    "F,",
    "H",
    "J,",
    "K",
    "M",
    "N,",
    "O",
    "R,1",
    "T,",
    "U",
    "V",
    "X",
    "Y",
    "Z",
};

const uint8_t * const Service_command[] = 
{
    "LC",
    "LS,",
    "CHR,",
    "CHW,",
    "CURC,",
    "CURV,",
    "CUWC,",
    "CUWV,",
    "SHR,",
    "SHW,",
    "SUR,",
    "SUW,",
    "PC,",
    "PS,",
    "PZ",
};

const uint8_t * const MLDP_command[] = 
{
    "SE,",
    "I",
};
