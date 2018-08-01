#include <msp430.h>
#include "Headers/head.h"
#include "Headers/led_controller.h"
#include "Headers/light_detect.h"
//#include <ctpl.h>

/*
 * main.c
 */

/*
 * Display mode 0 lights up only 1 LED in each hour, minute, second ring. Lowest power consumption
 */
#define DISPLAY_MODE_0  0

/*
 * Display mode 1 lights up the LEDs so that it appears the hour value has long clock leg (the minute
 * and seconds LED in the same position as the hour LED are all lit up), the minute has a medium
 * length clock leg (minute and second LED are lit up depending on which minute is set) and seconds
 * has a short clock leg
 */
#define DISPLAY_MODE_1  1

/*
 * Display mode 2 lights up all LEDs in the ring up to the current hour, minute, and second
 */
#define DISPLAY_MODE_2  2

/*
 * Must store these values within FRAM as all contents in RAM reset in LPM3.5.
 */
/////////////////////////////////////////////////////////////////////////////////////
#pragma PERSISTENT(displayMode)
volatile char displayMode = DISPLAY_MODE_0;                 // Current display mode

#pragma PERSISTENT(periodicMode)
char periodicMode = PERIODIC_MINUTE;                    // RTC Periodic Alarm Mode

#pragma PERSISTENT(sleepTimeInterval)
unsigned char sleepTimeInterval = 10;                       // Time to sleep after no input (valid values 0 - 59 seconds)
/////////////////////////////////////////////////////////////////////////////////////


volatile unsigned char dim = 1;
volatile unsigned int dim_count = 0;
volatile unsigned int gbl_dim_amount = 0;

volatile unsigned char gbl_nextState = 1;					// Global copy of nextState for interrupts
volatile unsigned char gbl_blink_b = 1;						// Blink off = 0, blink on = 1
volatile unsigned int gbl_blink_count = 0;					// Used for setting blink frequency
volatile unsigned char gbl_selectedRow = 0;					// Global copy of selectedRow for interrupts

volatile unsigned char global_shift_reg_1 = 0;				// Global shift register for button 1
volatile unsigned char global_shift_reg_2 = 0;				// Global shift register for button 2

volatile unsigned char gb_button1_hold_seconds = 0;			// Global time button 1 has been held down
volatile unsigned char gb_button2_hold_seconds = 0;			// Global time button 2 has been held down

volatile unsigned char wakeTriggered = 0;                        // If RTC time event caused wake

volatile unsigned char gbl_measureLight_b = 1;


void EnterLPM35(void);
void ExitLPM35(char rtcPeriodicMode);
void GPIO_LPM_ENTER();
void GPIO_LPM_EXIT();

