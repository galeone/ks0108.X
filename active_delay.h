/* 
 * File:   active_delay.h
 * Author: Paolo Galeone
 *
 * Created on September 20, 2013, 5:21 PM
 */

#include "sfr_macros.h"

#ifndef ACTIVE_DELAY_H
#define	ACTIVE_DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

    volatile unsigned int *_TMR_TYPE_B_CON_CLR,
    *_TMR_TYPE_B_CON_SET,
    *_TMR_TYPE_B_CLR,
    *_TMR_TYPE_B;

    /*
     * Clock is 80 Mhz, _TMR_TYPE_B prescale is 256
     * This PIC had a 5 stage pipeline, so 1 instruction needs 5 clock periods
     * -> so 1 tick each (80 Mhz / 5 ) / 256 = 62500 Hz = 62.5 Khz
     * _TMR_TYPE_B is 16 bit wide, so it overflows every 2^16 = 65536 count >  62500 => diff = 65536 - 62500 = 3036
     * So has passed a second when _TMR_TYPE_B = 62500
     * So, a millisecond is passed when _TMR_TYPE_B = (62500/1000) = 62.5, rounded to 62 because of function calling that introduces delay
     */
    void type_b_active_delay_ms(int ms);

    /*
     * Clock is 80 Mhz, _TMR_TYPE_B_2 prescale is 8
     * This PIC had a 5 stage pipeline, so 1 instruction needs 5 clock periods
     * -> so 1 tick each (80 Mhz / 5 ) / 8 = 2 000 000 Hz = 2 MHz
     * So, a microsecond is passed when _TMR_TYPE_B_2 = (2000000/100000) = 2
     */
    void type_b_active_delay_us(int us);

#ifdef	__cplusplus
}
#endif

#endif	/* ACTIVE_DELAY_H */

