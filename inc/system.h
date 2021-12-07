//===================================================================
// File Name : System.h
// Function  : System
// Program   : B.H. Im & Kits   --  Boo-Ree Multimedia Inc.
// Date      : Oct, 25, 2005
// Version   : 0.0
// Mail      : support@boo-ree.com
// Web       : www.boo-ree.com
// History
//===================================================================

#ifndef __SYSTEM_h__
#define __SYSTEM_h__

#ifdef __SYSTEM_c__
#define SYSTEM_EXT
#else
#define SYSTEM_EXT extern
#endif


SYSTEM_EXT __near_func void mdelay(uint16_t ms);
SYSTEM_EXT __near_func void delay(uint8_t sec);

SYSTEM_EXT __near_func int getkey(void);
SYSTEM_EXT __near_func void putch(uint8_t uByte);
SYSTEM_EXT __near_func void putint(uint8_t val, uint8_t cr);
SYSTEM_EXT __near_func void puthex(uint8_t val, uint8_t cr);
SYSTEM_EXT __near_func void putstr(const char __code *ptr);


#endif   //__SYSTEM_h__
