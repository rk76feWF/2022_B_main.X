#include <xc.h>
#include "config.h"
#include "user.h"
#include "function.h"

extern controller_t controller;

int main(void)
{

    setup();

    while (1)
    {
        tenkai(&controller);
    }

    return 0;
}
