//===================================================================
// File Name : SysInit.c
// Function  : System Init
// Program   : maeam  --  Boo-Ree Multimedia Inc.
// Date      : Aug, 20, 2007
// Version   : 1.0
// Mail      : support@boo-ree.com
// Web       : www.boo-ree.com
// History
//===================================================================

#define __SYSINIT_C
#include "includes.h"

__near_func void init_clk(void)
{
	WDT_DISABLE;

	rSYSCFG = 0;
	/* System clock initialize.
	 */
 	while(!(rSYSCFG & MAIN_OSC_STABLE)); 	//Wait for PXI Stable

	/* PLLCLK(Fpll) = EMCLK * (MDIV + 8) / ((PDIV + 2) * (2^SDIV))
	 *              = 12Mhz * (0x28 + 8) / ((0xA + 2) * (2^0))
	 *              = 12Mhz * (48) / 12 = 48Mhz
	 */
 	rPLLCON0 = PLL_EN_EN | PDIV;
 	rPLLCON1 = (MDIV << 2) | SDIV;
 	while(!(rPLLCON0 & PLL_STABLE));		// Wait for PLL Stable

	rPCON = PCON_EF_WAIT_MODE;			// eFlash wait enable.
	rSMCLKCON = SMCLK_EN_VDMA | SMCLK_EN_I80LCD | SMCLK_EN_JPEG | SMCLK_EN_BRAC
		   | FLASH_WAIT_CNT_2 | ONE_CACHE_EN;
	// Using PLL clock @ 24MHz, Fsource = Fsys = 24Mhz
	rCLKCON = CLKO_EMCLK | CLKDIV_1 | CLKSRC_PLLCLK;

	// Enable all system clock
	CLK_EN0_ALL_EN;
	CLK_EN1_ALL_EN;

	/* Interrrupt initialize.
	 */
	rIE0 = 0x00;
	rIE1 = 0x00;
	rIE2 = 0x00;

	rP1MOD1 = GP14_CLKOUT;
}

__near_func void init_wdt(void)
{
	WDT_DISABLE;	// WDT disable, Default settig of WDT is enable.
}

__near_func void init_gpio(void)
{
	// GPIO Setting
	// bit 00 : Output mode , bit 11 : Input mode
	// Note : To prevent IO Leakage current, Set unused port to Output
	// GPIO Setting
	// Bit 11 : Output mode , Bit 00 : Input mode
	// Note : To prevent I/O Leakage current, Set unused port to Output
	rP0 = 0xff;
	rP1 = 0xff;
	rP3 = 0xff;
	rP4 = 0xff;
	rP5 = 0xff;
	rP6 = 0xff;
	rP7 = 0xff;
	rP8 = 0xff;

	rP0MOD0 = 0x00;				// GP00, GP01 : Input
	rP0MOD1 = GP04_DI | GP05_DI;		// GP05_KEY_UP, GP04_KEY_DOWN
	//check	rP0MOD3 = 0x00;				// GP06, GP07 : Input

	rP1MOD0 = 0x80;				// GP1[0:3] : Input
	rP1MOD1 = 0x2A;				// GP1[4:6] : EINT5

	rP3MOD0 = 0xAA;				// GP3[0:3] : Input
	rP3MOD1 = 0xAA;

	rP4MOD0 = 0xAA;				// GP4[0:3] : Input
	rP4MOD1 = 0xAA;				// GP4[4:7] : Input

	rP5MOD0 = 0xAA;				// GP5[0:3] : Input
	rP5MOD1 = 0xAA;				// GP5[4:7] : Input

	rP6MOD0 = 0xA6;				// GP6[0:3] : Input
	rP6MOD1 = 0xAA;				// GP6[4:7] : Input

	rP7MOD0 = 0xAA;				// GP7[0:3] : Input
	rP7MOD1 = 0xAF;				// GP7[4:7] : Input

	rP8MOD0 = 0xAA;				// GP8[0:3] : Input
	
//	rP0PUR = 0x00;					// GP0[0:7] Pull-up Disable
	rP1PUD0 = 0x00;				// GP1[0:3] Pull-up/down Disable
	rP1PUD1 = 0x00;				// GP1[4:6] Pull-up/down Disable
	rP3PUD0 = 0x00;				// GP3[0:3] Pull-up/down Disable
	rP3PUD1 = 0x00;				// GP3[4:7] Pull-up/down Disable
//	rP4PUR = 0x00;					// GP4[0:7] Pull-up Disable
//	rP5PUR = 0x00;					// GP5[0:7] Pull-up Disable
//	rP6PUR = 0x00;					// GP6[0:6] Pull-up Disable
//	rP7PUR = 0x00;					// GP7[0:7] Pull-up Disable
	rP8PUD0 = 0x00;				// GP8[0:3] Pull-up/down Disable

	rP7MOD0 = (rP7MOD0 & ~0xC0) | GP73_DO;
	rP7_b3 = 1;				// LED Off
}

