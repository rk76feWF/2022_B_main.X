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
#include "moterMain.h"

void setup(void);
void setIO(void);
void setUART(void);
void prints(char *text);

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void);

int enqueue(queue_t *que, data_t enq_data);
int dequeue(queue_t *que, data_t *deq_data);

int readController(controller_t *controller_data);
void convertXY(int x, int y, double *angle, double *power);

void setTimer(void);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void);

void drive(double *moterMain, controller_t *controller);
void omni4vector(double *moterMain, double angle, double power);
void moter(int number, double power);
void setPWM(void);

void tenkai(controller_t *ctrl);
void setCN(void);
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);

#endif /* FUNCTION_H */
