//===================================================================
// File Name : Test.h
// Function  : Test
// Program   : B.H. Im & Kits   --  Boo-Ree Multimedia Inc.
// Date      : Oct, 25, 2005
// Version   : 0.0
// Mail      : support@boo-ree.com
// Web       : www.boo-ree.com
// History
//===================================================================

#ifndef __TEST_h__
#define __TEST_h__

#ifdef __TEST_c__
#define TEST_EXT
#else
#define TEST_EXT extern
#endif


TEST_EXT void rb_isr(void);
TEST_EXT __near_func void BLDC_Test(void);


#endif   //__TEST_h__
