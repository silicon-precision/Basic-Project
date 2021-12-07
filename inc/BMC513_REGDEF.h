#ifndef __BMC513_REGDEF_h__
#define __BMC513_REGDEF_h__




//============================================================================
//      Compiler Dependent Definitions
//============================================================================


#if defined SDCC			// SDCC - Small Device C Compiler

	// ---------------------------------------------------------------------------
	#define SBIT(_ADDR,	_NAME)	__sbit  __at _ADDR	_NAME
	#define SFR(_ADDR,	_NAME)	__sfr   __at _ADDR	_NAME
	#define SFR16(_ADDR,_NAME)	__no_init volatile unsigned char _NAME @ _ADDR

	#define SFR_B_BITS(_ADDR, _NAME, _A,_B,_C,_D,_E,_F,_G,_H) \
		SFR(_ADDR,	_NAME); 			 \
		SBIT(_ADDR+0, _NAME ## _ ## _A); \
		SBIT(_ADDR+1, _NAME ## _ ## _B); \
		SBIT(_ADDR+2, _NAME ## _ ## _C); \
		SBIT(_ADDR+3, _NAME ## _ ## _D); \
		SBIT(_ADDR+4, _NAME ## _ ## _E); \
		SBIT(_ADDR+5, _NAME ## _ ## _F); \
		SBIT(_ADDR+6, _NAME ## _ ## _G); \
		SBIT(_ADDR+7, _NAME ## _ ## _H) 

	#define SFR_B(_ADDR, _NAME) 	SFR_B_BITS(_ADDR, _NAME, b0, b1, b2, b3, b4, b5, b6, b7)
	// ---------------------------------------------------------------------------

#elif defined __ICC8051__	// IAR 8051

	// ---------------------------------------------------------------------------
	#include <stdbool.h>
	#define SFR(_ADDR,	_NAME)	__sfr	__no_init volatile unsigned char _NAME	@ _ADDR
	#define SFR_WORD(_ADDR,	_NAME)	__sfr	__no_init volatile unsigned short _NAME	@ _ADDR
	#define SFR16(_ADDR,_NAME)	__no_init volatile unsigned char _NAME @ _ADDR
	#define SFR16_WORD(_ADDR,_NAME) 		\
		__no_init volatile union {			\
			unsigned short _NAME;			\
			struct {						\
				unsigned char _NAME ## 0;	\
				unsigned char _NAME ## 1;	\
			};								\
		} @ _ADDR

	#define SFR_B_BITS(_ADDR, _NAME, _A,_B,_C,_D,_E,_F,_G,_H) \
	__sfr __no_init volatile union  {     	  \
		unsigned char   _NAME;                \
		struct 	{                         	  \
			unsigned char _NAME ## _ ## _A:1, \
			              _NAME ## _ ## _B:1, \
			              _NAME ## _ ## _C:1, \
			              _NAME ## _ ## _D:1, \
			              _NAME ## _ ## _E:1, \
			              _NAME ## _ ## _F:1, \
			              _NAME ## _ ## _G:1, \
			              _NAME ## _ ## _H:1; \
   		};  								  \
	} @ _ADDR


	#define SFR_B(_ADDR, _NAME) 	SFR_B_BITS(_ADDR, _NAME, b0, b1, b2, b3, b4, b5, b6, b7)
	// ---------------------------------------------------------------------------

#endif



//============================================================================
//      Type Definitions
//============================================================================
typedef signed char			int8_t;
typedef unsigned char		uint8_t;
typedef signed int			int16_t;
typedef unsigned int		uint16_t;
typedef signed long			int32_t;
typedef unsigned long		uint32_t;


//#define bool   				unsigned char			// 1 Byte
#define BOOL   				unsigned char			// 1 Byte
#define CHAR				signed   char			// 1 Byte
#define UCHAR				unsigned char			// 1 Byte
#define uchar				unsigned char			// 1 Byte
#define UINT				unsigned int			// 2 Bytes
#define USHORT				unsigned short			// 2 Bytes
#define ushort				unsigned short			// 2 Bytes
#define BYTE   				unsigned char			// 1 Byte
#define WORD				unsigned short			// 2 Bytes
#define DWORD  				unsigned long			// 4 Bytes
#define SLONG  				signed long			// 4 Bytes
#define ULONG  				unsigned long			// 4 Bytes
#define LONG  				unsigned long			// 4 Bytes



#define TRUE				0x01
#ifndef true
#define true				0x01
#endif
#define FALSE				0x00
#ifndef false
#define false				0x00
#endif

typedef union {
	BYTE b[2];
	UINT i;
}Byte2;


typedef union {
	BYTE b[4];
	ULONG l;
}Byte4;

//============================================================================
//      SFR Registers
//============================================================================

// ---------------------------------------------------------------------------
//  SFR_B(0x80, rP0); Expands to:
//	
//  SFR(0x80, rP0);			// GPIO 0
//	SBIT(0x80, rP0_b0);		// GPIO 0.0
//	SBIT(0x81, rP0_b1);		// GPIO 0.1				
//	SBIT(0x82, rP0_b2);		// GPIO 0.2
//	SBIT(0x83, rP0_b3);		// GPIO 0.3
//	SBIT(0x84, rP0_b4);		// GPIO 0.4
//	SBIT(0x85, rP0_b5);		// GPIO 0.5
//	SBIT(0x86, rP0_b6);		// GPIO 0.6
//	SBIT(0x87, rP0_b7);		// GPIO 0.7
// ---------------------------------------------------------------------------

/***************
*  SFR GROUP 80  *
****************/
SFR_B(0x80, rP0);		// General Purpose I/O 0
SFR(0x81, rSP);			// STACK POINTER
SFR(0x82, rDP0L);		// DATA  POINTER 0 - LOW  BYTE
SFR(0x83, rDP0H);		// DATA  POINTER 0 - HIGH BYTE
SFR(0x84, rDP1L);		// DATA  POINTER 1 - LOW  BYTE
SFR(0x85, rDP1H);		// DATA  POINTER 1 - HIGH BYTE
SFR(0x86, rDPSEL);		// DPTR  Selector
SFR_B(0x88, rP5);		// General Purpose I/O 4

/***************
*  SFR GROUP 90  *
****************/
SFR_B(0x90, rP1);		// General Purpose I/O 1
SFR(0x91, rGIE);		// Global Interrupt Enable
SFR(0x92, rIE0);		// INT Enable 0
SFR(0x93, rIP0);		// INT Priority 0
SFR(0x94, rIE1);		// INT Enable 1
SFR(0x95, rIP1);		// INT Priority 1
SFR(0x96, rIE2);		// INT Enable 2
SFR(0x97, rIP2);		// INT Priority 2
SFR_B(0x98, rP6);		// General Purpose I/O 5
SFR(0x99, rIE3);		// INT Enable 3
SFR(0x9A, rIP3);		// INT Priority 3

/***************
*  SFR GROUP A0  *
****************/
SFR(0xA1, rROMB);		// ROM Bank Selection, [5:0] : ROM  Bank
SFR(0xA2, rXRAMB);		// Data Memory Bank Selection, [5:0] : XRAM Bank
SFR(0xA3, rCLKCON);		// Clock Control Register
SFR(0xA4, rSMCLKCON);		// Smart Clock Control Register
SFR(0xA5, rCLK_EN0);		// Peripheral Clock Enable Register 0
SFR(0xA6, rCLK_EN1);		// Peripheral Clock Enable Register 1
SFR(0xA7, rPCON);		// Power Control Register
SFR(0xA8, rRSTCON);		// Reset Control Register
SFR(0xA9, rRSTSTAT);	// Reset and Wakeup Status Register
SFR(0xAA, rSYSCFG);		// Clock output select through GP17
SFR(0xAB, rIVCON0);		// IVC Control Register 0
SFR(0xAC, rIVCON1);		// IVC Control Register 1
SFR(0xAD, rWKUPSTAT);	// WakeUp State Register from STOP 
SFR(0xAE, rPLLCON0);	// PLL control Register 0 
SFR(0xAF, rPLLCON1);	// PLL control Register 1 

/***************
*  SFR GROUP B0  *
****************/
SFR_B(0xB0, rP3);			// General Purpose I/O 3
SFR(0xB1, rUSBFA);		// USB Function address register
SFR(0xB2, rUSBPM);		// USB Power Management register
SFR(0xB3, rUSBIPEND);		// USB Interrupt Pending register
SFR(0xB4, rUSBINTEN);		// USB Interrupt Enable register
SFR(0xB5, rUSBFN_L);		// USB Frame Number L register
SFR(0xB6, rUSBFN_H);		// USB Frame Number H register
SFR(0xB7, rUSBEP0CSR0);		// USB EP 0 Common Status Register 0
SFR_B(0xB8, rP7);		// General Purpose I/O 7
SFR(0xB9, rUSBEP0CSR1);		// USB EP 0 Common Status Register 1
SFR(0xBA, rUSBEP1CSR0);		// USB EP 1 Common Status Register 0
SFR(0xBB, rUSBEP1CSR1);		// USB EP 1 Common Status Register 1
SFR(0xBC, rUSBEP1CSR2);		// USB EP 1 Common Status Register 2
SFR(0xBD, rUSBEP1CSR3);		// USB EP 1 Common Status Register 3
SFR(0xBE, rUSBEP2CSR0);		// USB EP 2 Common Status Register 0
SFR(0xBF, rUSBEP2CSR1);		// USB EP 2 Common Status Register 1

/***************
*  SFR GROUP C0  *
****************/
SFR_B(0xC0, rP4);		// General Purpose I/O 4
SFR(0xC1, rUSBEP2CSR2);		// USB EP 2 Common Status Register 2
SFR(0xC2, rUSBEP2CSR3);		// USB EP 2 Common Status Register 3
SFR(0xC3, rUSBEP3CSR0);		// USB EP 3 Common Status Register 0
SFR(0xC4, rUSBEP3CSR1);		// USB EP 3 Common Status Register 1
SFR(0xC5, rUSBEP3CSR2);		// USB EP 3 Common Status Register 2
SFR(0xC6, rUSBEP3CSR3);		// USB EP 3 Common Status Register 3
SFR(0xC7, rUSBEP4CSR0);		// USB EP 4 Common Status Register 0
SFR(0xC8, rUSBEP4CSR1);		// USB EP 4 Common Status Register 1
SFR(0xC9, rUSBEP4CSR2);		// USB EP 4 Common Status Register2
SFR(0xCA, rUSBEP4CSR3);		// USB EP 4 Common Status Register 3
SFR(0xCB, rUSBEP0WC);		// USB EP 0 Write Count Register
SFR(0xCC, rUSBEP1WC1);		// USB EP 1 Write Count Register 1
SFR(0xCD, rUSBEP1WC2);		// USB EP 1 Write Count Register 2
SFR(0xCE, rUSBEP2WC1);		// USB EP 2 Write Count Register 1
SFR(0xCF, rUSBEP2WC2);		// USB EP 2 Write Count Register 2

/***************
*  SFR GROUP D0  *
****************/
SFR(0xD1, rUSBEP3WC1);		// USB EP 3 Write Count Register 1
SFR(0xD2, rUSBEP3WC2);		// USB EP 3 Write Count Register 2
SFR(0xD3, rUSBEP4WC1);		// USB EP 4 Write Count Register 1
SFR(0xD4, rUSBEP4WC2);		// USB EP 4 Write Count Register 2
SFR(0xD5, rUSBEP0FIFO);		// USB EP 0 FIFO Register
SFR(0xD6, rUSBEP1FIFO);		// USB EP 1 FIFO Register
SFR(0xD7, rUSBEP2FIFO);		// USB EP 2 FIFO Register
SFR(0xD8, rUSBEP3FIFO);		// USB EP 3 FIFO Register
SFR(0xD9, rUSBEP4FIFO);		// USB EP 4 FIFO Register
SFR(0xDA, rUSBEPLNUM1);		// USB EP Logical Number Control Register 1
SFR(0xDB, rUSBEPLNUM2);		// USB EP Logical Number Control Register 2
SFR(0xDC, rUSBNAKCON1);		// USB EP NAK Control Register 1
SFR(0xDD, rUSBNAKCON2);		// USB EP NAK Control Register 2
SFR(0xDE, rUSBNAKEN);		// USB EP NAK Enable Register
SFR(0xDF, rUSBCONF);		// USB Configuration Register

/***************
*  SFR GROUP E0  *
****************/
SFR(0xE0, rACC);		// ACC (Accumulator);
SFR(0xE1, rADCON0);		// ADC Control Register 0
SFR(0xE2, rADCON1);		// ADC Control Register 1
SFR(0xE3, rADAT0);		// AD Conversion LOWER Result Register
SFR(0xE4, rADAT1);		// AD Conversion HIGHER Result Register
SFR(0xE5, rADREF);		// ADC Reference Register
SFR(0xE6, rADREFCMP);		// ADC Reference Compare Register
SFR_B(0xE8, rP8);		// General Purpose I/O 8
SFR(0xEC, rWDTCON);		// WDT Control Register
SFR(0xED, rWCNTCLK);		// WDT Counter clock select
SFR(0xEE, rWDTCNT);		// WDT Counter
SFR(0xEF, rWDTREF);		// WDT Reference Value



/***************
*  SFR GROUP F0  *
****************/
SFR(0xF0, rB);			// B Register
SFR(0xF1, rUCON0);		// UART Control Register 0
SFR(0xF2, rUCON1);		// UART Control Register 1
SFR(0xF3, rUTRSTAT);		// UART TX/RX Status Register
SFR(0xF4, rUERSTAT);		// UART RX Error Status Register
SFR(0xF5, rUINTCON);		// UART Interrupt Register
SFR(0xF6, rUBAUD);		// UART Baud Rate Divisor Register
SFR(0xF7, rURXBUF);		// UART Receive Buffer
SFR(0xF8, rUTXBUF);		// UART Transmit Buffer
SFR(0xF9, rUFCON);		// UART FIFO Control Register  
//SFR(0xFA, rUFTSTAT);		// UART TX FIFO Status Register         
//SFR(0xFB, rUFRSTAT);		// UART RX FIFO Status Register         
SFR(0xFC, rSPIMOD);		// SPI Mode Register 
SFR(0xFD, rSPICK);		// SPI Baud Rate counter clock select Register       
SFR(0xFE, rSPIDATA0);		// SPI Transmit and Receive Data 0                   
SFR(0xFF, rSPIDATA1);		// SPI Transmit and Receive Data 1                   


//============================================================================
//      Bit addressable SFR Registers
//============================================================================

// ---------------------------------------------------------------------------
//  SFR_B_BITS(0xC0, rTCON,		T0RUN, T0CLR, T1RUN, T1CLR, T2RUN, T2CLR, RSVD6, RSVD7);
//	
//  Expands to:
//	
//  SFR(0xC0, rTCON);			// Timer 0/1/2 Control register
//	SBIT(0xC0, rTCON_T0RUN);	// Enable Timer 0                        
//	SBIT(0xC1, rTCON_T0CLR);	// Clear Timer 0 counter (T0CNT1, T0CNT0)		
//	SBIT(0xC2, rTCON_T1RUN);	// Enable Timer 1                        
//	SBIT(0xC3, rTCON_T1CLR);	// Clear Timer 1 counter (T1CNT1, T1CNT0)
//	SBIT(0xC4, rTCON_T2RUN);	// Enable Timer 2                        
//	SBIT(0xC5, rTCON_T2CLR);	// Clear Timer 2 counter (T2CNT1, T2CNT0)
// ---------------------------------------------------------------------------

// 0xD0 PSW			// Program Status Word
SFR_B_BITS(0xD0, rPSW,		P, F1, OV, RS0, RS1, F0, AC, CY);
					// rPSW_P 		: Parity Flag
					// rPSW_F1 		: Flag1 available to the user for general purpose.  								   
					// rPSW_OV 		: Overflow Flag
					// rPSW_RS0		: Register Bank Select 0
					// rPSW_RS1		: Register Bank Select 1
					// rPSW_F0 		: Flag0 available to the user for general purpose.  
					// rPSW_AC 		: Auxiliary Carry Flag
					// rPSW_CY 		: Carry Flag


//============================================================================
//      Extended SFR Registers
//============================================================================
// TIMER
SFR16(0xfe00, rT0CON);	  // TIMER 0 Control Register
SFR16_WORD(0xFE01, rT0DATA);
SFR16_WORD(0xFE03, rT0CNT);
SFR16_WORD(0xFE05, rT0PDR);
//SFR16(0xfe01, rT0DATA0);	// TIMER 0 Reference Data Register 0
//SFR16(0xfe02, rT0DATA1);	// TIMER 0 Reference Data Register 1
//SFR16(0xfe03, rT0CNT0);	// TIMER 0 LOWER Counter
//SFR16(0xfe04, rT0CNT1);	// TIMER 0 UPPER Counter
//SFR16(0xfe05, rT0PDR0);	// TIMER 0 PWM Data Register 0
//SFR16(0xfe06, rT0PDR1);	// TIMER 0 PWM Data Register 1

SFR16(0xfe08, rT1CON);	  // TIMER 1 Control Register
SFR16_WORD(0xFE09, rT1DATA);
SFR16_WORD(0xFE0B, rT1CNT);
SFR16_WORD(0xFE0D, rT1PDR);
//SFR16(0xfe09, rT1DATA0);	// TIMER 1 Reference Data Register 0
//SFR16(0xfe0a, rT1DATA1);	// TIMER 1 Reference Data Register 1
//SFR16(0xfe0b, rT1CNT0);	// TIMER 1 LOWER Counter
//SFR16(0xfe0c, rT1CNT1);	// TIMER 1 UPPER Counter
//SFR16(0xfe0d, rT1PDR0);	// TIMER 1 PWM Data Register 0
//SFR16(0xfe0e, rT1PDR1);	// TIMER 1 PWM Data Register 1

SFR16(0xfe10, rT2CON);	  // TIMER 2 Control Register
SFR16_WORD(0xFE11, rT2DATA);
SFR16_WORD(0xFE13, rT2CNT);
SFR16_WORD(0xFE15, rT2PDR);
//SFR16(0xfe11, rT2DATA0);	// TIMER 2 Reference Data Register 0
//SFR16(0xfe12, rT2DATA1);	// TIMER 2 Reference Data Register 1
//SFR16(0xfe13, rT2CNT0);	// TIMER 2 LOWER Counter
//SFR16(0xfe14, rT2CNT1);	// TIMER 2 UPPER Counter
//SFR16(0xfe15, rT2PDR0);	// TIMER 2 PWM Data Register 0
//SFR16(0xfe16, rT2PDR1);	// TIMER 2 PWM Data Register 1



// Com/Seg LCD Controller
SFR16(0xfe20,  rLCON);	      // LCON
SFR16(0xfe21,  rLMOD);	      // LMOD
SFR16(0xfe22,	rLCKSEL);	    // CKSEL
SFR16(0xfe30,	rDISP_MEM0);	//
SFR16(0xfe31,	rDISP_MEM1);	//
SFR16(0xfe32,	rDISP_MEM2);	//
SFR16(0xfe33,	rDISP_MEM3);	//
SFR16(0xfe34,	rDISP_MEM4);	//
SFR16(0xfe35,	rDISP_MEM5);	//
SFR16(0xfe36,	rDISP_MEM6);	//
SFR16(0xfe37,	rDISP_MEM7);	//
SFR16(0xfe38,	rDISP_MEM8);	//
SFR16(0xfe39,	rDISP_MEM9);	//
SFR16(0xfe3a,	rDISP_MEM10);	//
SFR16(0xfe3b,	rDISP_MEM11);	//
SFR16(0xfe3c,	rDISP_MEM12);	//
SFR16(0xfe3d,	rDISP_MEM13);	//
SFR16(0xfe3e,	rDISP_MEM14);	//
SFR16(0xfe3f,	rDISP_MEM15);	//


// PORT mode
SFR16(0xfe40, rJTAGOFF);    // JTAG Port (gpio 3) disable
SFR16(0xfe41, rEINTMOD0);   // External Interrupt Control Register 0
SFR16(0xfe42, rEINTMOD1);   // External Interrupt Control Register 1
SFR16(0xfe43, rEINTMOD2);   // External Interrupt Control Register 2
SFR16(0xfe44, rEINTMOD3);   // External Interrupt Control Register 3
SFR16(0xfe45, rEINTEN0);    // External Interrupt Enable Register 0
SFR16(0xfe46, rEINTEN1);    // External Interrupt Enable Register 1
SFR16(0xfe47, rEINTPND0);   // External Interrupt Pending Register 0
SFR16(0xfe48, rEINTPND1);   // External Interrupt Pending Register 1
SFR16(0xfe49, rP0MOD0);  	 // GP00 ~ GP01 mode control register
SFR16(0xfe4A, rP0MOD1);  	 // GP02 ~ GP03 mode control register
SFR16(0xfe4B, rP0PU);  	   // GP00 ~ GP07 Pullup control register
SFR16(0xfe4C, rP1MOD0);  	 // GP10 ~ GP13 mode control register
SFR16(0xfe4D, rP1MOD1);  	 // GP14 ~ GP16 mode control register
SFR16(0xfe4E, rP1PUD0);  	 // GP10 ~ GP13 Pullup/down control register
SFR16(0xfe4F, rP1PUD1);  	 // GP14 ~ GP17 Pullup/down control register
SFR16(0xfe50, rP3MOD0);  	 // GP30 ~ GP33 mode control register
SFR16(0xfe51, rP3MOD1);  	 // GP34 ~ GP37 mode control register
SFR16(0xfe52, rP3PUD0);  	 // GP30 ~ GP33 Pullup/down control register
SFR16(0xfe53, rP3PUD1);  	 // GP34 ~ GP37 Pullup/down control register
SFR16(0xfe54, rP4MOD0);  	 // GP40 ~ GP43 mode control register
SFR16(0xfe55, rP4MOD1);  	 // GP44 ~ GP47 mode control register
SFR16(0xfe56, rP4PU);  	   // GP40 ~ GP47 Pullup control register
SFR16(0xfe57, rP5MOD0);  	 // GP50 ~ GP53 mode control register
SFR16(0xfe58, rP5MOD1);  	 // GP54 ~ GP57 mode control register
SFR16(0xfe59, rP5PU);  	   // GP50 ~ GP57 Pullup control register
SFR16(0xfe5A, rP6MOD0);  	 // GP60 ~ GP63 mode control register
SFR16(0xfe5B, rP6MOD1);  	 // GP64 ~ GP67 mode control register
SFR16(0xfe5C, rP6PU);  	   // GP60 ~ GP67 Pullup control register
SFR16(0xfe5D, rP7MOD0);  	 // GP70 ~ GP73 mode control register
SFR16(0xfe5E, rP7MOD1);  	 // GP74 ~ GP77 mode control register
SFR16(0xfe5F, rP7PU);  	   // GP70 ~ GP77 Pullup control register
SFR16(0xfe60, rP8MOD0);  	 // GP80 ~ GP83 mode control register
SFR16(0xfe61, rP8MOD1);  	 // GP84 ~ GP87 mode control register
SFR16(0xfe62, rP8PUD0);  	 // GP80 ~ GP83 Pullup control register
SFR16(0xfe63, rP8PUD1);  	 // GP84 ~ GP87 Pullup control register


// BRAC
SFR16(0xff00, rBRAC_CTRL);          // BRAC¢ç Decoding Control Register
SFR16(0xff01, rBRAC_CTRL2);         // BRAC¢ç Decoding Control Register 2
SFR16(0xff02, rBRAC_INT_EN);        // BRAC Interrupt Enable Register
SFR16(0xff03, rBRAC_INT_PEND);      // BRAC Interrupt Pending Register

SFR16(0xff04, rBRAC_START_ADRL);    // BRAC¢ç decoding LOW Start Address
SFR16(0xff05, rBRAC_START_ADRM);    // BRAC¢ç decoding MIDDLE Start Address
SFR16(0xff06, rBRAC_START_ADRH);    // BRAC¢ç decoding HIGH Start Address
SFR16(0xff07, rBRAC_SIZEL);         // BRAC¢ç data size LOW
SFR16(0xff08, rBRAC_SIZEM);         // BRAC¢ç data size MIDDLE
SFR16(0xff09, rBRAC_SIZEH);         // BRAC¢ç data size HIGH
SFR16(0xff0a, rIBB_READ_PTR_CH0);   // IBB Read Pointer for Channel 0 (for external NAND FLASH

SFR16(0xff0b, rBRAC_ADDR);          // Address for BRAC¢ç Decoding
SFR16(0xff0c, rBRAC_DATA);          // Data for BRAC¢ç Decoding
SFR16(0xff0d, rBRAC_BUFF);          // Buffer for BRAC¢ç Decoding
SFR16(0xff0e, rBRAC_CTRL3);         // BRAC¢ç Decoding Control Register 3

SFR16(0xff10, rBRAC_ENC_CTRL);      // Encoding Control Register
SFR16(0xff11, rBRAC_ENC_SAMPLE_L);  // Encoding PCM Sample High
SFR16(0xff12, rBRAC_ENC_SAMPLE_H);  // Encoding PCM Sample High
SFR16(0xff13, rBRAC_ENC_RESULT);    // Encoding Result Register

SFR16(0xff18, rDAC_CTL);            // DAC Control Register	
SFR16(0xff19, rDACOUT_L);           // DAC LOW Output Register
SFR16(0xff1a, rDACOUT_H);           // DAC HIGH Output Register
SFR16(0xff1b, rVOLUME);             // Volume Control Register in Decoding Mode
             
SFR16(0xff1c, rDCOL);               //
SFR16(0xff1d, rDCOH);               //

SFR16(0xff20, rSFCTRL);          // SF Control register
SFR16(0xff21, rSFPORT);          // SF Receive/Transmit Buffer
SFR16(0xff22, rSFDMA_CTRL);         // SF Read-DMA Control register
SFR16(0xff23, rSFDMA_START_ADRL);   // SF Read-DMA start address [7:0]
SFR16(0xff24, rSFDMA_START_ADRM);   // SF Read-DMA start address [15:8]
SFR16(0xff25, rSFDMA_START_ADRH);   // SF Read-DMA start address [23:16]
SFR16(0xff26, rSFDMA_RXBUF);        // SF Read-DMA RX Buffer
SFR16(0xff27, rSFDMA_TSIZE);        // SF Read-DMA Transfer Size
SFR16(0xff28, rSFDMA_XBASE_L);      // SF Read-DMA XRAM Base Address Low
SFR16(0xff29, rSFDMA_XBASE_H);      // SF Read-DMA XRAM Base Address High
SFR16(0xff2a, rSFCTRL2);         // SF Control register 2

// BRJPEG
SFR16(0xFF40, rBRJPEG_BUF_PTR_L);    // BRJPEG Buffer XRAM base
SFR16(0xFF41, rBRJPEG_BUF_PTR_H);    // BRJPEG Buffer XRAM base
SFR16(0xFF42, rBRJPEG_TABLE_PTR_L);  // BRJPEG Coef Flash base
SFR16(0xFF43, rBRJPEG_TABLE_PTR_H);  // BRJPEG Coef Flash base
SFR16(0xFF44, rBRJPEG_IBB_PTR_L);    // BRJPEG Bit Stream Flash pointer
SFR16(0xFF45, rBRJPEG_IBB_PTR_M);    // BRJPEG Bit Stream Flash pointer
SFR16(0xFF46, rBRJPEG_IBB_PTR_H);    // BRJPEG Bit Stream Flash pointer
SFR16(0xFF47, rBRJPEG_IBB_XRAM_PTR); // BRJPEG Bit Stream XRAM pointer
SFR16(0xFF48, rBRJPEG_GET_BUFFER_L); // BRJPEG Stream buffer
SFR16(0xFF49, rBRJPEG_GET_BUFFER_M); // BRJPEG Stream buffer
SFR16(0xFF4A, rBRJPEG_GET_BUFFER_H); // BRJPEG Stream buffer
SFR16(0xFF4B, rBRJPEG_BITS_LEFT);    // BRJPEG Bits left register
SFR16(0xFF4C, rBRJPEG_GET_PEEK_L);   // BRJPEG return for get/peak bits
SFR16(0xFF4D, rBRJPEG_GET_PEEK_H);   // BRJPEG return for get/peak bits
SFR16(0xFF4E, rBRJPEG_QP_Y);         // BRJPEG QP for luma
SFR16(0xFF4F, rBRJPEG_QP_C);         // BRJPEG QP for chroma
         
SFR16(0xFF50, rBRJPEG_PREV_DC_Y_L);  // BRJPEG previous dc for Y
SFR16(0xFF51, rBRJPEG_PREV_DC_Y_H);  // BRJPEG previous dc for Y
SFR16(0xFF52, rBRJPEG_PREV_DC_CB_L); // BRJPEG previous dc for CB
SFR16(0xFF53, rBRJPEG_PREV_DC_CB_H); // BRJPEG previous dc for CB
SFR16(0xFF54, rBRJPEG_PREV_DC_CR_L); // BRJPEG previous dc for CR
SFR16(0xFF55, rBRJPEG_PREV_DC_CR_H); // BRJPEG previous dc for CR
SFR16(0xFF56, rBRJPEG_CFG);          // BRJPEG Configuration
SFR16(0xFF57, rBRJPEG_BUFSEL);       // BRJPEG Buf allocation
SFR16(0xFF58, rBRJPEG_CMD);          // BRJPEG Command
SFR16(0xFF59, rBRJPEG_IE);           // BRJPEG Interrupt Enable
SFR16(0xFF5A, rBRJPEG_ICLR);         // BRJPEG Interrupt Clear
SFR16(0xFF5B, rBRJPEG_ST);           // BRJPEG Status
SFR16(0xFF5C, rBRJPEG_VLD_MODE);     // BRJPEG VLD mode
SFR16(0xFF5D, rBRJPEG_IDCT_MODE);    // BRJPEG IDCT mode
SFR16(0xFF5E, rBRJPEG_RESERVED_0); 
SFR16(0xFF5F, rBRJPEG_RESERVED_1); 

SFR16(0xFF60, rBRJPEG_IDCT_ACC_0);  // BRJPEG IDCT Accumulator
SFR16(0xFF61, rBRJPEG_IDCT_ACC_1);  // BRJPEG IDCT Accumulator
SFR16(0xFF62, rBRJPEG_IDCT_ACC_2);  // BRJPEG IDCT Accumulator
SFR16(0xFF63, rBRJPEG_IDCT_ACC_3);  // BRJPEG IDCT Accumulator
SFR16(0xFF64, rBRJPEG_RESERVED_2);  //
SFR16(0xFF65, rBRJPEG_RESERVED_3);  //
SFR16(0xFF66, rBRJPEG_RESERVED_4);  //
SFR16(0xFF67, rBRJPEG_RESERVED_5);  //
SFR16(0xFF68, rBRJPEG_RESERVED_6);  //
SFR16(0xFF69, rBRJPEG_RESERVED_7);  //
SFR16(0xFF6A, rBRJPEG_RESERVED_8);  //
SFR16(0xFF6B, rBRJPEG_RESERVED_9);  //
SFR16(0xFF6C, rBRJPEG_RESERVED_A);  //
SFR16(0xFF6D, rBRJPEG_RESERVED_B);  //
SFR16(0xFF6E, rBRJPEG_RESERVED_C);  //
SFR16(0xFF6F, rBRJPEG_RESERVED_D);  //


// RTC
SFR16(0xFF80, rRTCCON0);    // RTC Control Register 0
SFR16(0xFF81, rRTCCON1);    // RTC Control Register 1
SFR16(0xFF82, rBCDSEC);     // RTC BCD Second bits
SFR16(0xFF83, rBCDMIN);     // RTC BCD Minute bits
SFR16(0xFF84, rBCDHOUR);    // RTC BCD Hour bits
SFR16(0xFF85, rBCDDATE);    // RTC BCD Date bits
SFR16(0xFF86, rBCDDAY);     // RTC BCD Day of a Week bits
SFR16(0xFF87, rBCDMON);     // RTC BCD Month bits
SFR16(0xFF88, rBCDYEARL);   // RTC BCD Year lower bits
SFR16(0xFF89, rBCDYEARH);   // RTC BCD Year upper bits
SFR16(0xFF8A, rRTCALM);     // RTC ALARM control register
SFR16(0xFF8B, rALMSEC);     // RTC ALARM Second Data register. (BCD value
SFR16(0xFF8C, rALMMIN);     // RTC ALARM Minute Data register. (BCD value
SFR16(0xFF8D, rALMHOUR);    // RTC ALARM Hour Data register. (BCD value
SFR16(0xFF8E, rALMDATE);    // RTC ALARM Date Data register. (BCD value

// Flash Controller
SFR16(0xFFA0, rFCON_CTRL);
SFR16(0xFFA1, rFCON_STAT);
SFR16(0xFFA2, rFCON_ADDR_L);
SFR16(0xFFA3, rFCON_ADDR_M);
SFR16(0xFFA4, rFCON_ADDR_H);
SFR16(0xFFA5, rFCON_WDATA_L);
SFR16(0xFFA6, rFCON_WDATA_H_EN);
SFR16(0xFFA7, rFCON_CTRL2);
SFR16(0xFFA8, rFCON_WP_L);
SFR16(0xFFA9, rFCON_WP_H);

// I80LCD
SFR16(0xFFC0, rI80LCD_TP_W0);
SFR16(0xFFC1, rI80LCD_TP_W1);
SFR16(0xFFC2, rI80LCD_TP_W2);
SFR16(0xFFC3, rI80LCD_TP_W3);
SFR16(0xFFC4, rI80LCD_TP_W4);
SFR16(0xFFC5, rI80LCD_TP_W5);
SFR16(0xFFC6, rI80LCD_TP_W6);
SFR16(0xFFC7, rI80LCD_TP_R0);
SFR16(0xFFC8, rI80LCD_TP_R1);
SFR16(0xFFC9, rI80LCD_TP_R2);
SFR16(0xFFCA, rI80LCD_TP_R3);
SFR16(0xFFCB, rI80LCD_TP_R4);

SFR16(0xFFD0, rI80LCD_CFG_0);
SFR16(0xFFD1, rI80LCD_CFG_1);
SFR16(0xFFD2, rI80LCD_DATA_0);
SFR16(0xFFD3, rI80LCD_DATA_1);
SFR16(0xFFD4, rI80LCD_DATA_2);
SFR16(0xFFD5, rI80LCD_DATA_3);
SFR16(0xFFD6, rI80LCD_DATA_4);
SFR16(0xFFD7, rI80LCD_DATA_5);
SFR16(0xFFD8, rI80LCD_CMD);
SFR16(0xFFD9, rI80LCD_IE);
SFR16(0xFFDA, rI80LCD_ICLR);
SFR16(0xFFDB, rI80LCD_ST);
SFR16(0xFFDC, rI80LCD_RESERVED_4);
SFR16(0xFFDD, rI80LCD_RESERVED_5);
SFR16(0xFFDE, rI80LCD_RESERVED_6);
SFR16(0xFFDF, rI80LCD_RESERVED_7);

// VDMA
SFR16(0xFFE0, rVDMA_CFG_0); 
SFR16(0xFFE1, rVDMA_CFG_1); 
SFR16(0xFFE2, rVDMA_H_LEN);
SFR16(0xFFE3, rVDMA_V_LEN);
SFR16(0xFFE4, rVDMA_DST_H_WIDTH_L); 
SFR16(0xFFE5, rVDMA_DST_H_WIDTH_H); 
SFR16(0xFFE6, rVDMA_DST_ADDR_L);
SFR16(0xFFE7, rVDMA_DST_ADDR_H);
SFR16(0xFFE8, rVDMA_BG_H_WIDTH_L);
SFR16(0xFFE9, rVDMA_BG_H_WIDTH_H);
SFR16(0xFFEA, rVDMA_BG_ADDR_L); 
SFR16(0xFFEB, rVDMA_BG_ADDR_M); 
SFR16(0xFFEC, rVDMA_BG_ADDR_H); 
SFR16(0xFFED, rVDMA_RESERVED_0); 
SFR16(0xFFEE, rVDMA_RESERVED_1); 
SFR16(0xFFEF, rVDMA_RESERVED_2); 

SFR16(0xFFF0, rVDMA_FG_H_OFFSET);
SFR16(0xFFF1, rVDMA_FG_V_OFFSET);
SFR16(0xFFF2, rVDMA_FG_H_LEN); 
SFR16(0xFFF3, rVDMA_FG_V_LEN); 
SFR16(0xFFF4, rVDMA_FG_H_WIDTH_L);
SFR16(0xFFF5, rVDMA_FG_H_WIDTH_H);
SFR16(0xFFF6, rVDMA_FG_ADDR_L); 
SFR16(0xFFF7, rVDMA_FG_ADDR_M); 
SFR16(0xFFF8, rVDMA_FG_ADDR_H); 
SFR16(0xFFF9, rVDMA_CMD); 
SFR16(0xFFFA, rVDMA_IE);
SFR16(0xFFFB, rVDMA_ICLR);
SFR16(0xFFFC, rVDMA_ST);
SFR16(0xFFFD, rVDMA_R);
SFR16(0xFFFE, rVDMA_G);
SFR16(0xFFFF, rVDMA_B);


//============================================================================
//      Definitions for SFR Register
//============================================================================

// 0x91 rGIE			// INT Global Interrupt Enable
#define rGIE_GIE(x)	((x == 1) ? (rGIE |= (1 << 7)) : (x == 0) ? (rGIE &= ~(1 << 7)) : (rGIE & 0x80))
#define EnterCriticalSection    rGIE = 0x00
#define ExitCriticalSection     rGIE = 0x80
#define GlobalIntDisable        rGIE = 0x00
#define GlobalIntEnable         rGIE = 0x80

// 0x92 rIE0 					// INT Enable 0 Register
#define	IEWDT				0x01
#define	IEBRAC				0x02
#define	IEADC				0x04
#define	IEEXT0				0x08
#define	IEEXT1				0x10
#define	IESPI				0x20
#define	IET0				0x40
#define	IET1				0x80

// 0x93 rIP0 				// INT Priority 0 Register
#define	IPWDT				0x01
#define	IPBRAC				0x02
#define	IPADC				0x04
#define	IPEXT0				0x08
#define	IPEXT1				0x10
#define	IPSPI				0x20
#define	IPT0				0x40
#define	IPT1				0x80

// 0x94 rIE1 				// INT Interrupt Enable 1
#define IET2				0x01	// Enable Timer 2 interrupt
#define IEBRJPEG			0x02	// Enable JPEG interrupt
#define IEUTX				0x04	// Enable UART 0 Transmit interrupt
#define IEURX				0x08	// Enable UART 0 Receive interrupt
#define IEURXERR			0x10	// Enable UART 0 Receive interrupt
#define	IEVDMA  			0x20
#define	IEI80LCD  			0x40
#define	IEEXT2_3 			0x80

// 0x95 rIP1				// INT Interrupt Priority 1 register.
#define	IPT2				0x01
#define	IPBRJPEG			0x02
#define	IPUTX				0x04
#define	IPURX				0x08
#define	IPURXERR			0x10
#define	IPVDMA  			0x20
#define	IPI80LCD  			0x40
#define	IPEXT2_3 			0x80

// 0x96 rIE2 				// INT Enable 2 Register
#define	IEEXT4_5		    0x01
#define	IEEXT6				0x02
#define	IEEXT7				0x04
#define	IEEXT8				0x08
#define	IEEXT9				0x10
#define	IERTCPRI			0x20
#define	IERTCALM			0x40
#define	IEUSBRST			0x80

// 0x97 rIP2 				// INT Pending Priority 2 Register
#define	IPEXT4_5	    0x01
#define	IPEXT6				0x02
#define	IPEXT7				0x04
#define	IPEXT8				0x08
#define	IPEXT9				0x10
#define	IPRTCPRI			0x20
#define	IPRTCALM			0x40
#define	IPUSBRST			0x80

// 0x98 rIE3 				// INT Enable 2 Register
#define	IEUSBSOF			0x01
#define	IEUSBEP0			0x02
#define	IEUSBEP1			0x04
#define	IEUSBEP2			0x08
#define	IEUSBEP3			0x10
#define	IEUSBEP4			0x20

// 0x99 rIP3 				// INT Pending Priority 2 Register
#define	IPUSBSOF			0x01
#define	IPUSBEP0			0x02
#define	IPUSBEP1			0x04
#define	IPUSBEP2			0x08
#define	IPUSBEP3			0x10
#define	IPUSBEP4			0x20


// 0xA3 rCLKCON 		// Clock control 0
#define	CLKO_CLK12MPLL		0xE0
#define	CLKO_CLK12MSIE		0xC0
#define	CLKO_ESCLK		    0xA0
#define	CLKO_EMCLK		    0x80
#define	CLKO_RTCOSC		    0x60
#define	CLKO_ISCLK		    0x40
#define	CLKO_IMCLK		    0x20
#define	CLKO_FSYS		    0x00
#define	CLKDIV_1		    0x18
#define	CLKDIV_2		    0x10
#define	CLKDIV_4		    0x08
#define	CLKDIV_8		    0x00
#define	CLKSRC_PLLCLK		0x05
#define	CLKSRC_ESCLK		0x03
#define	CLKSRC_ISCLK		0x02
#define	CLKSRC_EMCLK		0x01
#define	CLKSRC_IMCLK		0x00

// 0xA4 rSMCLKCON0 		// Smart Clock control
#define	ONE_CACHE_EN		0x02
#define	FLASH_WAIT_CNT_0	0x00
#define	FLASH_WAIT_CNT_1	0x04
#define	FLASH_WAIT_CNT_2	0x08
#define	SMCLK_EN_BRAC		0x10
#define	SMCLK_EN_JPEG		0x20
#define	SMCLK_EN_I80LCD		0x40
#define	SMCLK_EN_VDMA		0x80


// 0xA5 rCLK_EN0 		// Peripheral Clock Enable Register 0
#define U0_CKEN 		    0x80	// 7 : UART
#define T2_CKEN			    0x40	// 6 : Timer 2
#define T1_CKEN			    0x20	// 5 : Timer 1
#define T0_CKEN			    0x10	// 4 : Timer 0
#define SPI_CKEN		    0x08	// 3 : SPI
#define ADC_CKEN		    0x04	// 2 : ADC
#define	RTC_CKEN		    0x02
#define WDT_CKEN		    0x01	// 0 : Watchdog timer
#define	CLK_EN0_ALL_EN		(rCLK_EN0  =  0xFF)
#define	CLK_EN0_ALL_DIS		(rCLK_EN0  =  0x00)


// 0xA6 rCLK_EN1 		// Peripheral Clock Enable Register 1
#define	LCD_CKEN		    0x80
#define	VDMA_CKEN		    0x40
#define	I80LCD_CKEN		    0x20
#define	JPEG_CKEN		    0x10
#define	FLASH_CKEN		    0x08
#define BRAC_CKEN		    0x04	// 1 : BRAC, DCO
#define	U11_CKEN		    0x01
#define	CLK_EN1_ALL_EN		(rCLK_EN1 =  0xFF)
#define	CLK_EN1_ALL_DIS		(rCLK_EN1 =  0x00)


// 0xA7 rPCON 			// Power Control Register
#define	PCON_USBPHYPUPEN		0x80
#define	PCON_EF_WAIT_MODE	    0x40
#define	PCON_LDO33_PD	        0x20
#define	PCON_STOP		        0x02
#define	PCON_IDLE		        0x01

// 0xA8 rRSTCON 		// Reset Control Register
#define	RSTCON_RTCRST		0x10
#define	RSTCON_SWRST		0x0B


// 0xA9 rRSTSTAT 		// Reset Status Register
#define	PORST		        0x10
#define	LVDRST		        0x08
#define	WDTRST		        0x04
#define	SWRST		        0x02
#define	PINRST		        0x01

// 0xAA, rSYSCFG		// System configuration register
#define	INT_MOSC_STABLE		0x80
#define	MAIN_OSC_STABLE		0x40
#define	INT_MOSCEN_STOP		0x20
#define	MAIN_OSCEN_STOP		0x10
#define	INT_32K_OSC_DIS		0x08
#define	INT_MOSC_DIS		    0x04
#define	SUB_OSC_DIS		    0x02
#define	MAIN_OSC_DIS		    0x01


// 0xAB, rIVCON0		//
#define	LVR_EN_DIS		    0x00
#define	LVR_EN_EN		    0x01
#define	LVR_SEL_2_051V	    0x00
#define	LVR_SEL_2_000V	    0x06
#define	LVR_SEL_1_951V	    0x04
#define	LVR_SEL_1_905V	    0x02
#define	BLD_EN_DIS		    0x00
#define	BLD_EN_EN		    0x20
#define	BLD_SEL_4_45V	    0x00
#define	BLD_SEL_4_00V	    0xC0
#define	BLD_SEL_3_33V	    0x80
#define	BLD_SEL_2_67V	    0x40

// 0xAC, rIVCON1		//
#define	TRIM_EN			    0x00
#define	NM_PD_EN		    0x02
#define	NS_PD_EN		    0x04
#define	IM_PD_EN		    0x08
#define	IS_PD_EN		    0x10

// 0xAD, rWKUPSTAT		//
#define	WDT_WKUP			    0x10
#define	RTC_WKUP			    0x20
#define	EINT_WKUP		    0x40
#define	USB_WKUP			    0x80

// 0xAE rPLLCON0 				// PLL Control Register
#define PLL_STABLE			0x80	// [READ]  0: PLL unstable, 1: PLL stable
#define	PLL_EN_DIS			0x00
#define	PLL_EN_EN			0x10


//0xB2 rUSBPM			// USB Power Management register
#define USBSUSE				0x01
#define USBSUSM				0x02
#define USBRESUM			0x04
#define USBRST				0x08


//0xB3 rUSBIPEND		// USB Interrupt Pending register
#define USBEP0PEND			0x01
#define USBEP1PEND			0x02
#define USBEP2PEND			0x04
#define USBEP3PEND			0x08
#define USBEP4PEND			0x10
#define USBSUSPEND			0x20
#define USBRESPEND			0x40
#define USBRSTPEND			0x80

//0xB4 rUSBINTEN		// USB Interrupt Enable register
#define USBEP0INTEN			0x01
#define USBEP1INTEN			0x02
#define USBEP2INTEN			0x04
#define USBEP3INTEN			0x08
#define USBEP4INTEN			0x10
#define USBSUSINTEN			0x20
#define USBRSTINTEN			0x80
#define USBINTEN_ALL		0xFF

//0xB7 rUSBEP0CSR0		// USB EP 0 Common Status Register 0
//0xBA rUSBEP1CSR0		// USB EP 1 Common Status Register 0
//0xBE rUSBEP2CSR0		// USB EP 2 Common Status Register 0
//0xC3 rUSBEP3CSR0		// USB EP 3 Common Status Register 0
//0xC7 rUSBEP4CSR0		// USB EP 4 Common Status Register 0
#define	MAXPSIZE_8			0x81
#define	MAXPSIZE_16			0x82
#define	MAXPSIZE_32			0x84
#define	MAXPSIZE_64			0x88

//0xB8 rUSBEP0CSR1		// USB EP 0 Common Status Register 1
#define	EP0_ORDY			0x01
#define	EP0_INRDY			0x02
#define	EP0_STSTALL			0x04
#define	EP0_DEND			0x08
#define	EP0_SETEND			0x10
#define	EP0_SDSTALL			0x20
#define	EP0_ORDY_CLR		0x40
#define	EP0_SETEND_CLR		0x80

//0xBB rUSBEP1CSR1		// USB EP 1 Common Status Register 1
//0xBF rUSBEP2CSR1		// USB EP 2 Common Status Register 1
//0xC4 rUSBEP3CSR1		// USB EP 3 Common Status Register 1
//0xC8 rUSBEP4CSR1		// USB EP 4 Common Status Register 1
#define	EP_OISO				0x01
#define	EP_OBULK			0x00
#define	EP_OATCLR			0x02
#define	EP_MODE_IN			0x04
#define	EP_MODE_OUT			0x00
#define	EP_IISO				0x08
#define	EP_IBULK			0x00
#define	EP_IATCLR			0x10

//0xBC rUSBEP1CSR2		// USB EP 1 Common Status Register 2
//0xC1 rUSBEP2CSR2		// USB EP 2 Common Status Register 2
//0xC5 rUSBEP3CSR2		// USB EP 3 Common Status Register 2
//0xC9 rUSBEP4CSR2		// USB EP 4 Common Status Register 2
#define	EP_OORDY			0x01
#define	EP_OFFULL			0x02
#define	EP_OOVER			0x04
#define	EP_ODERR			0x08
#define	EP_OFFLUSH			0x10
#define	EP_OSDSTALL			0x20
#define	EP_OSTSTALL			0x40
#define	EP_OCTLOG			0x80

//0xBD rUSBEP1CSR3		// USB EP 1 Common Status Register 2
//0xC2 rUSBEP2CSR3		// USB EP 2 Common Status Register 3
//0xC6 rUSBEP3CSR3		// USB EP 3 Common Status Register 3
//0xCA rUSBEP4CSR3		// USB EP 4 Common Status Register 3
#define	EP_IINRDY			0x01
#define	EP_INEMP			0x02
#define	EP_IUNDER			0x04
#define	EP_IFFLUSH			0x08
#define	EP_ISDSTALL			0x10
#define	EP_ISTSTALL			0x20
#define	EP_ICLTOG			0x40

// 0xD0 rPSW 			// PSW (Program Status Word)
#define PSW_P				0x01	// Parity Flag
#define PSW_F1				0x02	// Flag1 available to the user for general purpose.
#define PSW_OV				0x04	// Overflow Flag
#define PSW_RS0				0x00	// 00: Register Bank 0 (0x00 ~ 0x07)
#define PSW_RS1				0x08	// 01: Register Bank 1 (0x08 ~ 0x0F)
#define PSW_RS2				0x10	// 10: Register Bank 2 (0x10 ~ 0x17)
#define PSW_RS3				0x18	// 11: Register Bank 3 (0x18 ~ 0x1F)
#define PSW_F0				0x20	// Flag0 available to the user for general purpose.
#define PSW_AC				0x40	// Auxiliary Carry Flag
#define PSW_CY				0x80	// Carry Flag

// 0xDF rUSBCONF			// USB Configuration Register
#define	DMVALUE_L			0x00
#define	DMVALUE_H			0x01
#define	DPVALUE_L			0x00
#define	DPVALUE_H			0x02
#define	DP_DM_DIR_SW		0x04
#define	CLK_48M_EN			0x08
#define	SET_SUSP				0x10
#define	WAKE_EN				0x20
#define	SEND_NAK				0x40
#define	INTSOF_SEL_CRC		0x80

// 0xE1 rADCON0					// ADC Control Register 0
#define	ADCEN			    0x01	// Enable ADC operation
#define	ADINTEN			    0x02	// Enable ADC interrupt
#define	ADMOD_NORMAL		0x00	// Normal mode.
#define	ADMOD_INF		    0x04	// Infinite mode.
#define	ADMOD_COMP		    0x08	// Compare mode.
#define	ADMOD_REC		    0x0C	// Recording mode
#define	EXTAVREF			0x10	// Using External AVREF
#define	INT_PEND			0x20	// ADC Interrupt pending register
#define	RECORD_CON          0x40    // Manual Recording Mode
#define	STC				    0x80	// AD conversion start bit

// 0xE2 rADCON1					// ADC Control Register 1
#define	ADINSEL_ADIN0	    0x00	// ADIN0
#define	ADINSEL_ADIN1	    0x01	// ADIN1
#define	ADINSEL_ADIN2	    0x02	// ADIN2
#define	ADINSEL_ADIN3	    0x03	// ADIN3 
#define	ADINSEL_ADIN4	    0x04	// ADIN4 
#define	ADINSEL_ADIN5	    0x05	// ADIN5 
#define	ADCKSEL_000		    0x00	// Reserved (should not be set to this value)
#define	ADCKSEL_001		    0x10	// Fcnt/8
#define	ADCKSEL_010		    0x20	// Fcnt/16
#define	ADCKSEL_011		    0x30	// Fcnt/32
#define	ADCKSEL_100		    0x40	// Fcnt/64
#define	ADCKSEL_101		    0x50	// Fcnt/128
#define	ADCKSEL_110		    0x60	// Fcnt/256
#define	ADCKSEL_111		    0x70	// Fcnt/512

// 0xE3 rADAT0					// AD Conversion LOWER Result Register
#define EOC				    0x01	// AD Conversion Completion Indication
#define ADRDY				0x02	// AD Conversion Ready indication

// 0xEC rWDTCON				 // WDT Control Register
#define	WDTEN				    0x01
#define	WDT_SEL_INT_D_RST_D	0x00
#define	WDT_SEL_INT_D_RST_E	0x02
#define	WDT_SEL_INT_E_RST_D	0x04
#define	WDT_SEL_INT_E_RST_E	0x06
#define	WDTCLK_FSYS			0x00
#define	WDTCLK_ESCLK		0x08
#define	WDTWAKEEN			0x10
#define	WCNTCLR				0x20
#define	WINTPEND			0x40
#define	WDT_DISABLE			(rWDTCON &= ~WDTEN)
#define	WDT_ENABLE			(rWDTCON |= WDTEN)

// 0xED rWCNTCLK			//WDT counter clock select


// 0xF1 rUCON0				// UART Control Register 0
#define TMODE_EN			0x01
#define RMODE_EN			0x02
#define SBR				    0x04
#define	ECHO				0x08
#define LOOPB				0x10
#define PMD_NO_PARITY		0x00
#define PMD_ODD_PARITY		0x80
#define PMD_EVEN_PARITY		0xA0
#define PMD_FORCE1_PARITY	0xC0
#define PMD_FORCE0_PARITY	0xE0

// 0xF2 rUCON1				// UART Control Register 1
#define	STB				    0x01
#define	WL_5				0x00
#define	WL_6				0x02
#define	WL_7				0x04
#define	WL_8				0x06
#define	IRMODE				0x08
#define	UBAUDCLK_DIV0		0x00
#define	UBAUDCLK_EXT		0x10
#define	UBAUDCLK_DIV2		0x20
#define	UBAUDCLK_DIV4		0x30
#define	UBAUDCLK_DIV8		0x40
#define	UBAUDCLK_DIV16		0x50

// 0xF3 rUTRSTAT			// UART TX/RX Status Register
#define	RXIDLE				0x01
#define	RDV				    0x02
#define	RXTO				0x04
#define	TXIDLE				0x08
#define	THE				    0x10

// 0xF4 rUERSTAT			// UART RX Error Status Register
#define	BKD				    0x01
#define	FER				    0x02
#define	PER				    0x04
#define	OER				    0x08

// 0xF5 rUINTCON			// UART Interrupt Register
#define	RDVIE				0x01	// Receive Data Valid interrupt enable
#define	RXERRIE				0x04	// Receive Error interrupt enable
#define	THEIE				0x08	// Transmit holding register empty interrupt enable
#define	TIIE				0x10	// Transmit IDLE interrupt enable
#define	UTXINTPEND			0x20	// TX interrrupt pending bit
#define	URXINTPEND			0x40	// RX interrrupt pending bit
#define	URXERRINTPEND		0x80	// RX Error interrrupt pending bit
#define	UART_INT_ALL		0x1D

// 0xF9 rUFCON				// UART FIFO Control Register
#define	TXFIFOEN			0x01	// TX FIFO enable
#define	TXFIFORST			0x02	// TX FIFO reset
#define	TXFIFOTRIG4			0x04	// TX FIFO Triger Level 4
#define	TXFIFOTRIG8			0x08	// TX FIFO Triger Level 8
#define	TXFIFOTRIG12		0x0C	// TX FIFO Triger Level 12
#define	RXFIFOEN			0x10	// RX FIFO enable
#define	RXFIFORST			0x20	// RX FIFO reset
#define	RXFIFOTRIG1			0x00	// RX FIFO Triger Level 1
#define	RXFIFOTRIG4			0x40	// RX FIFO Triger Level 4
#define	RXFIFOTRIG8			0x80	// RX FIFO Triger Level 8
#define	RXFIFOTRIG12		0xC0	// RX FIFO Triger Level 12

// 0xFA rUFTSTAT
#define TXFIFOFULL			0x20
#define RXFIFOFULL			0x20

// 0xFC rSPIMOD				// SPI Mode Register
#define	SPI_INTPEND			0x80
#define	SPI_SSMD			0x40
#define	SPI_SCKPHA_SECOND	0x20
#define	SPI_SCKPHA_FIRST	0x00
#define	SPI_SCKPOL_HI		0x10
#define	SPI_SCKPOL_LOW		0x00
#define	SPI_MATEN			0x00
#define	SPI_SLVEN			0x08
#define	SPI_DIR_LSB			0x04
#define	SPI_DIR_MSB			0x00
#define	SPI_MODE_RXTX		0x02
#define	SPI_MODE_RX			0x00
#define	SPI_EN				0x01


// 0xFD rSPICK				// SPI Baud Rate counter clock select Register
#define	SPI_BUSY			0x80
#define	SPI_IDLE			0x00
#define	SPI_1BYTE			0x00
#define	SPI_2BYTE			0x40
#define	SPI_CKSEL_0000		0x00
#define	SPI_CKSEL_0001		0x01
#define	SPI_CKSEL_0010		0x02
#define	SPI_CKSEL_0011		0x03
#define	SPI_CKSEL_0100		0x04
#define	SPI_CKSEL_0101		0x05
#define	SPI_CKSEL_0110		0x06
#define	SPI_CKSEL_0111		0x07
#define	SPI_CKSEL_1000		0x08
#define	SPI_CKSEL_1001		0x09
#define	SPI_CKSEL_1010		0x0A
#define	SPI_CKSEL_1011		0x0B
#define	SPI_CKSEL_1100		0x0C




//============================================================================
//      Definitions for Extended SFR Registers (SFR16)
//============================================================================

// -----------------------------------------------------------------------
// TIMER 
// -----------------------------------------------------------------------
// 0xFE00 rT0CON 		// TIMER 0 Control Register
// 0xFE07 rT1CON 		// TIMER 1 Control Register
// 0xFE10 rT2CON 		// TIMER 2 Control Register
#define	TRUN				0x01	// Timer x running
#define	TINTPEND			0x02	// Timer x Interrupt Pending.
#define	SEL_INTERVAL		0x00	// Interval Mode
#define	SEL_TOGGLE			0x04	// Toggle Mode
#define	SEL_PWM				0x08	// PWM Mode
#define	SEL_CAPTURE_RISE	0x0C	// Capture Mode (rising edge of TxCAP pin input)
#define	SEL_TCLK4			0x00
#define	SEL_TCLK8			0x10
#define	SEL_TCLK16			0x20
#define	SEL_TCLK32			0x30
#define	SEL_TCLK64			0x40
#define	SEL_TCLK128			0x50
#define	SEL_TCLK256			0x60
#define	SEL_TCLK512			0x70
#define	SEL_TCLK1024		0x80
#define	SEL_TCLK2048		0x90
#define	SEL_TCLK4096		0xA0
#define	SEL_ETCLK			0xB0


// -----------------------------------------------------------------------
// GPIO mode 
// -----------------------------------------------------------------------
// 0xFE40 rJTAGOFF 		// JTAG port control Register
#define JTAGOFF			    0x01

// 0xFE41 rEINTMOD0 		// External Interrupt Control Register 0
#define EINT0_RISE_EDGE		0x01	//
#define EINT0_FALL_EDGE		0x02	//
#define EINT0_BOTH_EDGE		0x03	//
#define EINT0_FILTER_DIS	0x00	//
#define EINT0_FILTER_EN		0x04	//
#define EINT1_RISE_EDGE		0x10	//
#define EINT1_FALL_EDGE		0x20	//
#define EINT1_BOTH_EDGE		0x30	//
#define EINT1_FILTER_DIS	0x00	//
#define EINT1_FILTER_EN		0x40	//

// 0xFE42 rEINTMOD1 		// External Interrupt Control Register 1
#define EINT2_3_RISE_EDGE	0x01	//
#define EINT2_3_FALL_EDGE	0x02	//
#define EINT2_3_BOTH_EDGE	0x03	//
#define EINT2_3_FILTER_DIS	0x00	//
#define EINT2_3_FILTER_EN	0x04	//
#define EINT4_5_RISE_EDGE	0x10	//
#define EINT4_5_FALL_EDGE	0x20	//
#define EINT4_5_BOTH_EDGE	0x30	//
#define EINT4_5_FILTER_DIS	0x00	//
#define EINT4_5_FILTER_EN	0x40	//

// 0xFE43 rEINTMOD2 		// External Interrupt Control Register 2
#define EINT6_RISE_EDGE		0x01	//
#define EINT6_FALL_EDGE		0x02	//
#define EINT6_BOTH_EDGE		0x03	//
#define EINT6_FILTER_DIS	0x00	//
#define EINT6_FILTER_EN		0x04	//
#define EINT7_RISE_EDGE		0x10	//
#define EINT7_FALL_EDGE		0x20	//
#define EINT7_BOTH_EDGE		0x30	//
#define EINT7_FILTER_DIS	0x00	//
#define EINT7_FILTER_EN		0x40	//


// 0xFE44 rEINTMOD3 		// External Interrupt Control Register 3
#define EINT8_RISE_EDGE		0x01	//
#define EINT8_FALL_EDGE		0x02	//
#define EINT8_BOTH_EDGE		0x03	//
#define EINT8_FILTER_DIS	0x00	//
#define EINT8_FILTER_EN		0x04	//
#define EINT9_RISE_EDGE		0x10	//
#define EINT9_FALL_EDGE		0x20	//
#define EINT9_BOTH_EDGE		0x30	//
#define EINT9_FILTER_DIS	0x00	//
#define EINT9_FILTER_EN		0x40	//


// 0xFE45 rEINTEN0		// External Interrupt Control Register 0
#define EINT0EN			    0x01	// Enable external Interrupt 0
#define EINT1EN			    0x02	// Enable external Interrupt 1
#define	EINT2EN			    0x04	// Enable external Interrupt 2
#define	EINT3EN			    0x08	// Enable external Interrupt 3  //Only for I1BG 
#define	EINT4EN			    0x10	// Enable external Interrupt 4  //Only for I1BG 
#define	EINT5EN			    0x20	// Enable external Interrupt 5
#define	EINT6EN			    0x40	// Enable external Interrupt 6
#define	EINT7EN			    0x80	// Enable external Interrupt 7

// 0xFE46 rEINTEN1		// External Interrupt Control Register 1
#define EINT8EN			    0x01	// Enable external Interrupt 8
#define EINT9EN			    0x02	// Enable external Interrupt 9

// 0xFE47 rEINTPND0		// External Interrupt Pendign Register 0
#define EINT0PND		    0x01	// external Interrupt 0 pending
#define EINT1PND		    0x02	// external Interrupt 1 pending
#define	EINT2PND		    0x04	// external Interrupt 2 pending
#define	EINT3PND		    0x08	// external Interrupt 3 pending  //Only for I1BG 
#define	EINT4PND		    0x10	// external Interrupt 4 pending  //Only for I1BG 
#define	EINT5PND		    0x20	// external Interrupt 5 pending
#define	EINT6PND		    0x40	// external Interrupt 6 pending
#define	EINT7PND		    0x80	// external Interrupt 7 pending

// 0xFE48 rEINTPND1		// External Interrupt Pending Register 1
#define EINT8PND		    0x01	// external Interrupt 8 pending
#define EINT9PND		    0x02	// external Interrupt 9 pending


#define	GPMOD_ALL_DI	    0x00
#define	GPMOD_ALL_DO	    0x55

// 0xFE49 rP0MOD0 		// P00 ~ P03 mode control Register
#define GP00_DI			    0x00	// Data Input Mode
#define GP01_DI			    0x00
#define GP02_DI			    0x00
#define GP03_DI			    0x00
#define GP00_DO			    0x01	// Data Output Mode
#define GP01_DO			    0x04
#define GP02_DO			    0x10
#define GP03_DO			    0x40
#define GP00_SEG12		    0x02
#define GP01_SEG13		    0x08
#define GP02_SEG14		    0x20
#define GP03_SEG15		    0x80
#define GP00_I80		    0x03
#define GP01_I80		    0x0C
#define GP02_I80		    0x30
#define GP03_I80		    0xC0


// 0xFE4A rP0MOD1 		// P04 ~ P07 mode control Register
#define GP04_DI			    0x00	// Data Input Mode
#define GP05_DI			    0x00
#define GP06_DI			    0x00
#define GP07_DI			    0x00
#define GP04_DO			    0x01
#define GP05_DO			    0x04
#define GP06_DO			    0x10
#define GP07_DO			    0x40
#define GP04_SEG16		    0x02
#define GP05_SEG17		    0x08
#define GP06_SEG18		    0x20
#define GP07_SEG19		    0x80
#define GP04_TCLK		    0x03
#define GP05_T0OUT_CAP		0x0C
#define GP06_T1OUT_CAP		0x30
#define GP07_T2OUT_CAP		0xC0


// 0xFE4B rP0PU 		// P00 ~ P07 Pullup control Register
#define GP00_PUEN		    0x01
#define GP01_PUEN		    0x02
#define GP02_PUEN		    0x04
#define GP03_PUEN		    0x08
#define GP04_PUEN		    0x10
#define GP05_PUEN		    0x20
#define GP06_PUEN		    0x40
#define GP07_PUEN		    0x80
#define GP0_ALL_PUEN		0xFF
#define GP0_ALL_PUDIS		0x00

// 0xFE4C rP1MOD0 		// P10 ~ P13 mode control Register
#define	GP10_DI			    0x00	// Data Input Mode
#define	GP11_DI			    0x00	
#define	GP12_DI			    0x00	
#define	GP13_DI			    0x00	
#define	GP10_DO			    0x01	// Data Output Mode
#define	GP11_DO			    0x04	
#define	GP12_DO			    0x10	
#define	GP13_DO			    0x40	
#define	GP10_AIN3		    0x02
#define	GP11_AIN2		    0x08	
#define	GP12_AIN1		    0x20	
#define	GP13_AIN0		    0x80	
#define	GP10_T2OUT_CAP		0x03
#define	GP11_T1OUT_CAP		0x0C	
#define	GP12_T0OUT_CAP		0x30	
#define	GP13_TCLK		    0xC0	

// 0xFE4D rP1MOD1 		// P14 ~ P16 mode control Register
#define	GP14_DI			    0x00	// Data Input Mode
#define	GP15_DI			    0x00
#define	GP16_DI			    0x00
#define	GP14_DO			    0x01
#define	GP15_DO			    0x04
#define	GP16_DO			    0x10
#define	GP14_CLKOUT		    0x02
#define	GP14_EINT5		    0x03
#define	GP15_URXD		    0x0C
#define	GP16_UTXD		    0x30


// 0xFE4E rP1PUD0 		// P10 ~ P13 Pullup/down control Register
#define GP10_PUD_DIS		0x00
#define GP11_PUD_DIS		0x00
#define GP12_PUD_DIS		0x00
#define GP13_PUD_DIS		0x00
#define GP10_PDEN		    0x01
#define GP11_PDEN		    0x04
#define GP12_PDEN		    0x10
#define GP13_PDEN		    0x40
#define GP10_PUEN		    0x02
#define GP11_PUEN		    0x08
#define GP12_PUEN		    0x20
#define GP13_PUEN		    0x80
#define GP1_LOW_ALL_PDEN	0x55
#define GP1_LOW_ALL_PUEN	0xAA
#define GP1_LOW_ALL_PUD_DIS	0x00

// 0xFE4F rP1PUD1 		// P14 ~ P16 Pullup/down control Register
#define GP14_PUD_DIS		0x00
#define GP15_PUD_DIS		0x00
#define GP16_PUD_DIS		0x00
#define GP17_PUD_DIS		0x00
#define GP14_PDEN		    0x01
#define GP15_PDEN		    0x04
#define GP16_PDEN		    0x10
#define GP14_PUEN		    0x02
#define GP15_PUEN		    0x08
#define GP16_PUEN		    0x20
#define GP17_PUEN		    0x80
#define GP1_HIGH_ALL_PDEN	0x55
#define GP1_HIGH_ALL_PUEN	0xAA
#define GP1_HIGH_ALL_PUD_DIS    0x00

// 0xFE50 rP3MOD0 		// P30 ~ P33 mode control Register
#define	GP30_DI			    0x00	// Data Input Mode
#define	GP31_DI			    0x00	
#define	GP32_DI			    0x00	
#define	GP33_DI			    0x00	
#define	GP30_DO			    0x01	// Data Output Mode
#define	GP31_DO			    0x04	
#define	GP32_DO			    0x10	
#define	GP33_DO			    0x40	

// 0xFE51 rP3MOD1 		// P34 ~ P37 mode control Register
#define	GP34_DI			    0x00	// Data Input Mode
#define	GP35_DI			    0x00
#define	GP36_DI			    0x00
#define	GP37_DI			    0x00
#define	GP34_DO			    0x01
#define	GP35_DO			    0x04
#define	GP36_DO			    0x10
#define	GP37_DO			    0x40
#define	GP34_BSCLK			0x02
#define	GP35_BMISO			0x08
#define	GP36_BMOSI			0x20
#define	GP37_BSCSN			0x80
#define	GP34_EINT6		    0x03
#define GP35_EINT7		    0x0C
#define GP36_EINT8		    0x30
#define GP37_EINT9		    0xC0

// 0xFE52 rP3PUD0 		// P30 ~ P33 Pullup/down control Register
#define GP30_PUD_DIS		0x00
#define GP31_PUD_DIS		0x00
#define GP32_PUD_DIS		0x00
#define GP33_PUD_DIS		0x00
#define GP30_PDEN		    0x01
#define GP31_PDEN		    0x04
#define GP32_PDEN		    0x10
#define GP33_PDEN		    0x40
#define GP30_PUEN		    0x02
#define GP31_PUEN		    0x08
#define GP32_PUEN		    0x20
#define GP33_PUEN		    0x80
#define GP3_LOW_ALL_PDEN	0x55
#define GP3_LOW_ALL_PUEN	0xAA
#define GP3_LOW_ALL_PUD_DIS	0x00

// 0xFE53 rP3PUD1 		// P34 ~ P37 Pullup/down control Register
#define GP34_PUD_DIS		0x00
#define GP35_PUD_DIS		0x00
#define GP36_PUD_DIS		0x00
#define GP37_PUD_DIS		0x00
#define GP34_PDEN		    0x01
#define GP35_PDEN		    0x04
#define GP36_PDEN		    0x10
#define GP37_PDEN		    0x40
#define GP34_PUEN		    0x02
#define GP35_PUEN		    0x08
#define GP36_PUEN		    0x20
#define GP37_PUEN		    0x80
#define GP3_HIGH_ALL_PDEN	0x55
#define GP3_HIGH_ALL_PUEN	0xAA
#define GP3_HIGH_ALL_PUD_DIS	0x00

// 0xFE54 rP4MOD0 		// P40 ~ P43 mode control Register
#define	GP40_DI			    0x00	// Data Input Mode
#define	GP41_DI			    0x00	
#define	GP42_DI			    0x00	
#define	GP43_DI			    0x00	
#define	GP40_DO			    0x01	// Data Output Mode
#define	GP41_DO			    0x04	
#define	GP42_DO			    0x10	
#define	GP43_DO			    0x40	
#define GP40_SEG		    0x02
#define GP41_SEG		    0x08
#define GP42_SEG		    0x20
#define GP43_SEG		    0x80
#define GP40_I80		    0x03
#define GP41_I80		    0x0C
#define GP42_I80		    0x30
#define GP43_I80		    0xC0

// 0xFE55 rP4MOD1 		// P44 ~ P47 mode control Register
#define	GP44_DI			    0x00	// Data Input Mode
#define	GP45_DI			    0x00	
#define	GP46_DI			    0x00	
#define	GP47_DI			    0x00	
#define	GP44_DO			    0x01	// Data Output Mode
#define	GP45_DO			    0x04	
#define	GP46_DO			    0x10	
#define	GP47_DO			    0x40	
#define GP44_SEG		    0x02
#define GP45_SEG		    0x08
#define GP46_SEG		    0x20
#define GP47_SEG		    0x80
#define GP44_I80		    0x03
#define GP45_I80		    0x0C
#define GP46_I80		    0x30
#define GP47_I80		    0xC0

// 0xFE56 rP4PU 		// P40 ~ P47 Pullup control Register
#define GP40_PUEN		    0x01
#define GP41_PUEN		    0x02
#define GP42_PUEN		    0x04
#define GP43_PUEN		    0x08
#define GP44_PUEN		    0x10
#define GP45_PUEN		    0x20
#define GP46_PUEN		    0x40
#define GP47_PUEN		    0x80
#define GP4_ALL_PUEN		0xFF
#define GP4_ALL_PUDIS		0x00

// 0xFE57 rP5MOD0 		// P50 ~ P53 mode control Register
#define	GP50_DI			    0x00	// Data Input Mode
#define	GP51_DI			    0x00	
#define	GP52_DI			    0x00	
#define	GP53_DI			    0x00	
#define	GP50_DO			    0x01	// Data Output Mode
#define	GP51_DO			    0x04	
#define	GP52_DO			    0x10	
#define	GP53_DO			    0x40	
#define GP50_SEG		    0x02
#define GP51_SEG		    0x08
#define GP52_SEG		    0x20
#define GP53_SEG		    0x80
#define GP50_I80		    0x03
#define GP51_I80		    0x0C
#define GP52_I80		    0x30
#define GP53_I80		    0xC0

// 0xFE58 rP5MOD1 		// P54 ~ P57 mode control Register
#define	GP54_DI			    0x00	// Data Input Mode
#define	GP55_DI			    0x00	
#define	GP56_DI			    0x00	
#define	GP57_DI			    0x00	
#define	GP54_DO			    0x01	// Data Output Mode
#define	GP55_DO			    0x04	
#define	GP56_DO			    0x10	
#define	GP57_DO			    0x40	
#define GP54_SEG		    0x02
#define GP55_SEG		    0x08
#define GP56_SEG		    0x20
#define GP57_SEG		    0x80
#define GP54_SPI_CLK		0x03
#define GP55_SPI_MISO		0x0C
#define GP56_SPI_MOSI		0x30
#define GP57_SPI_CSN		0xC0

// 0xFE59 rP5PU 		// P50 ~ P57 Pullup control Register
#define GP50_PUEN		    0x01
#define GP51_PUEN		    0x02
#define GP52_PUEN		    0x04
#define GP53_PUEN		    0x08
#define GP54_PUEN		    0x10
#define GP55_PUEN		    0x20
#define GP56_PUEN		    0x40
#define GP57_PUEN		    0x80
#define GP5_ALL_PUEN		0xFF
#define GP5_ALL_PUDIS		0x00


// 0xFE5A rP6MOD0 		// P60 ~ P63 mode control Register
#define	GP60_DI			    0x00	// Data Input Mode
#define	GP61_DI			    0x00	
#define	GP62_DI			    0x00	
#define	GP63_DI			    0x00	
#define	GP60_DO			    0x01	// Data Output Mode
#define	GP61_DO			    0x04	
#define	GP62_DO			    0x10	
#define	GP63_DO			    0x40	
#define GP60_VLC		    0x02
#define	GP60_nRSTOUT		0x03
#define GP61_VLC		    0x08
#define GP62_VLC		    0x20
#define GP63_VLC		    0x80
#define GP62_I80		    0x30
#define GP63_I80		    0xC0

// 0xFE5B rP6MOD1 		// P64 ~ P67 mode control Register
#define	GP64_DI			    0x00	// Data Input Mode
#define	GP65_DI			    0x00	
#define	GP66_DI			    0x00	
#define	GP67_DI			    0x00	
#define	GP64_DO			    0x01	// Data Output Mode
#define	GP65_DO			    0x04	
#define	GP66_DO			    0x10	
#define	GP67_DO			    0x40	
#define GP64_COM		    0x02
#define GP65_COM		    0x08
#define GP66_COM		    0x20
#define GP67_COM		    0x80
#define GP64_I80		    0x03
#define GP65_I80		    0x0C
#define GP66_I80		    0x30
#define GP67_I80		    0xC0

// 0xFE5C rP6PU 		// P60 ~ P67 Pullup control Register
#define GP60_PUEN		    0x01
#define GP61_PUEN		    0x02
#define GP62_PUEN		    0x04
#define GP63_PUEN		    0x08
#define GP64_PUEN		    0x10
#define GP65_PUEN		    0x20
#define GP66_PUEN		    0x40
#define GP67_PUEN		    0x80
#define GP6_ALL_PUEN		0xFF
#define GP6_ALL_PUDIS		0x00

// 0xFE5D rP7MOD0 		// P70 ~ P73 mode control Register
#define	GP70_DI			    0x00	// Data Input Mode
#define	GP71_DI			    0x00	
#define	GP72_DI			    0x00	
#define	GP73_DI			    0x00	
#define	GP70_DO			    0x01	// Data Output Mode
#define	GP71_DO			    0x04	
#define	GP72_DO			    0x10	
#define	GP73_DO			    0x40	
#define GP70_SEG		    0x02
#define GP71_SEG		    0x08
#define GP72_SEG		    0x20
#define GP73_SEG		    0x80
#define	GP70_EINT0		    0x03	// External Interrupt 0 input mode
#define	GP71_EINT1		    0x0C	// External Interrupt 1 input mode
#define	GP72_EINT2		    0x30	// External Interrupt 2 input mode
#define GP73_UCLK		    0xC0


// 0xFE5E rP7MOD1 		// P74 ~ P77 mode control Register
#define	GP74_DI			    0x00	// Data Input Mode
#define	GP75_DI			    0x00	
#define	GP76_DI			    0x00	
#define	GP77_DI			    0x00	
#define	GP74_DO			    0x01	// Data Output Mode
#define	GP75_DO			    0x04	
#define	GP76_DO			    0x10	
#define	GP77_DO			    0x40	
#define GP74_SEG		    0x02
#define GP75_SEG		    0x08
#define GP74_URXD		    0x03
#define GP75_UTXD		    0x0C
#define GP76_SEG		    0x20
#define GP77_SEG		    0x80

// 0xFE5F rP7PU 		// P70 ~ P77 Pullup control Register
#define GP70_PUEN		    0x01
#define GP71_PUEN		    0x02
#define GP72_PUEN		    0x04
#define GP73_PUEN		    0x08
#define GP74_PUEN		    0x10
#define GP75_PUEN		    0x20
#define GP76_PUEN		    0x40
#define GP77_PUEN		    0x80
#define GP7_ALL_PUEN		0xFF
#define GP7_ALL_PUDIS		0x00

// 0xFE60 rP8MOD0 		// P82 ~ P83 mode control Register
#define	GP82_DI			    0x00	
#define	GP83_DI			    0x00	
#define	GP82_DO			    0x10	
#define	GP83_DO			    0x40	
#define GP82_AIN5		    0x20
#define GP83_AIN4		    0x80
#define	GP82_EINT3		    0x30	// External Interrupt 5 input mode
#define	GP83_EINT4		    0xC0	// External Interrupt 6 input mode

// 0xFE61 rP8MOD1 		// P84 ~ P87 mode control Register
#define	GP84_DI			    0x00	// Data Input Mode
#define	GP85_DI			    0x00	
#define	GP86_DI			    0x00	
#define	GP87_DI			    0x00	
#define	GP84_DO			    0x01	// Data Output Mode
#define	GP85_DO			    0x04	
#define	GP86_DO			    0x10	
#define	GP87_DO			    0x40	
#define GP84_SPI_CLK		0x03
#define GP85_SPI_MISO		0x0C
#define GP86_SPI_MOSI		0x30
#define GP87_SPI_CSN		0xC0

// 0xFE62 rP8PUD0 		// P82 ~ P83 Pullup/down control Register
#define GP82_PUD_DIS		0x00
#define GP83_PUD_DIS		0x00
#define GP82_PDEN		    0x10
#define GP83_PDEN		    0x40
#define GP82_PUEN		    0x20
#define GP83_PUEN		    0x80
#define GP8_LOW_ALL_PDEN	0x55
#define GP8_LOW_ALL_PUEN	0xAA
#define GP8_LOW_ALL_PUD_DIS	0x00

// 0xFE63 rP8PUD1 		// P84 ~ P87 Pullup/down control Register
#define GP84_PUD_DIS		0x00
#define GP85_PUD_DIS		0x00
#define GP86_PUD_DIS		0x00
#define GP87_PUD_DIS		0x00
#define GP84_PDEN		    0x01
#define GP85_PDEN		    0x04
#define GP86_PDEN		    0x10
#define GP87_PDEN		    0x40
#define GP84_PUEN		    0x02
#define GP85_PUEN		    0x08
#define GP86_PUEN		    0x20
#define GP87_PUEN		    0x80
#define GP8_HIGH_ALL_PDEN	0x55
#define GP8_HIGH_ALL_PUEN	0xAA
#define GP8_HIGH_ALL_PUD_DIS	0x00


// -----------------------------------------------------------------------
// BRAC 
// -----------------------------------------------------------------------
// 0xFF00 rBRAC_CTRL 			// Control Register for BRAC¢ç Decoding
#define	BRAC_EN				0x01	// Start the BRAC¢ç Decoding
#define	DIR_PCM_EN			0x02	// Enable Direct PCM output
#define	B3BIT_EN			0x08	// Enable 3bit BRAC¢ç Decoding
#define	GO_BOT			0x10	// Bring the Output DAC level to zero from VOmax/2
#define	GO_MID			0x20	// Bring the Output DAC level to VOmax/2 from zero
#define	SIL_EN			0x40	// Silence Start , size with BRAC_SIZEx
#define	DMA_EN				0x80	// Enable DMA operation

// 0xFF01 rBRAC_CTRL2			// Control Register2 for BRAC¢ç Decoding
#define	DATA_SRC_EFLASH		0x00	// select eFLASH area
#define	DATA_SRC_SFLASH		0x01	// select external serial FLASH area
#define	ENC_MODE        	0x02	// BRAC encoding mode enable
#define	XRAM_IBB_EN		    0x20	// XRAM IBB Enable

// 0xFF02 rBRAC_INT_EN			// BRAC interrupt mask register
#define BRAC_MASK         0x01  // BRAC interrupt enable
#define IBB_MASK          0x02  // IBB half empty interrupt enable

// 0xFF03 rBRAC_INT_PEND
#define BRAC_PEND			0x01
#define IBB_PEND	        0x02


// 0xFF10 rBRAC_ENC_CTRL
#define BRAC_ENC_BUSY			0x01



// 0xFF18 rDAC_CTL			// DAC Control Register
#define DAC_EN				0x01	// Enable DAC
#define D3_UP_DIS		  0x02	// Disable 3x up-sampling
#define VOL_DIS		    0x04	// Disable volume control
#define DAC_PDN				0x08	// Enable DAC power down


// 0xFF1B rVOLUME			// Volume Control Register in Decoding Mode.
#define	VOLUME_MUTE		0x00
#define	VOLUME_MAX		0xFF


// 0xFF20 rSFCTRL 			// SF Control register
#define	SF_BUSY		0x01	// 0 : Busy ( 0 : Idle, 1 : Busy )
#define	SF_CSN		0x02	// 1 : SF_CSN / CPU_Request
#define	SF_RS		0x04	  // 2 : READ_START
#define	SF_CSN_LOW()		(rSFCTRL = 0x00)
#define	SF_CSN_HIGH()		(rSFCTRL |= SF_CSN)


// 0xFF22 rSFDMA_CTRL			// SF Read-DMA Control register
#define	SFDMA_EN			    0x01	// Enable SF Read-DMA.
#define	SFDMA_AUTO_INC		0x02	// SFDMA_START_ADR is increased automatically.
#define	SFDMA_CPU_MODE    0x04  // XRAM is not written by SFDMA.

// 0xFF2A rSFCTRL2        // SF Control register 2
#define SF_FAST_MODE      0x01  // Fast mode of SPI clock.
#define SF_4BYTE_ADDR     0x10  // 4Byte serial flash address.

// -----------------------------------------------------------------------
// BRJPEG
// -----------------------------------------------------------------------

// 0xFF56 rBRJPEG_CFG       		// BRJPEG Configuration
#define BRJPEG_BLOCK_TYPE           0x01    // block size 0:8x8, 1:4x4
#define BRJPEG_BLOCK_TYPE_8         0x00    // block size 0:8x8, 1:4x4
#define BRJPEG_BLOCK_TYPE_4         0x01    // block size 0:8x8, 1:4x4

#define BRJPEG_DC_PREDICTION        0x02    // dc_prediction
#define BRJPEG_DC_PREDICTION_0      0x00    // block size 0:8x8, 1:4x4
#define BRJPEG_DC_PREDICTION_1      0x02    // block size 0:8x8, 1:4x4

#define BRJPEG_CFG_2_RESERVED       0x04    // reserved

#define BRJPEG_IBB_TYPE             0x18    // IBB type 0:Internal parallel flash, 1:External serial flash, 2:XRAM
#define BRJPEG_IBB_TYPE_EFLASH      0x00    
#define BRJPEG_IBB_TYPE_SFLASH      0x08    
#define BRJPEG_IBB_TYPE_XRAM        0x10    
#define BRJPEG_IBB_TYPE_RESERVED    0x18    

// 0xFF57 rBRJPEG_BUFSEL       		// BRJPEG Buf allocation
#define BRJPEG_VLD_OUT              0x01    // vld output buffer selection  0:BUF0/BUF1, 1:BUF2/BUF3
#define BUFSEL_VLD_OUT_BUF01        0x00    
#define BUFSEL_VLD_OUT_BUF23        0x01   

#define BRJPEG_IDCT_IN              0x02    // idct inpu buffer selection   0:BUF0/BUF1, 1:BUF2/BUF3
#define BRJPEG_IDCT_IN_BUF01        0x00    
#define BRJPEG_IDCT_IN_BUF23        0x02    

#define BRJPEG_IDCT_OUT             0x0C    // idct output buffer selection 0:BUF0, 1:BUF2, 2:BUF4, 3:BUF5
#define BRJPEG_IDCT_OUT_BUF0        0x00    
#define BRJPEG_IDCT_OUT_BUF2        0x04    
#define BRJPEG_IDCT_OUT_BUF4        0x08    
#define BRJPEG_IDCT_OUT_BUF5        0x0C    

// 0xFF58 rBRJPEG_CMD       		// BRJPEG Command
#define BRJPEG_VLD_EN               0x01    // vld enable 0:idle, 1:enable/busy
#define BRJPEG_VLD_EN_0             0x00    
#define BRJPEG_VLD_EN_1             0x01    

#define BRJPEG_IDCT_EN              0x02    // idct enable 0:idle, 1:enable/busy
#define BRJPEG_IDCT_EN_0            0x00    
#define BRJPEG_IDCT_EN_1            0x02    

// 0xFF59 rBRJPEG_IE       		// BRJPEG Interrupt Enable
#define BRJPEG_VLD_DONE_IE          0x01    // vld done interrupt enable 0:disable, 1:enable
#define BRJPEG_VLD_DONE_IE_0        0x00    
#define BRJPEG_VLD_DONE_IE_EN       0x01    

#define BRJPEG_IDCT_DONE_IE         0x02    
#define BRJPEG_IDCT_DONE_IE_0       0x00    
#define BRJPEG_IDCT_DONE_IE_EN      0x02    
//
// 0xFF5A rBRJPEG_ICLR       		// BRJPEG Interrupt Clear
#define BRJPEG_VLD_DONE_ICLR        0x01    // vld done interrupt clear by writing 1
#define BRJPEG_VLD_DONE_ICLR_0      0x00
#define BRJPEG_VLD_DONE_ICLR_CLR    0x01

#define BRJPEG_IDCT_DONE_ICLR       0x02    // idct done interrupt clear by writing 1
#define BRJPEG_IDCT_DONE_ICLR_0     0x00
#define BRJPEG_IDCT_DONE_ICLR_CLR   0x02

//
// 0xFF5B rBRJPEG_ST       		// BRJPEG Status
#define BRJPEG_VLD_DONE_ST          0x01    // vld done status, set by writing 1
#define BRJPEG_VLD_DONE_ST_0        0x00    
#define BRJPEG_VLD_DONE_ST_1        0x01    

#define BRJPEG_IDCT_DONE_ST         0x02    // idct done status, set by writing 1
#define BRJPEG_IDCT_DONE_ST_0       0x00   
#define BRJPEG_IDCT_DONE_ST_1       0x02  

#define BRJPEG_IDCT_OVF_ST          0x04    // idct accumulator overflow
#define BRJPEG_IDCT_OVF_ST_0        0x00 
#define BRJPEG_IDCT_OVF_ST_1        0x04

// 0xFF5C rBRJPEG_VLD_MODE 		// BRJPEG VLD mode
#define BRJPEG_VLD_BITS             0x1F    // Number of bits for bits operation command
#define BRJPEG_VLD_BITS_1           0x01    
#define BRJPEG_VLD_BITS_2           0x02    
#define BRJPEG_VLD_BITS_3           0x03    
#define BRJPEG_VLD_BITS_4           0x04    
#define BRJPEG_VLD_BITS_5           0x05    
#define BRJPEG_VLD_BITS_6           0x06    
#define BRJPEG_VLD_BITS_7           0x07    
#define BRJPEG_VLD_BITS_8           0x08    
#define BRJPEG_VLD_BITS_9           0x09    
#define BRJPEG_VLD_BITS_10          0x0A    
#define BRJPEG_VLD_BITS_11          0x0B    
#define BRJPEG_VLD_BITS_12          0x0C    
#define BRJPEG_VLD_BITS_13          0x0D    
#define BRJPEG_VLD_BITS_14          0x0E    
#define BRJPEG_VLD_BITS_15          0x0F    
#define BRJPEG_VLD_BITS_16          0x10 

#define BRJPEG_VLD_OP               0xE0    // VLD mode 
#define BRJPEG_VLD_OP_VLD_IQ        0x00    
#define BRJPEG_VLD_OP_VLD_ONLY      0x20    
#define BRJPEG_VLD_OP_IQ_ONLY       0x40    
#define BRJPEG_VLD_OP_RESERVED      0x60    
#define BRJPEG_VLD_OP_GET_BITS      0x80    
#define BRJPEG_VLD_OP_PEEK_BITS     0xA0    
#define BRJPEG_VLD_OP_DROP_BITS     0xC0    
#define BRJPEG_VLD_OP_FILL_BUFFER   0xE0    


// 0xFF5D rBRJPEG_IDCT_MODE 		// BRJPEG IDCT mode
#define BRJPEG_IDCT_NOO             0x0F    // Number of operations for MAC16/MUL16/ADD16/ADD32
#define BRJPEG_IDCT_NOO_1           0x00    
#define BRJPEG_IDCT_NOO_2           0x01    
#define BRJPEG_IDCT_NOO_3           0x02    
#define BRJPEG_IDCT_NOO_4           0x03    
#define BRJPEG_IDCT_NOO_5           0x04    
#define BRJPEG_IDCT_NOO_6           0x05    
#define BRJPEG_IDCT_NOO_7           0x06    
#define BRJPEG_IDCT_NOO_8           0x07    
#define BRJPEG_IDCT_NOO_9           0x08    
#define BRJPEG_IDCT_NOO_10          0x09    
#define BRJPEG_IDCT_NOO_11          0x0A    
#define BRJPEG_IDCT_NOO_12          0x0B    
#define BRJPEG_IDCT_NOO_13          0x0C    
#define BRJPEG_IDCT_NOO_14          0x0D    
#define BRJPEG_IDCT_NOO_15          0x0E    
#define BRJPEG_IDCT_NOO_16          0x0F    

#define BRJPEG_SAT_DIS              0x10    // IDCT acc saturation disable 
#define BRJPEG_SAT_DIS_0            0x00    // saturation mode
#define BRJPEG_SAT_DIS_1            0x10    // disable saturation

#define BRJPEG_IDCT_OP              0xE0    // IDCT mode 
#define BRJPEG_IDCT_OP_IDCT         0x00    
#define BRJPEG_IDCT_OP_MAC16        0x20   // mul 16bit and add/save it to 32bit 
#define BRJPEG_IDCT_OP_MUL16        0x40   // mul 16bit and save it to 32bit 
#define BRJPEG_IDCT_OP_ADD16H       0x60   // add 16bit and save it to 16bit 
#define BRJPEG_IDCT_OP_ADD16W       0x80   // add 16bit and save it to 32bit 
#define BRJPEG_IDCT_OP_ADD32        0xA0   // add 32bit and save it to 32bit 
#define BRJPEG_IDCT_OP_SUM16W       0xC0   // sum 16bit and save it to 32bit 
#define BRJPEG_IDCT_OP_SUM32        0xE0   // sum 32bit and save it to 32bit 

// -----------------------------------------------------------------------
// RTC 
// -----------------------------------------------------------------------

// 0xFF80 rRTCCON0			// RTC Control 0
#define	RTC_CNTSEL			        0x10	// for test
#define	RTC_CLKSEL			        0x08	// for test
#define	RTC_CLKRST			        0x04	// for test
#define	RTC_BCDMOD            		0x02	// BCD counter MODify.
#define	RTC_START			        0x00	// RTC start bit.
#define	RTC_HALT            		0x01	// RTC start bit.

// 0xFF81 rRTCCON1				// RTC Control 1
#define	PEINTPEND			        0x10	// Periodic Interrupt Pending
#define	PEINTS_1DIV512			    0x02	// Periodic interrupt generated every 1/512 second
#define	PEINTS_1DIV256			    0x04	// Periodic interrupt generated every 1/256 second
#define	PEINTS_1DIV64			    0x06	// Periodic interrupt generated every 1/64 second
#define	PEINTS_1DIV16			    0x08	// Periodic interrupt generated every 1/16 second
#define	PEINTS_1DIV4			    0x0A	// Periodic interrupt generated every 1/4 second
#define	PEINTS_1DIV2			    0x0C	// Periodic interrupt generated every 1/2 second
#define	PEINTS_1			        0x0E	// Periodic interrupt generated every 1 second
#define	PEINTEN	            		0x01	// Periodic Interrupt Enable

// 0xFF8A rRTCALM			// ALARM Control
#define	WKUP_PEND			        0x40	// ALARM Wakeup pending bit
#define	ALM_PEND            		0x20	// ALARM pending bit
#define	ALM_EN				        0x10	// ALARM global enable bit
#define	DATE_EN            			0x08	// Date ALARM enable bit
#define	HOUR_EN			            0x04	// Hour ALARM enable bit
#define	MIN_EN            			0x02	// Minute ALARM enable bit
#define	SEC_EN			            0x01	// Second ALARM enable bit


// 0xFFA0 rFCON_CTRL			//eFlash Control
#define	PROG_MODE_PROGRAM		    0x02
#define	PROG_MODE_ERASE			    0x00
#define	FCON_CTRL_RESET			    0x04

// 0xFFA1 rFCON_STAT
#define	FCON_BUSY				    0x01

// -----------------------------------------------------------------------
// I80LCD
// -----------------------------------------------------------------------

// 0xFFC0 rI80LCD_CFG_0	        
#define I80LCD_IF_BITS               0x03    // interface bits
#define I80LCD_IF_BITS_8             0x00    
#define I80LCD_IF_BITS_9             0x01    
#define I80LCD_IF_BITS_16            0x02    
#define I80LCD_IF_BITS_18            0x03    

#define I80LCD_IF_BYTE_MAPPING       0x0C    // interface byte mapping
#define I80LCD_IF_BYTE_MAPPING_0     0x00    
#define I80LCD_IF_BYTE_MAPPING_1     0x04    
#define I80LCD_IF_BYTE_MAPPING_2     0x08    
#define I80LCD_IF_BYTE_MAPPING_3     0x0C    

#define I80LCD_RGB_TYPE              0x30    // rgb depth
#define I80LCD_RGB_TYPE_RGB332       0x00
#define I80LCD_RGB_TYPE_RGB565       0x10
#define I80LCD_RGB_TYPE_RGB666       0x20
#define I80LCD_RGB_TYPE_RGB888       0x30

#define I80LCD_RGB_2PIXEL            0x40    // 1 pixel/2 pixel processing
#define I80LCD_RGB_2PIXEL_1PIXEL     0x00    
#define I80LCD_RGB_2PIXEL_2PIXEL     0x40    

#define I80LCD_2PIXEL_PACK           0x80    // 2 pixel packing in 3 x 16bits
#define I80LCD_2PIXEL_PACK_0         0x00    
#define I80LCD_2PIXEL_PACK_1         0x80    


// 0xFFC0 rI80LCD_CFG_1	        
#define I80LCD_I_P_BIT_LEN           0x01    // Index/paramter bit width
#define I80LCD_I_P_BIT_LEN_8_BIT     0x00 
#define I80LCD_I_P_BIT_LEN_16_BIT    0x01 

#define I80LCD_SPI_EN                0x02    // serial spi enable
#define I80LCD_SPI_EN_0              0x00    
#define I80LCD_SPI_EN_1              0x02    

#define I80LCD_SPI_LINE              0x04    // serial spi lines
#define I80LCD_SPI_LINE_3            0x00
#define I80LCD_SPI_LINE_4            0x04    

#define I80LCD_WAIT_EN               0x08    // cpu wait enable
#define I80LCD_WAIT_EN_0             0x00
#define I80LCD_WAIT_EN_1             0x08    

#define I80LCD_RS_INV                0x10    // cpu wait enable
#define I80LCD_RS_INV_0              0x00
#define I80LCD_RS_INV_1              0x10    

// 0xFFD8 rI80LCD_CMD       	       // I80LCD Command
#define I80LCD_EN                    0x01    // vld enable 0:idle, 1:enable/busy
#define I80LCD_EN_0                  0x00    
#define I80LCD_EN_1                  0x01    

#define I80LCD_CMD_TYPE              0x06    // cmd type
#define I80LCD_CMD_TYPE_INDEX        0x00    // cmd type
#define I80LCD_CMD_TYPE_PARAM        0x02    // cmd type
#define I80LCD_CMD_TYPE_RGB          0x04    // cmd type
#define I80LCD_CMD_TYPE_VDMA         0x06    // cmd type

#define I80LCD_CMD_WR                0x08    // write/read
#define I80LCD_CMD_WR_RD             0x00    // write/read
#define I80LCD_CMD_WR_WR             0x08    // write/read

#define I80LCD_KEEP_CSB_LOW          0x10    // keep csb low
#define I80LCD_KEEP_CSB_LOW_0        0x00   
#define I80LCD_KEEP_CSB_LOW_1        0x10    

#define I80LCD_N_TRAN                0xE0    // Number of transaction
#define I80LCD_N_TRAN_1              0x00    // Number of transaction
#define I80LCD_N_TRAN_2              0x20    // Number of transaction
#define I80LCD_N_TRAN_3              0x40    // Number of transaction
#define I80LCD_N_TRAN_4              0x60    // Number of transaction
#define I80LCD_N_TRAN_5              0x80    // Number of transaction
#define I80LCD_N_TRAN_6              0xA0    // Number of transaction


// 0xFFD9 rI80LCD_IE                     // I80LCD Interrupt Enable
#define I80LCD_DONE_IE           0x01    // vld done interrupt enable 0:disable, 1:enable
#define I80LCD_DONE_IE_0         0x00    
#define I80LCD_DONE_IE_EN        0x01    

// 0xFFDA rI80LCD_ICLR                   // I80LCD Interrupt Clear
#define I80LCD_DONE_ICLR         0x01    // vld done interrupt clear by writing 1
#define I80LCD_DONE_ICLR_0       0x00
#define I80LCD_DONE_ICLR_CLR     0x01

//
// 0xFFDB rI80LCD_ST                     // I80LCD Status
#define I80LCD_DONE_ST           0x01    // vld done status, set by writing 1
#define I80LCD_DONE_ST_0         0x00    
#define I80LCD_DONE_ST_1         0x01    

// -----------------------------------------------------------------------
// VDMA
// -----------------------------------------------------------------------

// 0xFFE0 rVDMA_CFG_0	        
#define VDMA_DST                 0x01    // destination memories
#define VDMA_DST_XRAM            0x00    
#define VDMA_DST_I80LCD          0x01    

#define VDMA_DST_RGB             0x06    // destination rgb type
#define VDMA_DST_RGB_RGB888      0x00
#define VDMA_DST_RGB_RGB565      0x02
#define VDMA_DST_RGB_RGB332      0x04
#define VDMA_DST_RGB_RGBA5551    0x06

#define VDMA_BG_SRC              0x18    // background source memories
#define VDMA_BG_SRC_XRAM         0x00
#define VDMA_BG_SRC_I80LCD       0x08
#define VDMA_BG_SRC_EFLASH       0x10
#define VDMA_BG_SRC_SFLASH       0x18

#define VDMA_BG_RGB              0xE0    // background source rgb type
#define VDMA_BG_RGB_YCBCR        0x00
#define VDMA_BG_RGB_RGB888       0x20
#define VDMA_BG_RGB_RGB565       0x40
#define VDMA_BG_RGB_RGB332       0x60
#define VDMA_BG_RGB_RGBA5551     0x80
#define VDMA_BG_RGB_RGBA4444     0xA0
#define VDMA_BG_RGB_RGB0         0xC0
#define VDMA_BG_RGB_VDMA_RGB     0xE0

// 0xFFE1 rVDMA_CFG_1
#define VDMA_BLEND_EN            0x01    // blending enable
#define VDMA_BLEND_EN_0          0x00    // blending enable
#define VDMA_BLEND_EN_1          0x01    // blending enable

#define VDMA_FG_SRC              0x06    // foreground source memories
#define VDMA_FG_SRC_XRAM         0x00
#define VDMA_FG_SRC_I80LCD       0x02
#define VDMA_FG_SRC_EFLASH       0x04
#define VDMA_FG_SRC_SFLASH       0x06

#define VDMA_FG_RGB              0x38    // foreground source rgb type
#define VDMA_FG_RGB_YCBCR        0x00
#define VDMA_FG_RGB_RGB888       0x08
#define VDMA_FG_RGB_RGB565       0x10
#define VDMA_FG_RGB_RGB332       0x18
#define VDMA_FG_RGB_RGBA5551     0x20
#define VDMA_FG_RGB_RGBA4444     0x28
#define VDMA_FG_RGB_FONT         0x30
#define VDMA_FG_RGB_VDMA_RGB     0x38

// 0xFFF9 rVDMA_CMD       	       // VDMA Command
#define VDMA_EN                  0x01    // vld enable 0:idle, 1:enable/busy
#define VDMA_EN_0                0x00    
#define VDMA_EN_1                0x01    

// 0xFFFA rVDMA_IE                     // VDMA Interrupt Enable
#define VDMA_DONE_IE             0x01    // vld done interrupt enable 0:disable, 1:enable
#define VDMA_DONE_IE_0           0x00    
#define VDMA_DONE_IE_EN          0x01    

// 0xFFFB rVDMA_ICLR                   // VDMA Interrupt Clear
#define VDMA_DONE_ICLR           0x01    // vld done interrupt clear by writing 1
#define VDMA_DONE_ICLR_0         0x00
#define VDMA_DONE_ICLR_CLR       0x01

//
// 0xFFFC rVDMA_ST                     // VDMA Status
#define VDMA_DONE_ST             0x01    // vld done status, set by writing 1
#define VDMA_DONE_ST_0           0x00    
#define VDMA_DONE_ST_1           0x01    



#define nc_print(a)				\
	{					\
		const UCHAR *ttt = (UCHAR *)a;	\
		EnterCriticalSection;		\
		ValPort16 = (USHORT)ttt;	\
		CmdPort = 0x10;			\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_printv(a,b)				\
	{					\
		const UCHAR *ttt = (UCHAR *)a;	\
		EnterCriticalSection;		\
		ValPort16 = (USHORT)ttt;	\
		ValPort32 = b;			\
		CmdPort = 0x11; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_printv8(a,b)				\
	{					\
		const UCHAR *ttt = (UCHAR *)a;	\
		EnterCriticalSection;		\
		ValPort16 = (USHORT)ttt;	\
		ValPort8 = b;			\
		CmdPort = 0x12; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_finish				\
	{					\
		EnterCriticalSection;		\
		CmdPort = 0x20; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_stop					\
	{					\
		EnterCriticalSection;		\
		CmdPort = 0x21; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_cyc_start				\
	{					\
		EnterCriticalSection;		\
		CmdPort = 0x30; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_cyc_end				\
	{					\
		EnterCriticalSection;		\
		CmdPort = 0x31; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_fsdb_start				\
	{					\
		EnterCriticalSection;		\
		CmdPort = 0x22; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#define nc_fsdb_dump_off			\
	{					\
		EnterCriticalSection;		\
		CmdPort = 0x23; 		\
		CmdPort = 0x80; 		\
		ExitCriticalSection;		\
	}

#endif	/* __BMC513_REGDEF_h__ */

//==========================================================================
//       Revision History
//==========================================================================
// Rev:   Date:                Reason:

