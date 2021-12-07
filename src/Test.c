
#define __TEST_c__
#include "includes.h"

uint8_t hall, Direction = 0;
const uint8_t MoveTable1[8] = {0, 50, 11, 56, 44, 14, 35, 0};
const uint8_t MoveTable2[8] = {0, 35, 14, 44, 56, 11, 50, 0};
/*
 *            bit-5(C_EN) bit-4(C_IN) bit-3(B_EN) bit-2(B_IN) bit-1(A_EN) bit-0(A_IN)
 * 0x00(00) : (0<<C_EN) | (0<<C_IN) | (0<<B_EN) | (0<<B_IN) | (0<<A_EN) | (0<<A_IN)
 * 0x23(35) : (1<<C_EN) | (0<<C_IN) | (0<<B_EN) | (0<<B_IN) | (1<<A_EN) | (1<<A_IN)
 * 0x0E(14) : (0<<C_EN) | (0<<C_IN) | (1<<B_EN) | (1<<B_IN) | (1<<A_EN) | (0<<A_IN)
 * 0x2C(44) : (1<<C_EN) | (0<<C_IN) | (1<<B_EN) | (1<<B_IN) | (0<<A_EN) | (0<<A_IN)
 * 0x38(56) : (1<<C_EN) | (1<<C_IN) | (1<<B_EN) | (0<<B_IN) | (0<<A_EN) | (0<<A_IN)
 * 0x0B(11) : (0<<C_EN) | (0<<C_IN) | (1<<B_EN) | (0<<B_IN) | (1<<A_EN) | (1<<A_IN)
 * 0x32(50) : (1<<C_EN) | (1<<C_IN) | (0<<B_EN) | (0<<B_IN) | (1<<A_EN) | (0<<A_IN)
 * 0x00(00) : (0<<C_EN) | (0<<C_IN) | (0<<B_EN) | (0<<B_IN) | (0<<A_EN) | (0<<A_IN)
 */

void setup_adc(uint8_t div)
{
	rADCON1 = div | ADINSEL_ADIN0;
	rADCON0 |= ADMOD_NORMAL | ADCEN;
}

void setup_timer(uint8_t a)
{
	rCLK_EN0 |= T0_CKEN;
	rT0CON = ((10<<4) | SEL_PWM);
	rT0DATA = 199;
	rT0PDR = 0;
	rT0CON |= TRUN | TINTPEND;
	rIE0 &= ~IET0;
}

uint16_t read_adc(void)
{
	rADCON0 |= STC;
	while( !(rADAT0 & EOC) );

	return (uint16_t)((rADAT1 << 2) + ((rADAT0 & 0x30)>>4));
}

void set_pwm1_duty(uint16_t pwm) //read_adc());	// PWM duty -> 0(0%), 512(50%), 1023(100%)
{
	rT0PDR = pwm;
}

__near_func void BLDC_Test(void)
{
	// GP4[5:0] -> C_EN, C_IN, B_EN, B_IN, A_EN, A_IN
	// GP3[6:4] -> C_SE, B_SE, A_SE -> External Interrupt 6/7/8
	// GP13 -> AIN0
	// GP02 -> T0OUT(PWM)
	// GP1[2:0] -> Button
	rP1MOD0 = (rP1MOD0 & ~0x3F) | (GP10_DI | GP11_DI | GP12_DI);
//	setup_oscillator(OSC_8MHZ);                 // Set internal oscillator to 8MHz
	rP1MOD0 = (rP1MOD0 & ~0xC0) | GP13_AIN0;
//	setup_adc_ports(AN0);                       // Configure RA0 (AN0) pin as analog
	rP3 = 0;
//	output_b(0);                                // PORTB initial state
//	rP3MOD0 = GP30_DI | GP31_DI | GP32_DI | GP33_DI;
	rP3MOD1 = GP34_EINT6 | GP35_EINT7 | GP36_EINT8 | GP37_DI;
	rEINTEN0 = (1<<6) | (1<<7);
	rEINTEN1 = (1<<0);
//	set_tris_b(0xF7);                           // TRISB configurartion
//	port_b_pullups(TRUE);                       // Enable PORTB internal pull-ups
	rP4 = 0x0;
//	output_d(0);                                // PORTD initial state
	rP4MOD0 = GP40_DO | GP41_DO | GP42_DO | GP43_DO;
	rP4MOD1 = GP44_DO | GP45_DO | GP46_DO | GP47_DO;
//	set_tris_d(0);                              // Configure PORTD pins as outputs
	setup_adc(ADCKSEL_111);                 // Set ADC conversion time to 64Tosc
//	set_adc_channel(0);                         // Select channel 0 input
	setup_timer(1);        					 // Timer0 configuration for PWM
	rP0MOD1 = (rP0MOD1 & ~0x0C) | GP05_DI;		// Timer0 Output disable.
//	setup_ccp1(CCP_OFF);
//	enable_interrupts(GLOBAL);                  // Enable global interrupts
	GlobalIntEnable;

	do {
		if( rP1_b0 == 0 ) {                       // If RB1 button pressed(change direction)
			if(Direction == 0) {
				Direction = 1;
				rP0MOD1 = (rP0MOD1 & ~0x0C) | GP05_T0OUT_CAP; // Timer0 PWM Output enable.
				rEINTPND0 = (1<<6)|(1<<7);
				rEINTPND1 = (1<<0);
				rEINTEN0 = (1<<6) | (1<<7);
				rEINTEN1 = (1<<0);
//				setup_ccp1(CCP_PWM);                  // Configure CCP1 as a PWM
//				clear_interrupt(INT_RB);              // Clear RB IOC flag bit
//				enable_interrupts(INT_RB);            // Enable PORTB IOC
				hall = (rP3 >> 4) & 7;
				rP4 = MoveTable1[hall];
			}
		}
		if( rP1_b1 == 0 ) {                       // If RB1 button pressed(START Button)
			if(Direction == 0) {
				Direction = 2;
//				setup_ccp1(CCP_PWM);                  // Configure CCP1 as a PWM
				rP0MOD1 = (rP0MOD1 & ~0x0C) | GP05_T0OUT_CAP; // Timer0 PWM Output enable.
				rEINTPND0 = (1<<6)|(1<<7);
				rEINTPND1 = (1<<0);
				rIE2 |= ((1<<1)|(1<<2)|(1<<3));
//				clear_interrupt(INT_RB);              // Clear RB IOC flag bit
//				enable_interrupts(INT_RB);            // Enable PORTB IOC
				hall = ( rP3 >> 4) & 7;
				rP4 = MoveTable2[hall];
			}
		}

		while(Direction != 0)
		{
			set_pwm1_duty(read_adc());	// PWM duty -> 0(0%), 512(50%), 1023(100%)
			if( rP1_b2 == 0 ) {					// STOP Button.
				rIE2 &= ~((1<<1)|(1<<2)|(1<<3));
				rP4 = 0;
				rP0MOD1 = (rP0MOD1 & ~0x0C) | GP05_DO; // Timer0 PWM Output disable.
//				disable_interrupts(INT_RB);             // Disable PORTB IOC
//				output_d(0);
//				setup_ccp1(CCP_OFF);                    // CCP1 OFF
				Direction = 0;
			}
		}
	} while( 1 );
}


void rb_isr(void)
{
	hall = ( rP3 >> 4) & 7;
	if(Direction == 1)
		rP4 = MoveTable1[hall];
	else
		rP4 = MoveTable2[hall];
}

/*	EOF	*/
