/* 
 * File:   pinmask.h
 * Author: Paolo
 *
 * Created on September 21, 2013, 2:16 AM
 * Description: this is the configuration file. To use this library you have to setup this file according to your pinmask.
 */

#ifndef PINMASK_H
#define	PINMASK_H

#ifdef	__cplusplus
extern "C" {
#endif


    //Data/Instruction
#define _ks0108_DI_MASK 0x04 //PORTD
    //Read/Write
#define _ks0108_RW_MASK 0x08 //PORTD
    //Enable
#define _ks0108_E_MASK 0x01 //PORTD
    //Chip Select 1 (half screen)
#define _ks0108_CS1_MASK 0x80 //PORTG
    //Chip select 2
#define _ks0108_CS2_MASK 0x40 //PORTG
    //Data bus. The L is MANDATORY ONLY IF in the mask you have values greatere than xFF. In this case x800 and other required long char array
#define _ks0108_DB_MASK L"\x20\x40\x80\x100\x800\x4000\x200\x100" //PORTD, PORTD, PORTD, PORTD, PORTD, PORTB, PORTG, PORTG

#ifdef	__cplusplus
}
#endif

#endif	/* PINMASK_H */

