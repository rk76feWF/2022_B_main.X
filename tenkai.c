#include <xc.h>
#include "user.h"
#include "function.h"

// リミットスイッチは押されていない時がHIGHT
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
        if (L_TOP || R_TOP)
        {
            moter(5, 20);
            moter(6, 20);
        }
    }

    // 縮小
    if (ctrl->btn_Cross)
    {
        if (L_BTM || R_BTM)
        {
            moter(5, -20);
            moter(6, -20);
        }
    }

    // 展開機構停止
    if (ctrl->btn_Triangle)
    {
        moter(5, 0);
        moter(6, 0);
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
    if (L_TOP == 0 || L_BTM == 0) // 左上 or 左下のリミットスイッチが押されたら
        moter(5, 0);              // 左のモータを停止

    if (R_TOP == 0 || R_BTM == 0) // 右上 or 右下のリミットスイッチが押されたら
        moter(6, 0);              // 右のモータを停止

    _CNIF = 0;
}