char determineNextSleepTime(char secNow, char sleepInterval, char sleepEnabled)
{
    if (sleepEnabled == 1 && sleepInterval < 60)
    {
        char sleepTime = secNow + sleepInterval;
        if (sleepTime >= 60)
        {
            return (sleepTime - 60);
        }
        return sleepTime;
    }
    else
    {
        return 60;     // Impossible to reach sleep time
    }
}

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer

	/* 
	 * The RTC S/M/H variables are used because the RTCMIN, RTCSEC, RTCHOUR registers do not hold valid 
	 * values when they are being updated by the RTC hardware module. Therefore, the value in each 
	 * register is copied only when the values are valid (RTCRDY == 1).
	 */
    char rtc_seconds = 0;									// Current RTC seconds
    char rtc_minutes = 0;									// Current RTC minutes
    char rtc_hours = 0;										// Current RTC hours

	unsigned char measureLight_b = 0;					    // Should light measure start
	unsigned char dim_amount = 0;

	/*
	 * If we are exiting from LPM3.5, only configure modules outside of RTC. Otherwise, this is a fresh
	 * boot and we need to initialize everything.
	 */
	if (SYSRSTIV == SYSRSTIV_LPM5WU)
	{
	    ExitLPM35(periodicMode);
	}
	else
	{
	    initialize(periodicMode);
	}

	/*
	 * Initialize code responsible for ADC in order to measure light using an LED.
	 */
    measureLightInit();

	/*
	 * The display S/M/H variables are used to determine which LED should be displayed in the
	 * seconds, minutes, and hours row of LEDs.
	 */
    char disp_seconds;
    char disp_minutes;
    char disp_hours;

	/*
	 * Used to store last button state. Used for button press qualification
	 */
    char lastButton1State = 0;
    char lastButton2State = 0;

	/*
	 * Shift register for button debouncing.
	 */
    unsigned char button_shift_reg_1 = 0;
    unsigned char button_shift_reg_2 = 0;
    unsigned char button1_hold_seconds = 0;
    unsigned char button2_hold_seconds = 0;

    unsigned char nextSleepTime = sleepTimeInterval;             // Unit seconds (Hours * minutes * 60 + seconds)
    unsigned char sleepEnabled_b = 1;

    unsigned char setNewTime_b = 0;

    unsigned char selectedRow = 0;                              // Selects the hours LED rings, minutes ring, or seconds ring

    while(1)
    {
        char temp_seconds = 0;
        char temp_minutes = 0;
        char temp_hours = 0;

        //unsigned char measureLight_b = gbl_measureLight_b;
		
        __disable_interrupt();
		
        unsigned char nextState = gbl_nextState;
        measureLight_b = gbl_measureLight_b;
        gbl_measureLight_b = 0;

		// Update time from RTC registers if they are currently valid
        if ((RTCCTL01 & RTCRDY) != 0)
        {
			// If we have finished setting time, update RTC registers
            if (setNewTime_b == 1)
            {
                // Change RTC time to requested new time
                RTCSEC = disp_seconds;
                RTCMIN = disp_minutes;
                RTCHOUR = disp_hours;
                setNewTime_b = 0;
                gbl_blink_b = 1;
                nextState = ShowTime;
            }
            else
            {
                temp_seconds = RTCSEC;
                temp_minutes = RTCMIN;
                temp_hours = RTCHOUR;
                //measureLight_b = 1;

				/*
				 * Ensure that the RTCRDY bit is still set. Could end up in a situation where RTCRDY was
				 * set but by the time we get to reading the registers, the registers are no longer valid.
				 * If no longer valid, don't update our current copy of the time
				 */
                if ((RTCCTL01 & RTCRDY) != 0)
                {
                    rtc_seconds = temp_seconds;
                    rtc_minutes = temp_minutes;
                    rtc_hours = temp_hours;

                    if (wakeTriggered == 1)
                    {
                        wakeTriggered = 0;
                        nextSleepTime = determineNextSleepTime(rtc_seconds, sleepTimeInterval, sleepEnabled_b);
                    }
                }
            }
        }



		// If our nextState is to ShowTime, update disp copies to reflect real time.
        if (nextState == ShowTime)
        {
            disp_seconds = rtc_seconds;
            disp_minutes = rtc_minutes;
            disp_hours = rtc_hours;
            selectedRow = gbl_selectedRow;
        }

		// Get a local copy of all global variables for this current iteration to prevent memory faults during interrupts
		
        unsigned char blink_b = gbl_blink_b;

        button_shift_reg_1 = global_shift_reg_1;
        button_shift_reg_2 = global_shift_reg_2;

        button1_hold_seconds = gb_button1_hold_seconds;
        button2_hold_seconds = gb_button2_hold_seconds;

        __enable_interrupt();


        // Handle how the LEDs are displayed
        if (nextState == ShowTime)
        {
            if (measureLight_b == 1)
            {
                measureLight_b = 0;
                dim_amount = (unsigned char)measureLightIntensity(disp_hours);
            }

            if (displayMode == DISPLAY_MODE_0)
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
                    reset_leds();
                    break;
                }
            }

            else if (displayMode == DISPLAY_MODE_1)
            {
                static char secs_i = 0;
                static char mins_i = 0;

                char hours = disp_hours;
                if (hours >= 12)
                {
                    hours = hours - 12;
                }

                if (selectedRow == SECONDS_ROW)
                {
                    static char i = 0;
                    if (i == 0)
                    {
                        secs_i = disp_minutes;
                    }
                    else if (i == 1)
                    {
                        secs_i = (5 * hours);
                        secs_i = (secs_i == 0) ? 0 : (secs_i);
                    }
                    else
                    {
                        secs_i = disp_seconds;
                    }

                    i = i + 1;
                    if (i >= 3)
                    {
                        i = 0;
                    }
                }

                if (selectedRow == MINUTES_ROW)
                {
                    static char i = 0;
                    if (i == 0)
                    {
                        mins_i = disp_minutes;
                    }
                    else if (i == 1)
                    {
                        mins_i = (5 * hours);
                        mins_i = (mins_i == 0) ? 0 : (mins_i);
                    }

                    i ++;
                    if (i >= 2)
                    {
                        i = 0;
                    }
                }


                switch (selectedRow)
                {
                case SECONDS_ROW:
                    LED_SetCurrentLED(secs_i, selectedRow);
                    break;

                case MINUTES_ROW:
                    LED_SetCurrentLED(mins_i, selectedRow);
                    break;

                case HOURS_ROW:
                    LED_SetCurrentLED(disp_hours, selectedRow);
                    break;
                default:
                    reset_leds();
                    break;
                }
            }
            else
            {
                static char secs_i = 0;
                static char mins_i = 0;
                static char hours_i = 0;

                char standardHours = disp_hours;
                if (standardHours >= 12)
                {
                    standardHours -= 12;
                }

                switch (selectedRow)
                {
                case SECONDS_ROW:
                    if ( secs_i > disp_seconds)
                    {
                        if (secs_i > 59)
                        {
                            secs_i = 0;
                        }
                        else
                        {
                            secs_i ++;
                            reset_leds();
                        }
                    }
                    else
                    {
                        LED_SetCurrentLED(secs_i, selectedRow);
                        secs_i ++;
                    }

                    break;

                case MINUTES_ROW:
                    if ( mins_i > disp_minutes)
                    {
                        if (mins_i > 59)
                        {
                            mins_i = 0;
                        }
                        else
                        {
                            mins_i ++;
                            reset_leds();
                        }
                    }
                    else
                    {
                        LED_SetCurrentLED(mins_i, selectedRow);
                        mins_i ++;
                    }
                    break;

                case HOURS_ROW:

                    if ( hours_i > standardHours)
                    {
                        if (hours_i > 11)
                        {
                            hours_i = 0;
                        }
                        else
                        {
                            hours_i ++;
                            reset_leds();
                        }
                    }
                    else
                    {
                        if (disp_hours > 11)
                        {
                            LED_SetCurrentLED(hours_i + 12, selectedRow);
                        }
                        else
                        {
                            LED_SetCurrentLED(hours_i, selectedRow);
                        }
                        hours_i ++;
                    }
                    break;
                default:
                    reset_leds();
                    break;
                }
            }
        }


        else if ((nextState == SetTime) || (nextState == SetAlarm))
        {
            if (blink_b == 1)
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
                    reset_leds();
                    break;
                }
            }
            else
            {
                reset_leds();
            }

            nextSleepTime = 60;
        }

        else if (nextState == SetPeriodicAlarm)
        {
            switch (periodicMode)
            {
                case PERIODIC_MINUTE:
                {
                    LED_SetCurrentLED(1, MINUTES_ROW);
                    break;
                }
                case PERIODIC_HOUR:
                {
                    LED_SetCurrentLED(1, HOURS_ROW);
                    break;
                }
                case PERIODIC_MIDNIGHT:
                {
                    LED_SetCurrentLED(0, HOURS_ROW);
                    break;
                }

                case PERIODIC_NOON:
                {
                    LED_SetCurrentLED(12, HOURS_ROW);
                    break;
                }
                default:    // PERIODIC_NONE
                {
                    reset_leds();
                    break;
                }
            }

            __enable_interrupt();
        }
        else if (nextState == SetSleepTime)
        {
            LED_SetCurrentLED(sleepTimeInterval, SECONDS_ROW);
        }

        // If both buttons are pushed simutaneously
        if (button_shift_reg_1 == 0xFF && button_shift_reg_2 == 0xFF)
        {
            // If we are currently in ShowTime mode and we hold both buttons for two seconds, go into SetSleepTime mode
            if ((nextState == ShowTime) && (button1_hold_seconds >= 2) && (button2_hold_seconds >= 2))
            {
                nextState = SetSleepTime;
                __disable_interrupt();
                gb_button1_hold_seconds = 0;
                gb_button2_hold_seconds = 0;
                __enable_interrupt();
                nextSleepTime = 60;
            }
            else if ((nextState == SetSleepTime) && (button1_hold_seconds >= 2) && (button2_hold_seconds >= 2))     // How to exit SetSleepTime mode
            {
                nextState = ShowTime;
				
                __disable_interrupt();
                gb_button1_hold_seconds = 0;
                gb_button2_hold_seconds = 0;
                __enable_interrupt();
            }
        }
        else
        {
            // If button 1 has been confirmed as being pushed
            if (button_shift_reg_1 == 0xFF)
            {
                nextSleepTime = determineNextSleepTime(rtc_seconds, sleepTimeInterval, sleepEnabled_b);
                //nextSleepTime = 0xFFFFFFFF;
                if ((nextState == SetTime && lastButton1State == 0) || (nextState == SetTime && button1_hold_seconds >= 2))
                {
                    if (selectedRow >= 2)
                    {
                        // Change RTC values
                        setNewTime_b = 1;
                        //TA1CCTL0 = CCIE;
                        //nextState = ShowTime;
                        //blink = 1;
                    }
                    else
                    {
                        selectedRow ++;
                    }
                    __disable_interrupt();
                    gb_button1_hold_seconds = 0;
                    gbl_blink_count = 0;
                    gbl_blink_b = 1;
                    __enable_interrupt();

                }
                else if (nextState == ShowTime && button1_hold_seconds >= 3)
                {
                    nextState = SetTime;
                    //TA1CCTL0 &= ~CCIE;
                    selectedRow = 0;
                    __disable_interrupt();
                    gb_button1_hold_seconds = 0;
                    __enable_interrupt();
                }
                else if ((nextState == SetPeriodicAlarm && lastButton1State == 0))
                {
                    nextState = ShowTime;
                    if (periodicMode != PERIODIC_NONE)
                    {
                        RTCCTL1 |= periodicMode;
                        RTCCTL0 |= RTCTEVIE;
                    }
                    else
                    {
                        RTCCTL0 &= ~RTCTEVIE;
                    }
                }
                else if ((nextState == SetSleepTime && lastButton1State == 0) || (nextState == SetSleepTime && button1_hold_seconds >= 1))
                {
                    sleepTimeInterval --;
                    if (sleepTimeInterval == 0)    // Restrict sleepTimeInterval to be between 0 - 60 seconds
                    {
                        sleepEnabled_b = 0;
                    }
                    else if (sleepTimeInterval >= 60)
                    {
                        sleepTimeInterval = 59;
                        sleepEnabled_b = 1;
                    }
                    __disable_interrupt();
                    gb_button1_hold_seconds = 0;
                    __enable_interrupt();
                }

                lastButton1State = 1;
            }
            else if (button_shift_reg_1 == 0x00)
            {
                lastButton1State = 0;
            }

            if (button_shift_reg_2 == 0xFF)
            {

                nextSleepTime = determineNextSleepTime(rtc_seconds, sleepTimeInterval, sleepEnabled_b);
                //nextSleepTime = 0xFFFFFFFF;
                if ((nextState == SetTime && lastButton2State == 0) || (nextState == SetTime && button2_hold_seconds >= 1))
                {
                    switch (selectedRow)
                    {
                        case HOURS_ROW:
                        {
                            if (disp_hours == 23)
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
                    blink_b = 1;

                    __disable_interrupt();
                    gb_button2_hold_seconds = 0;
                    gbl_blink_count = 0;
                    gbl_blink_b = 1;
                    __enable_interrupt();
                }
                else if ((nextState == ShowTime && lastButton2State == 0))
                {
                    if (displayMode == DISPLAY_MODE_0)
                    {
                        displayMode = DISPLAY_MODE_1;
                    }
                    else if (displayMode == DISPLAY_MODE_1)
                    {
                        displayMode = DISPLAY_MODE_2;
                    }
                    else
                    {
                        displayMode = DISPLAY_MODE_0;
                    }

                }
                else if ((nextState == ShowTime && button2_hold_seconds >= 3))
                {
                    nextState = SetPeriodicAlarm;
                }
                else if ((nextState == SetPeriodicAlarm && lastButton2State == 0))
                {
                    periodicMode ++;
                    if (periodicMode > PERIODIC_NONE)
                    {
                        periodicMode = PERIODIC_MINUTE;
                    }
                }
                else if ((nextState == SetSleepTime && lastButton2State == 0) || (nextState == SetSleepTime && button2_hold_seconds >= 1))
                {
                    sleepTimeInterval ++;
                    if (sleepTimeInterval == 60)    // Restrict sleepTimeInterval to be between 0 - 60 seconds
                    {
                        sleepTimeInterval = 0;
                        sleepEnabled_b = 0;
                    }
                    else if (sleepTimeInterval > 0)
                    {
                        sleepEnabled_b = 1;
                    }
                    __disable_interrupt();
                    gb_button2_hold_seconds = 0;
                    __enable_interrupt();
                }

                lastButton2State = 1;
            }
            else if (button_shift_reg_2 == 0x00)
            {
                lastButton2State = 0;
            }
        }

        __disable_interrupt();

        //gbl_blink_b = blink_b;
        //gbl_selectedRow = selectedRow;


        gbl_nextState = nextState;
        gbl_dim_amount = dim_amount;

        __enable_interrupt();

        // Determine if we should sleep
        if ((rtc_seconds == nextSleepTime) && (sleepEnabled_b == 1))
        {
            reset_leds();
            nextSleepTime = 60;                 // A value that's impossible to reach to prevent going right back to sleep before recalculating new sleep time
            EnterLPM35();
        }
    }
}

