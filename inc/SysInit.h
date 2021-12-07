//===================================================================
// File Name : SysInit.h
// Function  : System Init
// Program   : maeam  --  Boo-Ree Multimedia Inc.
// Date      : Aug, 20, 2007
// Version   : 0.0
// Mail      : support@boo-ree.com
// Web       : www.boo-ree.com
// History
//===================================================================

#ifndef __SYSINIT_h__
#define __SYSINIT_h__

#ifdef  __SYSINIT_c__
#define SYSINIT_EXT
#else
#define SYSINIT_EXT extern
#endif


/* PLL Clock : 48Mhz, when EMCLK is 12Mhz */
#define MDIV	(40)
#define PDIV	(10)
#define SDIV	(0)

//
// Fosc  : 24MHz
// PCON  : 0
// UxCON0: SCSEL = 0
// UxCON1: ECLKSEL = 0, XDRATE = 0
//

//#define BAUD_57600	12			// Fsys = EMCLK(12Mhz)

#define BAUD_57600	0x19			// Fsys = PLL(48Mhz)


SYSINIT_EXT __near_func void init_clk(void);
SYSINIT_EXT __near_func void init_wdt(void);
SYSINIT_EXT __near_func void init_gpio(void);
SYSINIT_EXT __near_func void init_uart(uint8_t buad);

SYSINIT_EXT __near_func void init_system(void);

#endif  //__SYSINIT_h__
