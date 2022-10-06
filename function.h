/*
 * File:   function.h
 * Author: rk76fewf
 *
 * Created on August 30, 2022, 8:53 PM
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#include "user.h"
#include "controller.h"

void setup(void);
void setIO(void);

// UART
void setUART(void);
void setU1(long BRG);
void setU2(long BRG);
void setU3(long BRG);
void setU4(long BRG);
void prints(char *text);
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void);
void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt(void);

// Queue
int enqueue(queue_t *que, data_t enq_data);
int dequeue(queue_t *que, data_t *deq_data);

// Controller
void setCtrl(void);
int readController(controller_t *controller_data);
void convertXY(int x, int y, double *angle, double *power);
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

// Moter
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void);
void drive(double *moterMain, controller_t *controller);
void omni4vector(double *moterMain, double angle, double power);
void moter(int number, double power);
void setMoter(void);

// 展開
void tenkai(controller_t *ctrl);
void setCN(void);
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);

#endif /* FUNCTION_H */
