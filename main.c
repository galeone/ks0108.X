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

int main(void) {
    volatile unsigned int *(bus_port[]) = {&PORTD, &PORTD, &PORTD, &PORTD, &PORTD, &PORTB, &PORTG, &PORTG};
    unsigned short y, x;

    //TRISDSET = 0x10; //vincolo per poter usare D2 come porta di output (usata nella pinmask.h per E) è che PORTD.0x10 sia impostato come input, (dalla XRef)

    type_b_timer_config(&TMR2, &T2CON);
    ks0108_init(&PORTD, &PORTD, &PORTD, &PORTG, &PORTG, bus_port);

    /*
     * Always do this step in this order (if you want to use raw methods):
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

    type_b_active_delay_ms(1000);

    ks0108_set_side(ks0108_LEFT);
    ks0108_set_state(ks0108_OFF);

    type_b_active_delay_ms(1000);

    ks0108_set_side(ks0108_RIGHT);
    ks0108_set_state(ks0108_OFF);

    type_b_active_delay_ms(1000);

    ks0108_set_state(ks0108_ON);
    ks0108_set_side(ks0108_LEFT);

    type_b_active_delay_ms(1000);

    ks0108_set_state(ks0108_ON);

    ks0108_cls();

    //type_b_active_delay_ms(1000);
    //__ks0108_GOTO_XY(4,24);

    //We can use this method to write string witout worrying about character positioning and encoding, this function works for you)

    ks0108_write_string("SUPER\n    MEGA\n        TEST :D\n\n   ---> http://www.nerdz.eu/ <---\nAndatevene a cagare: \nbrutte seghe    ( cit . )");
    
    return 0;
}
