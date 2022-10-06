#include <xc.h>
#include "user.h"
#include "function.h"
#include <math.h>

controller_t controller;

void setCtrl(void)
{
    setU2(38400);

    T2CON = 0x0000;
    T2CONbits.TCKPS = 0b11;
    // (1/16000000*256分周期*330 = 0.00528...(s))
    PR2 = 330;
    _T2IP = 3;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;

    return;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    enqueue(&controller.FIFO, U2RXREG);
    _U2RXIF = 0;
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

int readController(controller_t *controller_data)
{
    data_t d;

    // dequeue
    if (dequeue(&controller_data->FIFO, &d))
        return -1;

    if (d == 0x80)
    {
        controller_data->ReadCount = 0;
        return 0;
    }

    if (controller_data->ReadCount < 7)
    {
        controller_data->Read_data[controller_data->ReadCount] = d;
        controller_data->ReadCount++;

        if (controller_data->ReadCount == 7)
        {
            int checksum = controller_data->Read_data[0] + controller_data->Read_data[1] + controller_data->Read_data[2] + controller_data->Read_data[3] + controller_data->Read_data[4] + controller_data->Read_data[5];
            if (controller_data->Read_data[6] == ((0x80 + checksum) & 0x0000007F))
            {
                // 内部の処理
                controller_data->Lx_scalar = -64 + controller_data->Read_data[2];
                controller_data->Ly_scalar = 64 - controller_data->Read_data[3];
                controller_data->Rx_scalar = -64 + controller_data->Read_data[4];
                controller_data->Ry_scalar = 64 - controller_data->Read_data[5];
                convertXY(controller_data->Lx_scalar, controller_data->Ly_scalar, &controller_data->L_angle, &controller_data->L_scalar);

                controller_data->btn_UP = controller_data->Read_data[1] == 0x01;
                controller_data->btn_DOWN = controller_data->Read_data[1] == 0x02;
                controller_data->btn_RIGHT = controller_data->Read_data[1] == 0x04;
                controller_data->btn_LEFT = controller_data->Read_data[1] == 0x08;

                controller_data->btn_Triangle = controller_data->Read_data[1] == 0x10;
                controller_data->btn_Cross = controller_data->Read_data[1] == 0x20;
                controller_data->btn_Circle = controller_data->Read_data[1] == 0x40;
                controller_data->btn_Square = controller_data->Read_data[0] == 0x01;

                controller_data->btn_L1 = controller_data->Read_data[0] == 0x02;
                controller_data->btn_L2 = controller_data->Read_data[0] == 0x04;
                controller_data->btn_R1 = controller_data->Read_data[0] == 0x08;
                controller_data->btn_R2 = controller_data->Read_data[0] == 0x10;
            }
            else
                return -1;
        }
    }

    return 0;
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
