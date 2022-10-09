#include <xc.h>
#include "config.h"
#include "user.h"
#include "function.h"

extern controller_t controller;

int main(void)
{

    controller.type = 1; // PS3
    setup();

    while (1)
    {
        if (controller.type == 0) // PS3
            ctrl_btn_ps3(&controller);
        else if (controller.type == 1) // Original
            ctrl_btn_original(&controller);
    }

    return 0;
}
