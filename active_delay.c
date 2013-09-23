#include "active_delay.h"

// Config settings
// POSCMOD = HS, FNOSC = PRIPLL, FWDTEN = OFF
// PLLIDIV = DIV_2, PLLMUL = MUL_16
// PBDIV = 8 (default)
// Main clock = 8MHz /2 * 16    = 80MHz
// Peripheral clock = 80MHz /8  =  10MHz

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 10 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void type_b_timer_config(volatile unsigned int *TIMER, volatile unsigned int *TIMER_CONFIGURATION) {
    _TMR_TYPE_B = TIMER;
    _TMR_TYPE_B_CLR = __SFR_PORTCLR(TIMER);
    _TMR_TYPE_B_CON_CLR = __SFR_PORTCLR(TIMER_CONFIGURATION);
    _TMR_TYPE_B_CON_SET = __SFR_PORTSET(TIMER_CONFIGURATION);
}

void type_b_active_delay_ms(int ms) {
    const unsigned short int THRESOLD = 62;

    *_TMR_TYPE_B_CON_CLR = 0x8002; //Clear ON control bit to disable the timer AND clear TSC control bit to select internal PBCLK source (primary osc)
    *_TMR_TYPE_B_CON_SET = 0x0070; //prescale 1:256 PB
    *_TMR_TYPE_B_CLR = 0xFFFF; //clear timer
    *_TMR_TYPE_B_CON_SET = 0x8000; //start the timer

    while (*_TMR_TYPE_B < ms * THRESOLD); //active wait
}

void type_b_active_delay_us(int us) {
    const unsigned short int THRESOLD = 2;

    *_TMR_TYPE_B_CON_CLR = 0x8002; //Clear ON control bit to disable the timer AND clear TSC control bit to select internal PBCLK source (primary osc)
    *_TMR_TYPE_B_CON_SET = 0x0040; //prescale 1:8 PB
    *_TMR_TYPE_B_CLR = 0xFFFF; //clear timer
    *_TMR_TYPE_B_CON_SET = 0x8000; //start the timer

    while (*_TMR_TYPE_B < us * THRESOLD); //active wait
}
