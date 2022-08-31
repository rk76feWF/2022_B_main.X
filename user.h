/*
 * File:   user.h
 * Author: rk76fewf
 *
 * Created on August 30, 2022, 8:51 PM
 */

#ifndef USER_H
#define USER_H

#define FCY 16000000UL

#define LED2 _LATB13
#define LED3 _LATB12

typedef unsigned char data_t;

#define QUEUE_SIZE (64)
typedef struct
{
    int head;
    int num;
    data_t data[QUEUE_SIZE];
} queue_t;

#define F_CYCLE (320 - 1)

#endif /* USER_H */
