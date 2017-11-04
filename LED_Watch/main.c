#include <msp430.h>
#include "Headers/head.h"
#include "Headers/led_controller.h"
//#include <ctpl.h>

/*
 * main.c
 */
#define DISPLAY_MODE_0  0
#define DISPLAY_MODE_1  1
#define DISPLAY_MODE_2  2

volatile int nextState = 1;
volatile int blink = 1;						// Blink off = 0, blink on = 1





volatile selectedRow_t selectedRow = SECONDS_ROW;
volatile char rtc_seconds;
volatile char rtc_minutes;
volatile char rtc_hours;

volatile int set_new_time;

volatile char displayMode = DISPLAY_MODE_0;
volatile char disp_seconds;
volatile char disp_minutes;
volatile char disp_hours;

volatile unsigned char button_shift_reg_1 = 0;
volatile unsigned char button_shift_reg_2 = 0;

volatile unsigned char button1_hold_seconds = 0;
volatile unsigned char button2_hold_seconds = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer

    rtc_seconds = 0;
    rtc_minutes = 0;
    rtc_hours = 0;

    set_new_time = 0;

    disp_seconds = 0;
    disp_minutes = 0;
    disp_hours = 0;

    initialize();

    char lastButton1State = 0;
    char lastButton2State = 0;

    while(1)
    {
        // Handle how the LEDs are displayed

        if (nextState != SetTime)
        {
            if (displayMode == DISPLAY_MODE_0)
            {
                __disable_interrupt();
                disp_seconds = rtc_seconds;
                disp_minutes = rtc_minutes;
                disp_hours = rtc_hours;

                switch (selectedRow)
                {
                case SECONDS_ROW:
                    LED_SetCurrentLED(disp_seconds, selectedRow);
                    break;

                case MINUTES_ROW:
                    LED_SetCurrentLED(disp_minutes, selectedRow);
                    break;

                case HOURS_ROW:
                    LED_SetCurrentLED(disp_hours, selectedRow);
                    break;
                default:
                    break;
                }

                __enable_interrupt();

                /*
                int i = 0;
                for (i = 0; i < 10; i++);;
                rtc_seconds++;
                */

            }

            else if (displayMode == DISPLAY_MODE_1)
            {

                /*
                static char i = 0;

                if (i == 0)
                {
                    disp_seconds = rtc_seconds;
                }
                if (i == 1)
                {
                    disp_seconds = rtc_minutes;
                    disp_minutes = rtc_minutes;
                }
                if (i == 2)
                {
                    char hours = rtc_hours;
                    if (hours >= 12)
                    {
                        hours = hours - 12;
                    }
                    disp_seconds = 5 * hours;
                    disp_seconds = (disp_seconds == 0) ? 0 : (disp_seconds - 1);
                    disp_minutes = 5 * hours;
                    disp_minutes = (disp_minutes == 0) ? 0 : (disp_minutes - 1);
                    disp_hours = rtc_hours;
                }

                if (selectedRow == SECONDS_ROW)
                {
                    i = i + 1;
                    if (i >= 3)
                    {
                        i = 0;
                    }
                }
                */
            }
        }


        else if (nextState == SetTime)
        {
            __disable_interrupt();

            if (blink == 1)
            {
                switch (selectedRow)
                {
                case SECONDS_ROW:
                    LED_SetCurrentLED(disp_seconds, selectedRow);
                    break;

                case MINUTES_ROW:
                    LED_SetCurrentLED(disp_minutes, selectedRow);
                    break;

                case HOURS_ROW:
                    LED_SetCurrentLED(disp_hours, selectedRow);
                    break;
                default:
                    break;
                }
            }
            else
            {
                reset_leds();
            }
            __enable_interrupt();
        }




    	// Determine next state
    	if (button_shift_reg_1 == 0xFF)
        {
            if ((nextState == SetTime && lastButton1State == 0) || (nextState == SetTime && button1_hold_seconds >= 2))
            {
                if (selectedRow >= 2)
                {
                    // Change RTC values
                    set_new_time = 1;
                    //nextState = ShowTime;
                    //blink = 1;
                }
                else
                {
                    selectedRow = (selectedRow_t)((int)selectedRow + 1);
                }

                button1_hold_seconds = 0;

            }
            else if (nextState != SetTime && button1_hold_seconds >= 3)
            {
                nextState = SetTime;
                selectedRow = (selectedRow_t)0;
                button1_hold_seconds = 0;
            }
            lastButton1State = 1;
        }
    	else if (button_shift_reg_1 == 0x00)
    	{
    	    lastButton1State = 0;
    	}

        if (button_shift_reg_2 == 0xFF)
        {
            if ((nextState == SetTime && lastButton2State == 0) || (nextState == SetTime && button2_hold_seconds >= 1))
            {
                switch (selectedRow)
                {
                    case HOURS_ROW:
                    {
                        if (disp_hours == 11)
                        {
                            disp_hours = 0;
                        }
                        else
                        {
                            disp_hours++;
                        }
                        break;
                    }
                    case MINUTES_ROW:
                    {
                        if (disp_minutes == 59)
                        {
                            disp_minutes = 0;
                        }
                        else
                        {
                            disp_minutes++;
                        }
                        break;
                    }
                    case SECONDS_ROW:
                    {
                        if (disp_seconds == 59)
                        {
                            disp_seconds = 0;
                        }
                        else
                        {
                            disp_seconds ++;
                        }
                        break;
                    }
                }
                blink = 1;
                button2_hold_seconds = 0;
            }
            lastButton2State = 1;
        }
        else if (button_shift_reg_2 == 0x00)
        {
            lastButton2State = 0;
        }

    }
}

