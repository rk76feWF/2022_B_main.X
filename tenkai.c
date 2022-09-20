#include <xc.h>
#include "user.h"
#include "function.h"
#include "moterMain.h"

// リミットスイッチは押されていない時がLOW
// NH5が左のリミットスイッチ, NH6に右のリミットスイッチをつける
// moter5は左, moter6は右

#define L_TOP _RF7
#define L_BTM _RC12
#define R_TOP _RC15
#define R_BTM _RD10

void tenkai(controller_t *ctrl)
{
    // 展開
    if (ctrl->btn_Circle)
    {
        if (L_BTM == 0)
            moter(5, 20);
        if (R_BTM == 0)
            moter(6, 20);
    }

    // 縮小
    if (ctrl->btn_Cross)
    {
        if (L_TOP == 0)
            moter(5, -20);
        if (R_TOP == 0)
            moter(6, -20);
    }

    // 展開機構停止
    if (ctrl->btn_Triangle)
    {
        moter(5, 0);
        moter(6, 0);
    }

    if (ctrl->btn_L2)
    {
        U3TXREG = 0x88;
    }
    if (ctrl->btn_R2)
    {
        U4TXREG = 0x88;
    }

    return;
}

void setCN(void)
{
    _CNIE = 1; // 割り込みを有効化
    _CNIF = 0; // 割り込みのフラグを下げる
    _CNIP = 1; // 割り込み優先度の設定

    _CN83IE = 1; // 左上のリミットスイッチの割り込みを有効化
    _CN23IE = 1; // 左下のリミットスイッチの割り込みを有効化
    _CN22IE = 1; // 右上のリミットスイッチの割り込みを有効化
    _CN55IE = 1; // 右下のリミットスイッチの割り込みを有効化

    return;
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
{
    if (M5S1 || M6S1) // 展開している
    {
        if (L_BTM == 1)  // 左が展開し切った
            moter(5, 0); // 左のモータを停止
        if (R_BTM == 1)  // 右が展開し切った
            moter(6, 0); // 右のモータを停止
    }
    if (M5S2 || M6S2) // 縮小
    {
        if (L_TOP == 1)  // 左が縮小し切った
            moter(5, 0); // 左のモータを停止
        if (R_TOP == 1)  // 右が縮小し切った
            moter(6, 0); // 右のモータを停止
    }
    _CNIF = 0;
}