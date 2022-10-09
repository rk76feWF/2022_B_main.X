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

union btn
{
    struct
    {
        bool FUNC1 : 1;
        bool FUNC2 : 1;
        bool FUNC3 : 1;
        bool FUNC4 : 1;
        bool FUNC5 : 1;
        bool FUNC6 : 1;
        bool b01 : 1;
        bool LOCK : 1;

        bool R_Triangle : 1;
        bool R_Square : 1;
        bool R_Cross : 1;
        bool R_Circle : 1;
        bool R1 : 1;
        bool R2 : 1;
        bool b09 : 1;
        bool b08 : 1;

        bool L_UP : 1;
        bool L_LEFT : 1;
        bool L_DOWN : 1;
        bool L_RIGHT : 1;
        bool L1 : 1;
        bool L2 : 1;
        bool b17 : 1;
        bool b16 : 1;
    };
    unsigned char chr[3];
};

typedef struct
{
    // FIFO
    queue_t FIFO;

    // READ
    int ReadCount;
    data_t Read_data[7];

    // DATA
    int type;
    bool status;
    double L_angle;
    double L_scalar;
    int Lx_scalar;
    int Ly_scalar;

    double R_angle;
    double R_scalar;
    int Rx_scalar;
    int Ry_scalar;

    union btn btn;

} controller_t;

#endif /* CONTROLLER_H */