void initialize()
{
	//GPIO Setup
	//
	// Data register setup for PxDIR, PxOUT
	//   | Px.7 | Px.6 | Px.5 | Px.4 | Px.3 | Px.2 | Px.1 | Px.0 |
	//

	//P1SEL = 0xEF;
	P1DIR = 0x3F;       // All P1 ports outputs except P1.6, P1.7
	P1OUT = 0x3E;       // All outputs high except P1.0. P1.6, P1.7 pulldown selected
	P1REN |= BIT6;      // Enable pulldown for P1.6
	P1IES &= ~(BIT6);   // Interrupt on low -> high
	P1IE |= BIT6;       // Enable interrupt for B1

	P2DIR = 0xDB;       // All P2 ports outputs except P2.3, P2.5
	P2OUT = 0x18;       // All outputs low except P2.3, P2.4. P2.2, P2.5 pulldown selected
	P2REN |= BIT2;      // Enable pulldown for P2.2
	P2IES &= ~(BIT2);   // Interrupt on low -> high
	P2IE |= BIT2;       // Enable interrupt for B2

	P3DIR = 0xDF;   // All P3 ports output except P3.5
	P3OUT = 0x0F;   // All outputs low, P3.5 pulldown selected

	P4DIR = BIT0;   // P4.0 is a output;
	P4OUT = 0x00;   // All outputs low, P4.0 pulldown selected

	PJDIR = 0x0F;   // PJ.0 - PJ.3 set as outputs
	PJOUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // PJ.0 - PJ.3 outputs low

	// For XT1
	// External clock (XT1) and system clocks setup
	PJSEL0 |= BIT4 + BIT5;


	CSCTL0_H = 0xA5;						// Unlock clock register
	//CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting (8)
	CSCTL1 |= DCOFSEL_3;
	CSCTL2 = SELA_0 + SELS_3 + SELM_3; 		//ACLK = XT1 and MCLK = DCO
	//CHANGE CSCTL3 DIVIDERS!
	//CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;
	CSCTL3 = DIVA_0 + DIVS_5 + DIVM_0;      // ACLK / 1, SMCLK / 32 (250 kHz), MCLK / 1 (8 MHz)
	CSCTL4 = XT1DRIVE_0;
	CSCTL4 &= ~XT1OFF;

	do
	{
		CSCTL5 &= ~XT1OFFG;		// Clear XT1 fault flag
		SFRIFG1 &= ~OFIFG;
	} while (SFRIFG1&OFIFG);
	CSCTL0_H = 0x01; // Lock clock register


	// RTC Setup
	RTCCTL01 |= RTCHOLD + RTCRDYIE; // Hold RTC, enable RTC ready interrupt (1 sec interval)
	RTCSEC = 0x0;                  // Set seconds to 0
	RTCMIN = 0x0;                  // Set minutes to 0
	RTCHOUR = 0x0;                 // Set hours to 0
	RTCCTL01 &= ~RTCHOLD;           //Release RTC hold


	// Timer for button debouncing
	TB1CCTL0 = CCIE;
    TB1CCR0 = 125;    // 2 milliseconds
	TB1CTL = TBSSEL_2 + MC_1 + ID_2 + TBCLR;


	// Timer used for long press
	/*
	TB0CCTL0 = CCIE;
	TB0CCR0 = 24576;    // 3 seconds

	TB0CTL = TBSSEL_1 + MC_1 + ID_2 + TBCLR;    // (250 kHz / 8 = 8192)
    */
	// Timer for sleeping between LED updating
	// @TODO Consider running this timer off SMCLK. That way, it is disabled when in sleep mode 3.0
    TA1CCTL0 = CCIE;
    TA1CCR0 = 126;                    // TASSEL_2 / ID (250 kHz / 4 == 62500) / 62500 = 1 Hz
    //TA1CCR0 = 1000;                                  // Used for blinking LEDs

    TA1CCR1 = 62500;                       // TASSEL_2 / ID (250 kHz / 4 == 62500) / 63 = ~ 1 kHz
                                        // This timer is used for updating LEDs
	TA1CTL = TASSEL_2 + MC_2 + ID_2 + TAIE + TACLR;

	// Turn off temp sensor
	REFCTL0 |= REFTCOFF;
	REFCTL0 &= ~OFIFG;

	__bis_SR_register(GIE); //Enable interrupts
}

