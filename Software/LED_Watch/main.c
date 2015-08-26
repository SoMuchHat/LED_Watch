#include <msp430.h>
#include "Headers/head.h"
#include <ctpl.h>

/*
 * main.c
 */

int nextState = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    initialize();

    while(1)
    {
    	switch(nextState)
    	{
    	case ShowTime:
    		break;
    	case SetTime:
    		break;
    	case Sleep:
    		ctpl_enterLpm35(CTPL_DISABLE_RESTORE_ON_RESET);
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
	P2IFG &= ~BIT6; // Clear P2.6 interrupt flag

	P3DIR = 0xBF; // P3.6 input, all else output
	P3OUT = 0x9B; // P3.1, P3.2, P3.3, P3.4, P3.7 high, all else low. P3.6 pulldown selected
	P3REN |= BIT6; // Enable P3.6 pulldown
	P3IES =~ BIT6; // Interrupt on low -> high
	P3IE |= BIT6;  // Enable interrupt
	P3IFG &= ~BIT6; // Clear P3.6 interrupt flag

	P4DIR |= BIT0 + BIT1; // P4.0 and P4.1 outputs
	P4OUT = BIT1; // P4.1 high

	// External clock (XT1) and system clocks setup
	PJSEL0 |= BIT4 + BIT5;

	CSCTL0_H = 0xA5;						// Unlock clock register
	CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting (8)
	CSCTL2 = SELA_0 + SELS_3 + SELM_3; 		//ACLK = XT1 and MCLK = DCO
	//CHANGE CSCTL3 DIVIDERS!
	CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;
	CSCTL4 |= XT1DRIVE_0;
	CSCTL4 &= ~XT1OFF;

	do
	{
		CSCTL5 &= ~XT1OFFG;		// Clear XT1 fault flag
		SFRIFG1 &= ~OFIFG;
	} while (SFRIFG1&OFIFG);
	CSCTL0_H = 0x01; // Lock clock register

	// RTC Setup
	RTCCTL01 |= RTCBCD + RTCHOLD + RTCRDYIE; //BCD, Hold RTC, enable RTC ready interrupt (1 sec)
	RTCSEC = 0x00;
	RTCMIN = 0x00;
	RTCHOUR = 0x00;
	RTCCTL01 &= ~RTCHOLD; //Release RTC hold


	__bis_SR_register(GIE); //Enable interrupts
}

// RTC_b ISR
#pragma vector=RTC_VECTOR
__interrupt void rtc_isr(void)
{

}

// Port 2 ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
	switch(nextState)
	{
	case Sleep:
	{
		nextState = ShowTime;
		break;
	}
	case ShowTime:
	{
		nextState = SetTime;
		break;
	}
	case SetTime:
	{
		//Switch between sec/min/hour select
		break;
	}
	}
	P2IFG &= ~BIT6;
	P2IE = 0; 			// Disable interrupt from P2 and wait for standby clock to elapse before enabling again
}

// Port 3 ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT3_VECTOR
__interrupt void Port_3(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT3_VECTOR))) Port_3 (void)
#else
#error Compiler not supported!
#endif
{
	switch(nextState)
	{
	case Sleep:
	{
		nextState = ShowTime;
		break;
	}
	case ShowTime:
	{
		nextState = SetTime;
		break;
	}
	case SetTime:
	{
		//Increment sec/min/hour
		break;
	}
	}
	P3IFG &= ~BIT6;
	P3IE = 0;		// Disable interrupt from P3 and wait for standby clock to elapse before enabling again
}
