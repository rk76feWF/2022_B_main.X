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
    PR2 = 330;
    _T2IP = 3;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;

    T4CON = 0x0000;
    T4CONbits.TCKPS = 0b11;
    PR4 = 3125;
    _T4IP = 2;
    _T4IF = 0;
    _T4IE = 1;
    T4CONbits.TON = 1;

    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    static int cnt = 0;
    if (readController(&controller))
        cnt++;
    else
    {
        LED2 = LED3 = 0;
        cnt = 0;
    }

    if (cnt >= 10)
    {
        controller.Lx_scalar = 0;
        controller.Ly_scalar = 0;
        controller.Rx_scalar = 0;
        controller.Ry_scalar = 0;
        convertXY(controller.Lx_scalar, controller.Ly_scalar, &controller.L_angle, &controller.L_scalar);

        controller.btn_UP = 0;
        controller.btn_DOWN = 0;
        controller.btn_RIGHT = 0;
        controller.btn_LEFT = 0;

        controller.btn_Triangle = 0;
        controller.btn_Cross = 0;
        controller.btn_Circle = 0;
        controller.btn_Square = 0;

        controller.btn_L1 = 0;
        controller.btn_L2 = 0;
        controller.btn_R1 = 0;
        controller.btn_R2 = 0;

        moter(1, 0);
        moter(2, 0);
        moter(3, 0);
        moter(4, 0);
        moter(5, 0);
        moter(6, 0);

        LED2 = LED3 = 1;
        cnt--;
    }
    _T2IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
    drive(moterMain, &controller);
    _T4IF = 0;
}