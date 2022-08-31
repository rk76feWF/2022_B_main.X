#include <xc.h>
#include "user.h"
#include "function.h"
#include <stdio.h>

extern controller_t controller;
extern double moterMain[4];

void setTimer(void)
{
    T2CON = 0x0000;
    T2CONbits.TCKPS = 0b11;
    // (1/16000000*256分周期*3125 = 0.05...(s))
    // (1/16000000*256分周期*125 = 0.002...(s))
    PR2 = 50;
    _T2IP = 0x03;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;

    T4CON = 0x0000;
    T4CONbits.TCKPS = 0b11;
    PR4 = 10000;
    _T4IP = 0x02;
    _T4IF = 0;
    _T4IE = 1;
    T4CONbits.TON = 1;

    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    if (readController(&controller))
    _T2IF = 0;

    return;
}

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
    drive(moterMain, &controller);
    LED2 = LED3 = ~LED2;
    _T4IF = 0;

    return;
}