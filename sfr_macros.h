/* 
 * File:   sfr_macros.h
 * Author: Paolo
 *
 * Created on September 21, 2013, 1:48 AM
 */

#ifndef SFR_MACROS_H
#define	SFR_MACROS_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*
     * SFR is always the first address in stack. This means that after a "position" (the next pointer address) we will find
     * in order the CLR register, SET and INV (for atomic instruction).
     * The parameter sfr MUST BE a pointer to a PORT. Thus, for example, the + 1 mens + sizeof(pointer) = +4
     */
    
#define __SFR_TRIS(PORT) (PORT - 4)
#define __SFR_TRISCLR(PORT) (PORT - 3)
#define __SFR_TRISSET(PORT) (PORT - 2)
#define __SFR_TRISINV(PORT) (PORT - 1)

#define __SFR_PORTCLR(PORT) (PORT + 1)
#define __SFR_PORTSET(PORT) (PORT + 2)
#define __SFR_PORTINV(PORT) (PORT + 3)

#define __SFR_LAT(PORT) (PORT + 4)
#define __SFR_LATCLR(PORT) (PORT + 5)
#define __SFR_LATSET(PORT) (PORT + 6)
#define __SFR_LATINV(PORT) (PORT + 7

#ifdef	__cplusplus
}
#endif

#endif	/* SFR_MACROS_H */

