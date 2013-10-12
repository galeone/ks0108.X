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

    /* Initiazlize the screen, enable both lcds and clear screen.+
     * Set _ks0108_X =  _ks0108_Y = 0 (corner on top-left)
     */
    void ks0108_init(
            volatile unsigned int *DATA_OR_INSTRUCTION,
            volatile unsigned int * READ_WRITE, volatile unsigned int *E,
            volatile unsigned int *CS1,
            volatile unsigned int *CS2,
            volatile unsigned int **DATA_BUS
            );

    /*Set THE CURRENT SELECTED DISPLAY (with set_side) to desired state*/
    void ks0108_set_state(ks0108_display_state state);

    /*Set start line*/
    void ks0108_set_start_line(unsigned short int data_bus_bitmask);

    /* set address (Y coordinate) to desired value.
     * 0 <= data_bus_bitmask < 128
     * ks0108_set_y_address(unsigned short int data_bus_bitmask); is a mnemonic alias defined in ks0108.c
     */
    void ks0108_set_address(unsigned short int data_bus_bitmask);

    /* set page (X coordinate) to desired value.
     * 0 <= data_bus_bitmask < 64
     * ks0108_set_x_address(unsigned short int data_bus_bitmask); is a mnemonic alias defined in ks0108.c
     */
    void ks0108_set_page(unsigned short int data_bus_bitmask);

    /*
     * Read ks0108 controller status and store in in ks0108_status structure
     */
    ks0108_status ks0108_status_read(void);

    /*
     * write RAW data to selected lcd at the current position
     * 0 <= data_bus_bitmask < xFF
     */
    void ks0108_write_data(unsigned short int data_bus_bitmask);

    /*
     * read RAW data at current position
     */
    unsigned short int ks0108_read_data();

    /*
     * set E pin to high logical level
     */
    void ks0108_e_high(void);

    /*
     * set E pin to low logical level
     */
    void ks0108_e_low(void);

    /*
     * enable selected lcd side
     */
    void ks0108_set_side(ks0108_side side);

    /*
     * fill all controller memory with 0, set current position to left-top cornet
     */
    void ks0108_cls(void);

    /*
     * write a string using ascii.c bitmap. The string MUST be a standard ASCII (no extended set) value.
     * 0 <= string[0 .. N] < 128
     * See ascii.c for details
     */
    void ks0108_write_string(char *string);

    /*
     * set data bus as output (clearing tristate registers)
     */
    void extern inline __ks0108_SET_DB_AS_OUTPUT(void);

    /*
     * set data bus as input (filling tristate registers)
     */
    void extern inline __ks0108_SET_DB_AS_INPUT(void);

    /*
     * set current position to lcd and set internal position values _ks0108_X, _ks0108_Y
     */
    void extern inline __ks0108_GOTO_XY(unsigned short X, unsigned short Y);

    /*
     * E pulse for a valid amount of time
     */
    void extern inline __ks0108_COMMIT(void);

    /*
     * go on the next new line, or go on top.
     * (increase X address)
     */
    void extern inline __ks0108_NEWLINE(void);


#ifdef	__cplusplus
}
#endif

#endif	/* KS0108_H */

