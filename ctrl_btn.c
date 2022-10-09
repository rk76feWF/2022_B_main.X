#include <xc.h>
#include "user.h"
#include "function.h"

extern controller_t controller;

void setModule(void)
{
    // (1/16000000*256分周期*10000= 0.1(s))
    T3CON = 0x0000;
    T3CONbits.TCKPS = 0b11;
    PR3 = 6250;
    _T3IP = 1;
    _T3IF = 0;
    _T3IE = 1;
    T3CONbits.TON = 1;

    return;
}
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    if (controller.type == 0) // PS3
        ctrl_btn_ps3(&controller);
    else if (controller.type == 1) // Original
        ctrl_btn_original(&controller);
    _T3IF = 0;
}

// -----------------------------------------------

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

static inline void NAKAMITCH(void)
{
    U3TXREG = 0x80;
    while (U3STAbits.TRMT == 0)
        ;
    U3TXREG = controller.btn.chr[2];
    while (U3STAbits.TRMT == 0)
        ;
    U3TXREG = controller.btn.chr[1];
    while (U3STAbits.TRMT == 0)
        ;
    U3TXREG = controller.btn.chr[0];

    U3TXREG = (0x80 + controller.btn.chr[2] + controller.btn.chr[1] + controller.btn.chr[0]) & 0x0000007F;
}

// -----------------------------------------------

void ctrl_btn_ps3(controller_t *ctrl)
{
    // 展開
    if (ctrl->btn.R_Circle)
        deploy();

    // 縮小
    if (ctrl->btn.R_Cross)
        folding();

    // 展開機構停止
    if (ctrl->btn.R_Triangle)
        stop();

    // btnをU3で送信
    NAKAMITCH();

    if (ctrl->btn.R1)
        U4TXREG = 0x99;
    if (ctrl->btn.R2)
        U4TXREG = 0x88;

    return;
}

void ctrl_btn_original(controller_t *ctrl)
{
    // 展開
    if (ctrl->btn.R_Circle)
        deploy();

    // 縮小
    if (ctrl->btn.R_Cross)
        folding();

    // 展開機構停止
    if (ctrl->btn.R_Triangle)
        stop();
    // 展開

    // btnをU3で送信
    NAKAMITCH();

    if (ctrl->btn.R1)
        U4TXREG = 0x99;
    if (ctrl->btn.R2)
        U4TXREG = 0x88;

    return;
}
