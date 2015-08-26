#include <msp430.h>
#include "Headers/head.h"
#include <ctpl.h>

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    initialize();
    int nextState = 0;
    while(1)
    {

    	switch(nextState)
    	{
    	case ShowTime:
    		break;
    	case SetTime:
    		break;
    	case Sleep:
    		break;

    	}

    }


    return 0;
}

void initialize()
{

	//GPIO Setup
	//
	// Data register setup for PxDIR, PxOUT
	//   | Px.7 | Px.6 | Px.5 | Px.4 | Px.3 | Px.2 | Px.1 | Px.0 |
	//

	P1DIR = 0xFF; // All P1 ports outputs
	P1OUT = 0x08; // P1.3 high, all else low

	P2DIR = 0xBF; // P2.6 input, all else output
	P2OUT = 0xB4; // P2.2, P2.4, P2.5, P2.7 high, all else low. P2.6 pulldown selected
	P2REN |= BIT6; // Enable P2.6 pulldown
	P2IES =~ BIT6; // Interrupt on low -> high
	P2IE |= BIT6;  // Enable interrupt

	P3DIR = 0xBF; // P3.6 input, all else output
	P3OUT = 0x9B; // P3.1, P3.2, P3.3, P3.4, P3.7 high, all else low. P3.6 pulldown selected
	P3REN |= BIT6; // Enable P3.6 pulldown
	P3IES =~ BIT6; // Interrupt on low -> high
	P3IE |= BIT6;  // Enable interrupt

	P4DIR |= BIT0 + BIT1; // P4.0 and P4.1 outputs
	P4OUT = BIT1; // P4.1 high

	// External clock (XT1) and system clocks setup
	PJSEL0 |= BIT4 + BIT5;

	// RTC Setup
}
