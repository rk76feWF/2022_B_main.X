#include <xc.h>
#include "user.h"
#include "function.h"

static inline void deploy(void)
{
    if (L_BTM == 0)
        moter(5, 20);
    if (R_BTM == 0)
        moter(6, 20);
}
static inline void folding(void)
{
    if (L_TOP == 0)
        moter(5, -20);
    if (R_TOP == 0)
        moter(6, -20);
}
static inline void stop(void)
{
    moter(5, 0);
    moter(6, 0);
}

// -----------------------------------------------

void ctrl_btn_ps3(controller_t *ctrl)
{
    // 展開
    if (ctrl->btn_Circle)
        deploy();

    // 縮小
    if (ctrl->btn_Cross)
        folding();

    // 展開機構停止
    if (ctrl->btn_Triangle)
        stop();

    if (ctrl->btn_L1)
        U3TXREG = 0x99;
    if (ctrl->btn_L2)
        U3TXREG = 0x88;

    if (ctrl->btn_R1)
        U4TXREG = 0x99;
    if (ctrl->btn_R2)
        U4TXREG = 0x88;

    return;
}

void ctrl_btn_original(controller_t *ctrl)
{
    // 展開
    if (ctrl->btn_Circle)
        deploy();

    // 縮小
    if (ctrl->btn_Cross)
        folding();

    // 展開機構停止
    if (ctrl->btn_Triangle)
        stop();

    if (ctrl->btn_L1)
        U3TXREG = 0x99;
    if (ctrl->btn_L2)
        U3TXREG = 0x88;

    if (ctrl->btn_R1)
        U4TXREG = 0x99;
    if (ctrl->btn_R2)
        U4TXREG = 0x88;

    return;
}
