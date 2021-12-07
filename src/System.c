
#define __SYSTEM_c__
#include "includes.h"


__idata uint8_t start, diff, tick, cnt, end;
__near_func void mdelay(uint16_t ms)
{
//	uint8_t start, diff, tick;
//	uint8_t cnt = ms / 200;
//	uint8_t end = ms % 200;
	cnt = ms / 200;
	end = ms % 200;

	while( cnt ) {
		start = tick_1ms;
//		printf((char *)"cnt = %d, end = %d, start = %d\n", cnt, end, start);
		do {
			tick = tick_1ms;
			if( tick < start ) diff = ((255 - start) + tick);
			else  diff = tick - start;
		} while( diff < 200 );
		cnt--;
	}

	start = tick_1ms;
	do {
		tick = tick_1ms;
		if( tick < start ) diff = ((255 - start) + tick);
		else  diff = tick - start;
	} while( diff < end );
}

__near_func void delay(uint8_t sec)
{
	do {
		mdelay(1000);
	} while( sec-- );
}

__near_func int getkey(void)
{
	int c = -1;

	if( rUERSTAT & ((1<<0)|(1<<1)|(1<<2)|(1<<3)) ) {		// Error check.
		rUINTCON = (rUINTCON & 0x1F) | (1<<7);
	}

	if( rUTRSTAT & (1<<1) ) {
		c = rURXBUF;
	}

	return c;
}


/*******************************************************************************
* Function Name  : putch
* Description    : Transmits signle data through the uart peripheral.
* Input          : uByte - the data to transmit.
* Output         : None
* Return         : None
*******************************************************************************/
__near_func void putch(uint8_t uByte)
{
	if(uByte == '\n') {
		while(!(rUTRSTAT & (1<<4)));
		rUTXBUF = '\r';
	}
	while(!(rUTRSTAT & (1<<4)));
	rUTXBUF= uByte;
}




#if (__CODE_MODEL__ == 2)
__near_func
#endif
int putchar(int ch)
{
	putch(ch);

	return ch;
}

#if (__CODE_MODEL__ == 2)
__near_func
#endif
int getchar(void)
{
	int ch = 0;

	do {
		ch = getkey();
	} while( ch == -1 );

	return ch;
}

// max : 255
void putint(uint8_t val, uint8_t cr)
{
	uint8_t t, z = 0;

	t = (val / 100) % 10;
	if( t ) {
		putchar(t+'0');
		z = 1;
	}
	t = (val / 10) % 10;
	if( t || z ) putchar(t+'0');
	t = (val / 1) % 10;
	putchar(t+'0');

	if( cr ) putchar(cr);
}

void puthex(uint8_t val, uint8_t cr)
{
	uint8_t t, d;

	for(d=0; d<2; d++) {
		if( d == 0 ) {
			t = (val >> 4) & 0xF;
		} else {
			t = val & 0xF;
		}

		if( t < 10 ) t += '0';
		else t += ('A' - 10);
		putchar(t);
	}
	if( cr ) putchar(cr);
}


__near_func void putstr(const char __code *ptr)
{
	while(*ptr) putchar(*ptr++);
}


/*	EOF	*/
