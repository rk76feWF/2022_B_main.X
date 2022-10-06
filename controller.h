/*
 * File:   controller.h
 * Author: rk76fewf
 *
 * Created on August 31, 2022, 1:23 PM
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "user.h"
#include <stdbool.h>

typedef struct
{
    // FIFO
    queue_t FIFO;

    // READ
    int ReadCount;
    data_t Read_data[7];

    // DATA
    double L_angle;
    double L_scalar;
    int Lx_scalar;
    int Ly_scalar;

    double R_angle;
    double R_scalar;
    int Rx_scalar;
    int Ry_scalar;

    bool btn_UP;
    bool btn_DOWN;
    bool btn_RIGHT;
    bool btn_LEFT;

    bool btn_Triangle;
    bool btn_Cross;
    bool btn_Circle;
    bool btn_Square;

    bool btn_L1;
    bool btn_L2;
    bool btn_R1;
    bool btn_R2;

} controller_t;

#endif /* CONTROLLER_H */
