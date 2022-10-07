#include <xc.h>
#include "user.h"
#include "function.h"

extern controller_t controller;

void setUART(void)
{
    setU1(38400);
    setU3(38400);
    setU4(38400);

    return;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    // U1TXREG = U1RXREG;
    _U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void)
{
    // U3TXREG = U3RXREG;
    _U3RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt(void)
{
    // U4TXREG = U4RXREG;
    _U4RXIF = 0;
}

void setU1(long BRG)
{
    // U1のピンの設定
    _TRISD0 = 1;  // RX
    _TRISD11 = 0; // TX
    _U1RXR = 11;  // RX
    _RP12R = 3;   // TX

    // U1モジュールの設定
    U1MODE = 0x0000;
    U1STA = 0x0000;
    U1MODEbits.BRGH = 1;           // 高速ボーレートモード
    U1BRG = (FCY / (4 * BRG)) - 1; // ボーレート設定
    _U1RXIE = 1;                   // 割り込みを有効化
    _U1RXIF = 0;                   // 割り込みのフラグを下げる
    _U1RXIP = 7;                   // 割り込み優先度の設定
    U1MODEbits.UARTEN = 1;         // UART有効化
    U1STAbits.UTXEN = 1;           // 送信有効化

    return;
}

void setU2(long BRG)
{
    // U2のピンの設定
    _TRISD9 = 1; // RX
    _TRISD8 = 0; // TX
    _U2RXR = 4;  // RX
    _RP2R = 5;   // TX

    // U2モジュールの設定
    U2MODE = 0x0000;
    U2STA = 0x0000;
    U2MODEbits.BRGH = 1;           // 高速ボーレートモード
    U2BRG = (FCY / (4 * BRG)) - 1; // ボーレート設定
    _U2RXIE = 1;                   // 割り込みを有効化
    _U2RXIF = 0;                   // 割り込みのフラグを下げる
    _U2RXIP = 7;                   // 割り込み優先度の設定
    U2MODEbits.UARTEN = 1;         // UART有効化
    U2STAbits.UTXEN = 1;           // 送信有効化

    return;
}

void setU3(long BRG)
{
    // U3のピンの設定
    _TRISB14 = 1; // RX
    _TRISB15 = 0; // TX
    _U3RXR = 14;  // RX
    _RP29R = 28;  // TX

    // U3モジュールの設定
    U3MODE = 0x0000;
    U3STA = 0x0000;
    U3MODEbits.BRGH = 1;           // 高速ボーレートモード
    U3BRG = (FCY / (4 * BRG)) - 1; // ボーレート設定
    _U3RXIE = 1;                   // 割り込みを有効化
    _U3RXIF = 0;                   // 割り込みのフラグを下げる
    _U3RXIP = 1;                   // 割り込み優先度の設定
    U3MODEbits.UARTEN = 1;         // UART有効化
    U3STAbits.UTXEN = 1;           // 送信有効化

    return;
}

void setU4(long BRG)
{
    // U4のピンの設定
    _TRISF4 = 1; // RX
    _TRISF5 = 0; // TX
    _U4RXR = 10; // RX
    _RP17R = 30; // TX

    // U4モジュールの設定
    U4MODE = 0x0000;
    U4STA = 0x0000;
    U4MODEbits.BRGH = 1;           // 高速ボーレートモード
    U4BRG = (FCY / (4 * BRG)) - 1; // ボーレート設定
    _U4RXIE = 1;                   // 割り込みを有効化
    _U4RXIF = 0;                   // 割り込みのフラグを下げる
    _U4RXIP = 1;                   // 割り込み優先度の設定
    U4MODEbits.UARTEN = 1;         // UART有効化
    U4STAbits.UTXEN = 1;           // 送信有効化

    return;
}

void prints(char *text)
{
    U1TXREG = 0x0a;
    U1TXREG = 0x0d;

    while (*text != '\0')
    {
        while (U1STAbits.TRMT == 0)
            ;
        U1TXREG = *text++;
    }

    return;
}
