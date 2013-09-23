/* 
 * File:   pinmask.h
 * Author: Paolo
 *
 * Created on September 21, 2013, 2:16 AM
 */

#ifndef PINMASK_H
#define	PINMASK_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _ks0108_DI_MASK 0x04 //PORTD
#define _ks0108_RW_MASK 0x08 //PORTD
#define _ks0108_E_MASK 0x01 //PORTD
#define _ks0108_CS1_MASK 0x80 //PORTG
#define _ks0108_CS2_MASK 0x40 //PORTG
#define _ks0108_DB_MASK L"\x20\x40\x80\x100\x800\x4000\x200\x100" //PORTD, PORTD, PORTD, PORTD, PORTD, PORTB, PORTG, PORTG

#ifdef	__cplusplus
}
#endif

#endif	/* PINMASK_H */

