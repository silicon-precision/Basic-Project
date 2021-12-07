/**************************************************
 *
 * This module contains the function `__low_level_init', a function
 * that is called before the `main' function of the program.  Normally
 * low-level initializations - such as setting the prefered interrupt
 * level or setting the watchdog - can be performed here.
 *
 * Note that this function is called before the data segments are
 * initialized, this means that this function can't rely on the
 * values of global or static variables.
 *
 * When this function returns zero, the startup code will inhibit the
 * initialization of the data segments.  The result is faster startup,
 * the drawback is that neither global nor static data will be
 * initialized.
 *
 * Copyright 2003 IAR Systems. All rights reserved.
 *
 * $Revision: 5241 $
 *
 * $Log $
 *
 **************************************************/

#ifdef __cplusplus
extern "C" {
#endif
//#include "BMC513_REGDEF.h"
#pragma language=extended

//
// Locate low_level_init in the CSTART module
//
#pragma location="CSTART"
//
// If the code model is banked, low_level_init must be declared
// __near_func elsa a ?BRET is performed
//
#if (__CODE_MODEL__ == 2)
__near_func __root char
#else
__root char
#endif
__low_level_init(void)
{
//	void (*run)(void) = (void (*)(void))0x200;
	/*==================================*/
	/*  Initialize hardware.            */
	/*==================================*/
//	if( rP1_b2 == 0 )
//		run();
	/*==================================*/
	/* Choose if segment initialization */
	/* should be done or not.           */
	/* Return: 0 to omit seg_init       */
	/*         1 to run seg_init        */
	/*==================================*/
	return (1);
}

#pragma language=default

#ifdef __cplusplus
}
#endif

