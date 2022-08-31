#include <xc.h>
#include "config.h"
#include "user.h"
#include "function.h"
#include <libpic30.h>
#include <stdio.h>

controller_t controller;

int main(void)
{
    setup();

    char buf[64];
    while (1)
    {
        readController(&controller);
        sprintf(buf, "%d %d", controller.Lx_scalar, controller.Ly_scalar);
        prints(buf);
    }

    return 0;
}

void setup(void)
{
    OSCCON = 0x0000;
    _COSC = 0b001;
    _NOSC = 0b001;
    CLKDIV = 0x0000;

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

    _TRISB13 = 0;
    _TRISB12 = 0;

    setUART();
    setPWM();

    return;
}
