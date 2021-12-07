/*********************************************************
 * File Name : Boot.c
 * Function  : Boot Code For BMC51A
 * Program   : maeam, jhkim, nam  --  Boo-Ree Multimedia Inc.
 * Date      : Ayg, 1, 2008
 * Version   : 1.0
 * Mail      : support@boo-ree.com
 * Web       : www.boo-ree.com
 * History
 **********************************************************/

//===================================================================
//	Instruction to RUN !!!!!!
//		Build -> Build
//		Debug->Start Debugging
//		RUN
//===================================================================
#define __MAIN_c__
#include "includes.h"


/*
	***************************************
	* Memory map of BRmDPF
	***************************************
	
	0xFFFF +------------------+
	       | Fast debug code  |
	0xFC00 +------------------+
	       | Reserved         |
	0xFA00 +------------------+
	       | Environment data |
	0xF800 +------------------+
	       |                  |
	       |                  |
	       |                  |
	       | Application code |
	       |                  |
	       |                  |
	       |                  |
	0x1000 +------------------+
	       | Boot loader      |
	0x0100 +------------------+
	       | Interrupt vector |
	0x0000 +------------------+
	
	***************************************
*/

__near_func uint8_t check_tick(uint8_t task_tick)
{
	uint8_t ret;

	GlobalIntDisable;
	if( tick_10ms < task_tick ) ret = ((255 - task_tick) + tick_10ms);
	else ret = (tick_10ms - task_tick);
	GlobalIntEnable;

	return ret;
}

__near_func void main(void)
{
	uint8_t tx_tick = 0;

 	init_system();

	GlobalIntEnable;		// Global Interrupt Disable.

	printf((char *)"System Information : Fsys = %s\n", ((rCLKCON & 0x7)==0x5)?"PLL":"EMCLK");
//	putstr("\n\n\nSystem Information : Fsys = ");
//	putstr(((rCLKCON & 0x7)==0x5)?"PLL":"EMCLK");
//	putchar('\n');

	BLDC_Test();

	do {
		mdelay(500);
		printf((char *)"%s()[%d]:\n", __func__, __LINE__);
		rP7_b3 ^= 1;
#if 0
		if( check_tick(tx_tick) >= 50 ) {			// 500 ms
			tx_tick = tick_10ms;

//			printf((char *)"%s()[%d]:\n", __func__, __LINE__);
			rP7_b3 ^= 1;
		}
#endif
	} while(getkey() != ESC);
}

//============================================================================
//		Secondary Interrupt Vectors Begin
//============================================================================
// 	Notice : -------------------------------------------------
// 	Interrupt Vector can be installed by "#pragma vector=0x##"
// 	But there is one Limitation that Interrupt Vector
//	SHOULD be used with main() within Same File.
//------------------------------------------------------------

#pragma vector=0x03
#pragma location="ISR_SEG"
__interrupt void _WdtInt(void)
{
	rWDTCON |= WINTPEND;
}


#pragma vector=0x0b
#pragma location="ISR_SEG"
__interrupt void _BracDmaInt(void)
{
}


#pragma vector=0x13
#pragma location="ISR_SEG"
__interrupt void _AdcInt(void)
{
}


#pragma vector=0x1b
#pragma location="ISR_SEG"
__interrupt void _ExInt0(void)
{
}


#pragma vector=0x23
#pragma location="ISR_SEG"
__interrupt void _ExInt1(void)
{
}



#pragma vector=0x2b
#pragma location="ISR_SEG"
__interrupt void _SpiInt(void)
{
}


#pragma vector=0x33
#pragma location="ISR_SEG"
__interrupt void _Tmr0MatInt(void)
{
	rT0CON |= TINTPEND;
	tick_1ms++;
}


#pragma vector=0x3b
#pragma location="ISR_SEG"
__interrupt void _Tmr1MatInt(void)
{
	rT1CON |= TINTPEND;
	tick_10ms++;
}


#pragma vector=0x43
#pragma location="ISR_SEG"
__interrupt void _Tmr2MatInt(void)
{
}


#pragma vector=0x4b
#pragma location="ISR_SEG"
__interrupt void _BrJpegInt(void)
{
}


#pragma vector=0x53
#pragma location="ISR_SEG"
__interrupt void _UartTxInt(void)
{
	rUINTCON = (rUINTCON & 0x1F) | (1<<5);
}


#pragma vector=0x5b
#pragma location="ISR_SEG"
__interrupt void _UartRxInt(void)
{
	rUINTCON = (rUINTCON & 0x1F) | (1<<6);
}


#pragma vector=0x63
#pragma location="ISR_SEG"
__interrupt void _Uart0ErrInt(void)
{
	rUINTCON = (rUINTCON & 0x1F) | (1<<7);
}


#pragma vector=0x6b
#pragma location="ISR_SEG"
__interrupt void _VdmaInt(void)
{
}


#pragma vector=0x73
#pragma location="ISR_SEG"
__interrupt void _I80LcdInt(void)
{
}


#pragma vector=0x83
#pragma location="ISR_SEG"
__interrupt void _ExInt4_5(void)
{
}


#pragma vector=0x7b
#pragma location="ISR_SEG"
__interrupt void _ExInt2_3(void)
{
}


#pragma vector=0x8B
#pragma location="ISR_SEG"
__interrupt void _ExInt6(void)
{
	rb_isr();
	rEINTPND0 = (1<<6);
}


#pragma vector=0x93
#pragma location="ISR_SEG"
__interrupt void _ExInt7(void)
{
	rb_isr();
	rEINTPND0 = (1<<7);
}


#pragma vector=0x9b
#pragma location="ISR_SEG"
__interrupt void _ExInt8(void)
{
	rb_isr();
	rEINTPND1 = (1<<0);
}


#pragma vector=0xa3
#pragma location="ISR_SEG"
__interrupt void _ExInt9(void)
{
}


#pragma vector=0xab
#pragma location="ISR_SEG"
__interrupt void _RtcPriInt(void)
{
}


#pragma vector=0xb3
#pragma location="ISR_SEG"
__interrupt void _RtcAlmInt(void)
{
}


#pragma vector=0xbb
#pragma location="ISR_SEG"
__interrupt void _USBRSTInt()
{
}


#pragma vector=0xc3
#pragma location="ISR_SEG"
__interrupt void _USBSOFInt()
{
}

#pragma vector=0xcb
#pragma location="ISR_SEG"
__interrupt void _USBEP0Int()
{
}

#pragma vector=0xd3
#pragma location="ISR_SEG"
__interrupt void _USBEP1Int()
{
}

#pragma vector=0xdb
#pragma location="ISR_SEG"
__interrupt void _USBEP2Int()
{
}

#if EPIN_INTERRUT_ENABLE
#pragma vector=0xe3
#pragma location="ISR_SEG"
__interrupt void _USBEP3Int()
{
}
#endif

#pragma vector=0xeb
#pragma location="ISR_SEG"
__interrupt void _USBEP4Int()
{
}

//============================================================================
//		Secondary Interrupt Vectors End
//============================================================================
