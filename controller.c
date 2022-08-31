#include <xc.h>
#include "user.h"
#include "function.h"
#include <math.h>

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
