#include <xc.h>
#include "user.h"
#include "function.h"
#include <stdio.h>

extern controller_t controller;
extern double moterMain[4];

void setTimer(void)
{

    // (1/16000000*256分周期*3125 = 0.05...(s))
    T4CON = 0x0000;
    T4CONbits.TCKPS = 0b11;
    PR4 = 3125;
    _T4IP = 2;
    _T4IF = 0;
    _T4IE = 1;
    T4CONbits.TON = 1;

    return;
}

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
    drive(moterMain, &controller);
    _T4IF = 0;
}
