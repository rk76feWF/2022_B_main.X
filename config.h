/*
 * File:   config.h
 * Author: rk76fewf
 *
 * Created on August 30, 2022, 8:02 PM
 */

#ifndef CONFIG_H
#define CONFIG_H

// PIC24FJ64GC006 Configuration Bit Settings

// 'C' source line config statements

// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
#pragma config DSWDTOSC = LPRC     // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = ON        // Deep Sleep BOR Enable bit (DSBOR Enabled)
#pragma config DSWDTEN = OFF       // Deep Sleep Watchdog Timer Enable (DSWDT Disabled)
#pragma config DSSWEN = OFF        // DSEN Bit Enable (Deep Sleep operation is always disabled)
#pragma config RTCBAT = OFF        // RTC Battery Operation Enable (RTC operation is discontinued in VBAT)
#pragma config PLLDIV = DIV2       // PLL Input Prescaler Select bits (Oscillator divided by 2 (8 MHz input))
#pragma config I2C2SEL = PRI       // Alternate I2C2 Location Select bit (I2C2 is multiplexed to SDA2/RA3 and SCL2/RA2 )
#pragma config IOL1WAY = OFF       // PPS IOLOCK Set Only Once Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)

// CONFIG3
#pragma config WPFP = WPFP127   // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config SOSCSEL = OFF    // SOSC Selection bits (Digital (SCLKI) mode)
#pragma config WDTWIN = PS25_0  // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset Enable)
#pragma config WPDIS = WPDIS    // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMD = NONE       // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config WDTCLK = LPRC       // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = ON       // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as port I/O (RC15))
#pragma config FCKSM = CSDCMD      // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL      // Initial Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config ALTADREF = AVREF_RA // External 12-Bit A/D Reference Location Select bit (AVREF+/AVREF- are mapped to RA9/RA10)
#pragma config ALTCVREF = CVREF_RA // External Comparator Reference Location Select bit (CVREF+/CVREF- are mapped to RA9/RA10)
#pragma config WDTCMX = WDTCLK     // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config IESO = OFF          // Internal External Switchover (Disabled)

// CONFIG1
#pragma config WDTPS = PS32768  // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128    // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF     // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = WDT_DIS // Watchdog Timer Enable (WDT enabled in hardware)
#pragma config ICS = PGx1       // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config LPCFG = OFF      // Low power regulator control (Disabled - regardless of RETEN)
#pragma config GWRP = OFF       // General Segment Write Protect (Disabled)
#pragma config GCP = OFF        // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF     // JTAG Port Enable (Disabled)

#endif /* CONFIG_H */
