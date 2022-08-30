#include <xc.h>
#include "user.h"
#include "function.h"

void setUART(void)
{
    // U1のピンの設定
    _TRISD0 = 1;  // RX
    _TRISD11 = 0; // TX
    _U1RXR = 11;  // RX
    _RP12R = 3;   // TX

    // U1モジュールの設定
    U1MODE = 0x0000;
    U1STA = 0x0000;
    U1MODEbits.BRGH = 1;   // 高速ボーレートモード
    U1BRG = 103;           // ボーレート設定
    _U1RXIE = 1;           // 割り込みを有効化
    _U1RXIF = 0;           // 割り込みのフラグを下げる
    _U1RXIP = 1;           // 割り込み優先度の設定
    U1MODEbits.UARTEN = 1; // UART有効化
    U1STAbits.UTXEN = 1;   // 送信有効化

    return;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    U1TXREG = U1RXREG;
    _U1RXIF = 0;

    return;
}