// RTC_b ISR
#pragma vector=RTC_VECTOR
__interrupt void rtc_isr(void)
{
    switch (RTCIV)
    {
        case RTCIV_RTCRDYIFG:
        {
            if (set_new_time == 1)
            {
                // Change RTC time to requested new time
                RTCSEC = disp_seconds;
                RTCMIN = disp_minutes;
                RTCHOUR = disp_hours;
                set_new_time = 0;
                blink = 1;
                nextState = ShowTime;
            }



            rtc_seconds = RTCSEC;
            rtc_minutes = RTCMIN;
            rtc_hours = RTCHOUR;

            break;
        }
        default:
            rtc_seconds = 29;
            rtc_minutes = 29;
            rtc_hours = 8;
    }
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    // Shift value of each button
    button_shift_reg_1 = (button_shift_reg_1 << 1) | ((P1IN & BIT6) >> 6);
    button_shift_reg_2 = (button_shift_reg_2 << 1) | ((P2IN & BIT2) >> 2);
}

/*
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    if (button_shift_reg_1 == 0xFF) // The button has been held for 3 seconds
    {
        // Mode should be SetTime now
        if (nextState != SetTime)
        {
            nextState = SetTime;
            selectedRow = HOURS_ROW;
        }
    }
    TB0CTL = TBSSEL_0 + MC_1 + ID_2;    // (32.768 kHz / 4 = 8192)
}
*/

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
    // Toggle blink
    //blink = blink ^ 1;
    //TA1CCR0 += 62500;


    //int interruptSource = TA1IV;

    if (nextState != SetTime)
    {
        selectedRow = (selectedRow_t)((int)selectedRow + 1);
        if (selectedRow >= NO_ROW)
        {
            selectedRow = HOURS_ROW;
        }
    }

    TA1CCR0 += 126;
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR(void)
{
    //int interruptSource = TA1IV;
    switch (__even_in_range(TA1IV, 14))
    {
    case 0:
        //blink ^= 1;
        //TA1CCR1 += 62500;
        break;
    default:
        if (nextState == SetTime)
        {
            blink ^= 1;
        }

        if (button_shift_reg_1 == 0xFF) // The button has been held for 3 seconds
        {
            button1_hold_seconds ++;
        }
        else
        {
            button1_hold_seconds = 0;
        }

        if (button_shift_reg_2 == 0xFF)
        {
            button2_hold_seconds ++;
        }
        else
        {
            button2_hold_seconds = 0;
        }

        break;
    }
}


// Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

    int interruptSource = P1IV;
    //displayMode = DISPLAY_MODE_1;

    // Change mode to set time

}

// Port 2 ISR
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{

    int interruptSource = P2IV;



    //displayMode = DISPLAY_MODE_0;
}
