/*
 * File:   function.h
 * Author: rk76fewf
 *
 * Created on August 30, 2022, 8:53 PM
 */

#ifndef FUNCTION_H
#define FUNCTION_H

void setup(void);
void setUART(void);

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void);

int enqueue(queue_t *que, data_t enq_data);
int dequeue(queue_t *que, data_t *deq_data);

void setPWM(void);

#endif /* FUNCTION_H */
