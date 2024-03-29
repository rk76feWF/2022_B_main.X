#include <xc.h>
#include "user.h"
#include "function.h"

void setPWM(void)
{
    OC1CON1 = 0b0001110000000110;
    OC1CON2 = 0b0000000000011111;
    _RP21R = 18;
    OC1R = 0;
    OC1RS = F_CYCLE;

    OC2CON1 = 0b0001110000000110;
    OC2CON2 = 0b0000000000011111;
    _RP26R = 19;
    OC2R = 0;
    OC2RS = F_CYCLE;

    OC3CON1 = 0b0001110000000110;
    OC3CON2 = 0b0000000000011111;
    _RP25R = 20;
    OC3R = 0;
    OC3RS = F_CYCLE;

    OC4CON1 = 0b0001110000000110;
    OC4CON2 = 0b0000000000011111;
    _RP20R = 21;
    OC4R = 0;
    OC4RS = F_CYCLE;

    OC5CON1 = 0b0001110000000110;
    OC5CON2 = 0b0000000000011111;
    _RP23R = 22;
    OC5R = 0;
    OC5RS = F_CYCLE;

    OC6CON1 = 0b0001110000000110;
    OC6CON2 = 0b0000000000011111;
    _RP22R = 23;
    OC6R = 0;
    OC6RS = F_CYCLE;

    return;
}