void initialize(char rtcPeriodicMode)
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
	//RTCCTL01 |= RTCHOLD + RTCRDYIE; // Hold RTC, enable RTC ready interrupt (1 sec interval)
    RTCCTL01 |= RTCHOLD;

    RTCSEC = 0;                  // Set seconds to 0
    RTCMIN = 0;                  // Set minutes to 0
    RTCHOUR = 0;                 // Set hours to 0

    RTCCTL01 &= ~RTCHOLD;           //Release RTC hold

    RTCCTL1 |= rtcPeriodicMode;
    RTCCTL0 |= RTCTEVIE;                                    // Enable RTC wake event interrupt

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
    TA1CCR0 = 10;                    // TASSEL_2 / ID (250 kHz / 4 == 62500) / 62500 = 1 Hz
    //TA1CCR0 = 50;                                  // Used for blinking LEDs

    TA1CCR1 = 62500;                       // TASSEL_2 / ID (250 kHz / 4 == 62500) / 63 = ~ 1 kHz
                                        // This timer is used for updating LEDs
	TA1CTL = TASSEL_2 + MC_2 + ID_2 + TAIE + TACLR;

	// Turn off temp sensor
	REFCTL0 |= REFTCOFF;
	REFCTL0 &= ~OFIFG;

	displayMode = DISPLAY_MODE_0;

	__bis_SR_register(GIE); //Enable interrupts
}

