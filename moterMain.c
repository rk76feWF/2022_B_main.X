#include <xc.h>
#include "user.h"
#include "function.h"
#include <math.h>

extern double cMoterMain[4];

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
