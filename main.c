#include <xc.h>
#include "config.h"
#include "user.h"
#include "function.h"
#include <libpic30.h>
#include <stdio.h>

controller_t controller;
double moterMain[4];

int main(void)
{
    setup();

    while (1)
    {
        // 展開
        if (controller.btn_Circle)
        {
            moter(5, 20);
            moter(6, 20);
        }
        
        // 縮小
        if (controller.btn_Cross)
        {
            moter(5, -20);
            moter(6, -20);
        }
        
        // 展開機構停止
        if (controller.btn_Triangle)
        {
            moter(5, 0);
            moter(6, 0);
        }
    }

    return 0;
}

void setup(void)
{
    OSCCON = 0x0000;
    _COSC = 0b001;
    _NOSC = 0b001;
    CLKDIV = 0x0000;
    
    setIO();
    setUART();
    setPWM();
    setTimer();

    return;
}

void setIO(void)
{
    // Analog or Digital
    ANSB = 0x0000;
    ANSC = 0x0000;
    ANSD = 0x0000;
    ANSE = 0x0000;
    ANSF = 0x0000;
    ANSG = 0x0000;

    TRISB = 0xffff;
    TRISC = 0xffff;
    TRISD = 0xffff;
    TRISE = 0xffff;
    TRISF = 0xffff;
    TRISG = 0xffff;

    // LED
    _TRISB13 = 0;
    _TRISB12 = 0;

    // LAN
    _TRISE4 = 0;
    _TRISE5 = 0;
    _TRISE6 = 0;
    _TRISE7 = 0;
    _TRISE0 = 0;
    _TRISE1 = 0;
    _TRISE2 = 0;
    _TRISE3 = 0;
    _TRISD6 = 0;
    _TRISD7 = 0;
    _TRISF0 = 0;
    _TRISF1 = 0;
    
    return;
}