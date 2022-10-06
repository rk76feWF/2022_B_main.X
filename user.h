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

// UART
typedef unsigned char data_t;
#define QUEUE_SIZE (64)
typedef struct
{
    int head;
    int num;
    data_t data[QUEUE_SIZE];
} queue_t;

// Moter
#define F_CYCLE (320 - 1)
#define M1S1 (_LATE4)
#define M1S2 (_LATE5)
#define M2S1 (_LATE6)
#define M2S2 (_LATE7)
#define M3S1 (_LATE0)
#define M3S2 (_LATE1)
#define M4S1 (_LATE2)
#define M4S2 (_LATE3)
#define M5S1 (_LATD6)
#define M5S2 (_LATD7)
#define M6S1 (_LATF0)
#define M6S2 (_LATF1)

#endif /* USER_H */