#pragma FUNC_ALWAYS_INLINE(GPIO_LPM_ENTER)
void GPIO_LPM_ENTER()
{
    P1DIR = 0;
    P1OUT = 0;
    P1REN = 0xFF;

    P2DIR = 0;
    P2OUT = 0;
    P2REN = 0xFF;

    P3DIR = 0;
    P3OUT = 0;
    P3REN = 0xFF;

    P4DIR = 0;
    P4OUT = 0;
    P4REN = 0xFF;

    PJDIR = 0;
    PJOUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);
    PJREN = 0x0F;
}

#pragma FUNC_ALWAYS_INLINE(GPIO_LPM_EXIT)
void GPIO_LPM_EXIT()
{
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
}

void EnterLPM35(void)
{
    TB1CTL =  TBSSEL_2 + MC_0 + ID_2 + TBCLR;
    TA1CTL = TASSEL_2 + MC_0 + ID_2 + TAIE + TACLR;

    PMMCTL0_H = PMMPW_H;
    PMMCTL0_L |= PMMREGOFF;

    GPIO_LPM_ENTER();

    __bis_SR_register(LPM3_bits + GIE);
    __no_operation();
}

void ExitLPM35(char rtcPeriodicMode)
{
    GPIO_LPM_EXIT();

    PJDIR = 0x0F;   // PJ.0 - PJ.3 set as outputs
    PJOUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // PJ.0 - PJ.3 outputs low

    // For XT1
    // External clock (XT1) and system clocks setup
    PJSEL0 |= BIT4 + BIT5;

    PM5CTL0 &= ~LOCKLPM5;

    // RTC Setup
    //RTCCTL01 |= RTCHOLD + RTCRDYIE; // Hold RTC, enable RTC ready interrupt (1 sec interval)
    RTCCTL01 |= RTCHOLD;

    RTCCTL01 &= ~RTCHOLD;           //Release RTC hold

    // Timer for button debouncing
    TB1CCTL0 = CCIE;
    TB1CCR0 = 125;    // 2 milliseconds
    TB1CTL = TBSSEL_2 + MC_1 + ID_2 + TBCLR;


    // Timer used for long press

    TA1CCTL0 = CCIE;
    TA1CCR0 = 10;                    // TASSEL_2 / ID (250 kHz / 4 == 62500) / 62500 = 1 Hz
    //TA1CCR0 = 50;                                  // Used for blinking LEDs

    TA1CCR1 = 62500;                       // TASSEL_2 / ID (250 kHz / 4 == 62500) / 63 = ~ 1 kHz
                                        // This timer is used for updating LEDs
    TA1CTL = TASSEL_2 + MC_2 + ID_2 + TAIE + TACLR;

    CSCTL0_H = 0xA5;                        // Unlock clock register
    CSCTL1 |= DCOFSEL_3;
    CSCTL2 = SELA_0 + SELS_3 + SELM_3;      //ACLK = XT1 and MCLK = DCO
    //CHANGE CSCTL3 DIVIDERS!
    CSCTL3 = DIVA_0 + DIVS_5 + DIVM_0;      // ACLK / 1, SMCLK / 32 (250 kHz), MCLK / 1 (8 MHz)
    CSCTL4 = XT1DRIVE_0;
    CSCTL4 &= ~XT1OFF;

    do
    {
        CSCTL5 &= ~XT1OFFG;     // Clear XT1 fault flag
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1&OFIFG);
    CSCTL0_H = 0x01; // Lock clock register

    if (rtcPeriodicMode != PERIODIC_NONE)
    {
        RTCCTL1 |= periodicMode;
        RTCCTL0 |= RTCTEVIE;
    }
    else
    {
        RTCCTL0 &= ~RTCTEVIE;
    }

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
        case RTCIV_RTCTEVIFG:
        {
            wakeTriggered = 1;


            break;
        }
        default:
			break;
    }
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    // Shift value of each button
    global_shift_reg_1 = (global_shift_reg_1 << 1) | ((P1IN & BIT6) >> 6);
    global_shift_reg_2 = (global_shift_reg_2 << 1) | ((P2IN & BIT2) >> 2);
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
    if (gbl_nextState != SetTime)
    {
        //if (displayMode == DISPLAY_MODE_0 || displayMode == DISPLAY_MODE_1 )
        if (displayMode == DISPLAY_MODE_0)
        {
            if (dim == 1)
            {
                if (gbl_selectedRow < NO_ROW)
                {
                    gbl_selectedRow += NO_ROW;
                    dim_count = 0;
                }
                else if (dim_count >= gbl_dim_amount) // 30 max
                //else if (dim_count >= 0)
                {
                    gbl_selectedRow -= NO_ROW;
                    gbl_selectedRow ++;

                    if (gbl_selectedRow == NO_ROW)
                    {
                        gbl_selectedRow = HOURS_ROW;
                    }
                }
                else
                {
                    dim_count ++;
                }
            }
            else
            {
                gbl_selectedRow ++;
                if (gbl_selectedRow >= NO_ROW)
                {
                    gbl_selectedRow = HOURS_ROW;
                }
            }
        }
        else if (displayMode == DISPLAY_MODE_1)
        {
            static unsigned char count = 0;
            if (gbl_selectedRow == SECONDS_ROW)
            {
                if (count < 3)
                {
                    count ++;
                }
                else
                {
                    gbl_selectedRow += NO_ROW;
                    count = 0;
                }
            }
            else if (gbl_selectedRow == MINUTES_ROW)
            {
                if (count < 2)
                {
                    count ++;
                }
                else
                {
                    gbl_selectedRow += NO_ROW;
                    count = 0;
                }
            }
            else if (gbl_selectedRow == HOURS_ROW)
            {
                gbl_selectedRow += NO_ROW;
            }
            else
            {
                if (dim_count >= gbl_dim_amount)
                {
                    dim_count = 0;
                    gbl_selectedRow -= NO_ROW;
                    gbl_selectedRow ++;

                    if (gbl_selectedRow == NO_ROW)
                    {
                        gbl_selectedRow = HOURS_ROW;
                    }
                }
                else
                {
                    dim_count ++;
                }
            }

        }
        else
        {
            static unsigned char count = 0;
            if (gbl_selectedRow == SECONDS_ROW || gbl_selectedRow == MINUTES_ROW)
            {
                if (count < 5)
                {
                    count ++;
                }
                else
                {
                    if (gbl_selectedRow == 2)
                    {
                        gbl_selectedRow = 0;
                    }
                    else
                    {
                        gbl_selectedRow ++;
                    }
                    count = 0;
                }
            }
            else if (gbl_selectedRow == HOURS_ROW)
            {
                gbl_selectedRow ++;
            }
            else
            {
                gbl_selectedRow = 0;
            }
        }
    }
    else
    {
        gbl_blink_count ++;
        if (gbl_blink_count > 12500)
        {
            gbl_blink_b ^= 1;
            gbl_blink_count = 0;
        }
    }

    TA1CCR0 += 10;
    //TA1CCR0 += 50;
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
        if (gbl_nextState == SetTime)
        {
            //gbl_blink_b ^= 1;
        }

        if (global_shift_reg_1 == 0xFF) // The button has been held for 3 seconds
        {
            gb_button1_hold_seconds ++;
        }
        else
        {
            gb_button1_hold_seconds = 0;
        }

        if (global_shift_reg_2 == 0xFF)
        {
            gb_button2_hold_seconds ++;
        }
        else
        {
            gb_button2_hold_seconds = 0;
        }

        gbl_measureLight_b = 1;

        break;
    }
}


// Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    int interruptSource = P1IV;
}

// Port 2 ISR
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    int interruptSource = P2IV;
}
