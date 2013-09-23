/* 
 * File:   main.c
 * Author: Paolo
 * Always read the PORT
 * Always write the LAT
 *
 * Created on September 20, 2013, 5:12 PM
 */

#include <xc.h>
#include "ks0108.h"
#include "active_delay.h"

int main(void) {
    volatile unsigned int *(bus_port[]) = {&PORTD, &PORTD, &PORTD, &PORTD, &PORTD, &PORTB, &PORTG, &PORTG};
    unsigned short y, x;

    TRISDSET = 0x10; //vincolo per poter usare D2 come porta di output (usata nella pinmask.h per E) è che PORTD.0x10 sia impostato come input, (dalla XRef)

    type_b_timer_config(&TMR2, &T2CON);
    ks0108_init(&PORTD, &PORTD, &PORTD, &PORTG, &PORTG, bus_port);

    /*
     * Always do this step in this order:
     * 0) screen on
     * 1) set_side
     * 2) set_x/set_y
     * 3) write.
     */

    x = y = 0;
    ks0108_set_side(ks0108_LEFT);
    __ks0108_GOTO_XY(x, y);
    while (x < 8) {
        if (y == 64) {
            ks0108_set_side(ks0108_RIGHT);
            __ks0108_GOTO_XY(x, y);
        }
        if (y == 128) {
            y = 0;
            ++x;
            ks0108_set_side(ks0108_LEFT);
            __ks0108_GOTO_XY(x, y);
        }

        ks0108_write_data(1);
        ++y;
    }

    return 0;
}
