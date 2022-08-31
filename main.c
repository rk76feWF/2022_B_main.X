#include <xc.h>
#include "config.h"
#include "user.h"
#include "function.h"
#include <libpic30.h>

int main(void)
{
    setup();

    while (1)
    {
        OC1R = F_CYCLE * 60.0 / 100.0;
        OC2R = F_CYCLE * 30.0 / 100.0;
        OC3R = F_CYCLE * 30.0 / 100.0;
        OC4R = F_CYCLE * 60.0 / 100.0;
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
