/* 
 * File:   ks0108.h
 * Author: Paolo
 *
 * Created on September 20, 2013, 5:13 PM
 */

#include "active_delay.h"
#include "pinmask.h"
#include "ascii.h"

#ifndef KS0108_H
#define	KS0108_H

#ifdef	__cplusplus
extern "C" {
#endif

    volatile unsigned int
    *_ks0108_DI, //Data/Instruction [H: Data, L: Instruction]
    *_ks0108_DI_CLR,
    *_ks0108_DI_SET,
    *_ks0108_RW, //Read/Write [H: Read data, L: write data]
    *_ks0108_RW_CLR,
    *_ks0108_RW_SET,
    *_ks0108_E, //Enable: When write (_ks0108_RW = L): data of ks0108_DB is latched at the fall of _ks0108_E
    //when read(_ks0108_RW = H): data is read white E is at higt level
    *_ks0108_CS1, //Chip select for first half (first 64 lines), NEGATIVE LOGIC
    *_ks0108_CS1_CLR,
    *_ks0108_CS1_SET,
    *_ks0108_CS2, //Chip select for second half (last 64 lines), NEGATIVE LOGIC.
    // CS1 AND CS2 BOTH THE SAME VALUES IS WRONG.
    *_ks0108_CS2_CLR,
    *_ks0108_CS2_SET,
    *_ks0108_E_CLR,
    *_ks0108_E_SET,
    *_ks0108_DB[8], //Data Bus [8 pin needs 8 bus]
    *_ks0108_DB_CLR[8],
    *_ks0108_DB_SET[8];

    typedef enum {
        ks0108_OFF = 0,
        ks0108_ON
    } ks0108_display_state;

    typedef struct {
        unsigned short int busy : 1;
        ks0108_display_state state;
        unsigned short int reset : 1;
    } ks0108_status;

    typedef enum {
        ks0108_LEFT,
        ks0108_RIGHT
    } ks0108_side;

    unsigned short int _ks0108_X, _ks0108_Y; //Global positions, always updated

    void ks0108_init(
            volatile unsigned int *DATA_OR_INSTRUCTION,
            volatile unsigned int * READ_WRITE, volatile unsigned int *E,
            volatile unsigned int *CS1,
            volatile unsigned int *CS2,
            volatile unsigned int **DATA_BUS
            );
    void ks0108_set_state(ks0108_display_state state);
    void ks0108_set_start_line(unsigned short int data_bus_bitmask);
    void ks0108_set_address(unsigned short int data_bus_bitmask);
    void ks0108_set_page(unsigned short int data_bus_bitmask);
    ks0108_status ks0108_status_read(void);
    void ks0108_write_data(unsigned short int data_bus_bitmask);
    unsigned short int ks0108_read_data();
    void ks0108_e_high(void);
    void ks0108_e_low(void);
    void ks0108_set_side(ks0108_side side);
    void ks0108_cls(void);
    void ks0108_write_string(char *string);

void extern inline __ks0108_SET_DB_AS_OUTPUT(void);

void extern inline __ks0108_SET_DB_AS_INPUT(void);

void extern inline __ks0108_GOTO_XY(unsigned short X, unsigned short Y);

void extern inline __ks0108_COMMIT(void);

void extern inline __ks0108_NEWLINE(void);


#ifdef	__cplusplus
}
#endif

#endif	/* KS0108_H */

