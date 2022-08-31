#include <xc.h>
#include "user.h"
#include "function.h"
#include <math.h>

void drive(double *moterMain, controller_t *controller)
{
    omni4vector(moterMain, controller->L_angle, controller->L_scalar);
    // モーター操作

    moter(1, moterMain[0]);
    moter(2, moterMain[1]);
    moter(3, moterMain[2]);
    moter(4, moterMain[3]);

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
    int S1 = 0;
    int S2 = 0;
    if (power > 0)
    {
        S1 = 1;
        S2 = 0;
    }
    else if (power == 0)
    {
        S1 = 0;
        S2 = 0;
    }
    else
    {
        S1 = 0;
        S2 = 1;
    }

    switch (number)
    {
    case 1:
        M1S1 = S1;
        M1S2 = S2;
        OC1R = (int)(fabs(power) / 100 * F_CYCLE);
        break;
    case 2:
        M2S1 = S1;
        M2S2 = S2;
        OC2R = (int)(fabs(power) / 100 * F_CYCLE);
        break;
    case 3:
        M3S1 = S1;
        M3S2 = S2;
        OC3R = (int)(fabs(power) / 100 * F_CYCLE);
        break;
    case 4:
        M4S1 = S1;
        M4S2 = S2;
        OC4R = (int)(fabs(power) / 100 * F_CYCLE);
        break;
    }
    return;
}