#include <xc.h>
#include "user.h"
#include "function.h"

extern controller_t controller;

void setLED(void)
{
    OC7CON1 = 0b0001110000000110;
    OC7CON2 = 0b0000000000011111;
    _RP6R = 24;
    OC7R = 0;
    OC7RS = F_CYCLE;

    // (1/16000000*256分周期*10000= 0.16...(s))
    T3CON = 0x0000;
    T3CONbits.TCKPS = 0b11;
    PR3 = 10000;
    _T3IP = 2;
    _T3IF = 0;
    _T3IE = 1;
    T3CONbits.TON = 1;

    return;
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    // 0.48秒周期
    if (controller.status)
    {
        if (OC7R)
            OC7R = 0;
        else
            OC7R = 100;
    }
    else
        OC7R = 100;

    _T3IF = 0;
}
