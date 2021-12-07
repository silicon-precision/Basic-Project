//===================================================================
// File Name : main.h
// Function  : main program header
// Program   : Boo-Ree Multimedia Inc.
// Date      : February, 04, 2013
// Version   : 0.01
// Mail      : support@boo-ree.com
// Web       : www.boo-ree.com
// History
//===================================================================

#ifndef __MAIN_h__
#define __MAIN_h__

/* variable type definitions */

#ifdef __MAIN_c__
#define MAIN_EXTERN
/** local definitions **/

/** internal functions **/

#else	/* __MAIN_c__ */
#define MAIN_EXTERN			extern
#endif	/* __MAIN_c__ */

/** global variable definitions **/
MAIN_EXTERN volatile uint8_t tick_1ms;
MAIN_EXTERN volatile uint8_t tick_10ms;

/** external functions **/
MAIN_EXTERN __near_func void main(void);

#endif	/* __MAIN_h__ */

