#include <xc.h>
#include "user.h"
#include "function.h"
#include <math.h>

extern controller_t controller;
double moterMain[4] = {0, 0, 0, 0};
double cMoterMain[4] = {0, 0, 0, 0};

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
    drive(moterMain, &controller);
    _T4IF = 0;
}

void drive(double *moterMain, controller_t *controller)
{
    omni4vector(moterMain, controller->L_angle, controller->L_scalar);

    // 回転
    for (int i = 0; i < 4; i++)
        moterMain[i] -= (int)(controller->Rx_scalar * 100 / 64) / 2;

    for (int i = 0; i < 4; i++)
    {
        cMoterMain[i] += ((double)(moterMain[i] - cMoterMain[i]) * 0.5);
        if (moterMain[i] == 0 && fabs(cMoterMain[i]) <= 0.01) // double型の比較なので、誤差を考慮
            cMoterMain[i] = 0;
    }
    // モーター操作
    for (int i = 0; i < 4; i++)
        moter(i + 1, -cMoterMain[i]);

    return;
}

void omni4vector(double *moterMain, double angle, double power)
{
    moterMain[0] = cos((45 + angle) * (M_PI / 180)) * power;
    moterMain[1] = cos((135 + angle) * (M_PI / 180)) * power;
    moterMain[2] = -moterMain[0];
    moterMain[3] = -moterMain[1];

    return;
}

void moter(int number, double power)
{
    int S1 = 0, S2 = 0;
    if (power > 0)
        S1 = 1, S2 = 0;
    else if (power == 0)
        S1 = 0, S2 = 0;
    else
        S1 = 0, S2 = 1;

    switch (number)
    {
    case 1:
        M1S1 = S1, M1S2 = S2;
        OC1R = (int)(fabs(power) * F_CYCLE / 100.0);
        break;
    case 2:
        M2S1 = S1, M2S2 = S2;
        OC2R = (int)(fabs(power) * F_CYCLE / 100.0);
        break;
    case 3:
        M3S1 = S1, M3S2 = S2;
        OC3R = (int)(fabs(power) * F_CYCLE / 100.0);
        break;
    case 4:
        M4S1 = S1, M4S2 = S2;
        OC4R = (int)(fabs(power) * F_CYCLE / 100.0);
        break;
    case 5:
        M5S1 = S1, M5S2 = S2;
        OC5R = (int)(fabs(power) * F_CYCLE / 100.0);
        break;
    case 6:
        M6S1 = S1, M6S2 = S2;
        OC6R = (int)(fabs(power) * F_CYCLE / 100.0);
        break;
    }
    return;
}

void setMoter(void)
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