#if 0
/*******************************************************************************
* Function Name  : bmc513_baudrate
* Description    : calculrate uart baudrate value.
* Input          : - clk : 
			CLKSEL_DIV0	0x0
			CLKSEL_EXTUCLK	0x1
			CLKSEL_DIV2	0x2
			CLKSEL_DIV4	0x3
			CLKSEL_DIV8	0x4
			CLKSEL_DIV16	0x5
*                  - baud: 9600, 19200, 38400, 57600, 115200
* Output         : None
* Return         : uart baudrate value
*******************************************************************************/ 
__near_func int bmc513_uart_baudrate(int clk, long baud)
{	
	int 	x;
	long	fsys;
	
	switch (clk) {
		case 0:	fsys = 24000000;
			break;
		case 2: fsys = 24000000/2;
			break;
		case 3: fsys = 24000000/4;
			break;
		case 4:	fsys = 24000000/8;
			break;
		case 5: fsys = 24000000/16;
			break;
		case 1: break; // EXTUCLK
		default:break; // reserved
	}
	
	/*
	 * baudrate = (select CLK)/((CNT0+1)*16)
	 */
	x = fsys/(baud * 16);
	return (x-1);
}
#endif

/*******************************************************************************
* Function Name  : init_uart
* Description    : Initializes the uart peripheral.
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
__near_func void init_uart(uint8_t baud)
{
	rP7MOD1 = (rP7MOD1 & (~0x3C)) | (GP75_UTXD | GP74_URXD);

	rUCON0	= TMODE_EN | RMODE_EN | PMD_NO_PARITY;
	rUCON1	= WL_8 | UBAUDCLK_DIV0;
	rUBAUD	= baud;
//	rUBAUD	= bmc513_uart_baudrate(UBAUDCLK_DIV0, 57600);
	
	rUFCON	= 0;
	rUINTCON= UART_INT_ALL;		

//	printf((char *)"rUBAUD = 0x%x\n", rUBAUD);
}

__near_func void init_timer(uint8_t channel)
{

	// Timer-2 Run : 100ms tick.
	/* TnCLK = Fsys / 2^(CLK_SEL+2), Fsys = 24MHz
	 *    when CLK_SEL = 0 : TnCLK = Fsys / 2^2 = Fsys / 4 = 24MHz / 4 = 6MHz
	 *    when CLK_SEL = 1 : TnCLK = Fsys / 2^3 = Fsys / 8 = 24MHz / 8 = 3MHz
	 * TnOUT = TnCNT / TnCLK, TnCNT = TnOUT * TnCLK
	 *    1ms Time-out : Tcnt = 1ms * 6MHz = 1 * 6 * 10^3 = 6000
	 *    10ms Time-out : Tcnt = 10ms * 6MHz = 10 * 6 * 10^3 = 60000
	 */
	if( channel == 0 ) {
		rCLK_EN0 |= T0_CKEN;				// Timer0 Clock Enable

		// Timer0 clock = Fsys/(2^2) = 6MHz
		rT0DATA  = 6000;						// 1-ms time-out.
		rT0CON   = TINTPEND | SEL_TCLK4 | SEL_INTERVAL | TRUN;
		rIE0     |= IET0;		// Timer0 Match Interrupt enable

		tick_1ms = 0;
	} else if( channel == 1 ) {
		rCLK_EN0 |= T1_CKEN;				// Timer1 Clock Enable

		// Timer0 clock = Fsys/(2^2) = 6MHz
		rT1DATA  = 60000;						// 10-ms time-out.
		rT1CON   = TINTPEND | SEL_TCLK4 | SEL_INTERVAL | TRUN;
		rIE0     |= IET1;		// Timer1 Match Interrupt enable

		tick_10ms = 0;
	}

}

__near_func void init_system(void)
{
	GlobalIntDisable;		// Global Interrupt Disable.
	init_clk();  
	init_wdt(); 			// WDT disable, Default settig of WDT is enable.
	init_gpio();
	init_uart(BAUD_57600);
	init_timer(0);			// 1 ms timer-out
	init_timer(1);			// 10 ms timer-out

//	GlobalIntEnable;		// Global Interrupt Disable.
}

/*		EOF		*/

