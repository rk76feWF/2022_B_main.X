#include <xc.h>
#include "user.h"
#include "function.h"
#include <math.h>

controller_t controller;

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    // 0.0016秒周期
    static int cnt = 0;
    if (controller.type == 0) // PS3
    {
        if (readPS3Controller(&controller))
            cnt++;
        else
            cnt = 0;
    }
    else if (controller.type == 1) // Original
    {
        if (readOriginalController(&controller))
            cnt++;
        else
            cnt = 0;
    }

    if (cnt >= 30)
    {
        // コントローラーとの接続が切れたとき

        controller.status = 0;
        for (int i = 1; i <= 6; i++)
            moter(i, 0);

        cnt--;
    }

    // status LED
    if (controller.status)
        LED2 = LED3 = 0;
    else
        LED2 = LED3 = 1;

    _T2IF = 0;
}

void setCtrl(void)
{
    if (controller.type == 0) // PS3
        setU2(38400);
    else if (controller.type == 1) // Original
        setU2(38400);

    T2CON = 0x0000;
    T2CONbits.TCKPS = 0b11;
    // (1/16000000*256分周期*100= 0.0016...(s))
    PR2 = 100;
    _T2IP = 3;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;

    controller.status = 0; // Statusを初期化

    return;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    enqueue(&controller.FIFO, U2RXREG);
    _U2RXIF = 0;
}

void convertXY(int x, int y, double *angle, double *power)
{
    *power = sqrt(x * x + y * y);
    if (*power > 64)
    {
        *power = 64;
    }

    *power = *power / 64 * 100;
    if (x == 0 && y == 0)
    {
        *angle = 0;
        return;
    }
    *angle = atan2(y, x);
    *angle = -((*angle) * 180 / M_PI) + 90;

    return;
}
