#include <msp430.h>
#include "Headers/head.h"
#include "Headers/led_controller.h"
#include "Headers/light_detect.h"
//#include <ctpl.h>

/*
 * main.c
 */
#define DISPLAY_MODE_0  0
#define DISPLAY_MODE_1  1
#define DISPLAY_MODE_2  2

volatile unsigned char gbl_nextState = 1;
volatile unsigned char gbl_blink_b = 1;						// Blink off = 0, blink on = 1
volatile unsigned int gbl_blink_count = 0;




volatile unsigned char gbl_selectedRow = 0;
volatile char rtc_seconds;
volatile char rtc_minutes;
volatile char rtc_hours;

volatile unsigned char gbl_setNewTime_b = 0;

volatile char displayMode = DISPLAY_MODE_2;

char gbl_disp_seconds;
char gbl_disp_minutes;
char gbl_disp_hours;

volatile unsigned char global_shift_reg_1 = 0;
volatile unsigned char global_shift_reg_2 = 0;

volatile unsigned char gb_button1_hold_seconds = 0;
volatile unsigned char gb_button2_hold_seconds = 0;

volatile unsigned char button1_pushed = 0;
volatile unsigned char button2_pushed = 0;

volatile unsigned char wakeTriggered = 0;
volatile unsigned char gbl_measureLight_b = 0;

unsigned long determineNextSleepTime(char secNow, char minNow, char hourNow, char sleepInterval, char sleepEnabled)
{
    if (sleepEnabled == 1)
    {
        unsigned long sleepTime = ((hourNow * 60) + minNow) * 60 + secNow + sleepInterval;
        if (sleepTime >= 86400ul)
        {
            return (sleepTime - 86400ul);
        }
        return sleepTime;
    }
    else
    {
        return 1000000ul;     // Impossible to reach sleep time
    }
}

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer

    rtc_seconds = 0;
    rtc_minutes = 0;
    rtc_hours = 0;

    initialize();
    measureLightInit();

    char disp_seconds;
    char disp_minutes;
    char disp_hours;

    char lastButton1State = 0;
    char lastButton2State = 0;

    unsigned char button_shift_reg_1 = 0;
    unsigned char button_shift_reg_2 = 0;
    unsigned char button1_hold_seconds = 0;
    unsigned char button2_hold_seconds = 0;

    char periodicMode = PERIODIC_MINUTE;
    RTCCTL1 |= periodicMode;
    RTCCTL0 |= RTCTEVIE;

    signed char sleepTimeInterval = 10;                       // Time to sleep after no input (valid values 0 - 59 seconds)
    unsigned long nextSleepTime = (unsigned long) sleepTimeInterval;             // Unit seconds (Hours * minutes * 60 + seconds)
    unsigned char sleepEnabled_b = 1;
    //unsigned int nextSleepTime = 0xFFFFFFFF;
    unsigned char selectedRow = 0;

    while(1)
    {
        // Get a local copy of all global variables for this current iteration to prevent memory faults during interrupts
        __disable_interrupt();
        if (wakeTriggered == 1)
        {

            wakeTriggered = 0;
            nextSleepTime = determineNextSleepTime(rtc_seconds, rtc_minutes, rtc_hours, sleepTimeInterval, sleepEnabled_b);
        }

        char temp_seconds = 0;
        char temp_minutes = 0;
        char temp_hours = 0;

        unsigned char measureLight_b = gbl_measureLight_b;
        unsigned char nextState = gbl_nextState;

        if ((RTCCTL01 & RTCRDY) != 0)
        {
            if (gbl_setNewTime_b == 1)
            {
                // Change RTC time to requested new time
                RTCSEC = gbl_disp_seconds;
                RTCMIN = gbl_disp_minutes;
                RTCHOUR = gbl_disp_hours;
                gbl_setNewTime_b = 0;
                gbl_blink_b = 1;
                nextState = ShowTime;
            }
            else
            {
                temp_seconds = RTCSEC;
                temp_minutes = RTCMIN;
                temp_hours = RTCHOUR;
                gbl_measureLight_b = 1;

                if ((RTCCTL01 & RTCRDY) != 0)
                {
                    rtc_seconds = temp_seconds;
                    rtc_minutes = temp_minutes;
                    rtc_hours = temp_hours;
                }
            }
        }

        if (nextState == ShowTime)
        {
            disp_seconds = rtc_seconds;
            disp_minutes = rtc_minutes;
            disp_hours = rtc_hours;
            selectedRow = gbl_selectedRow;
        }

        unsigned char blink_b = gbl_blink_b;
        unsigned char setNewTime_b = gbl_setNewTime_b;

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
                __disable_interrupt();
                gbl_measureLight_b = 0;
                __enable_interrupt();
                //unsigned int light = measureLightIntensity(disp_hours);
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
                    if (disp_hours >= 12)
                    {
                        disp_hours -= 12;
                    }
                    LED_SetCurrentLED(disp_hours, selectedRow);
                    break;
                default:
                    break;
                }
            }

            else if (displayMode == DISPLAY_MODE_1)
            {
                static char i = 0;

                if (i == 1)
                {
                    disp_seconds = disp_minutes;
                }
                if (i == 2)
                {
                    char hours = disp_hours;
                    if (hours >= 12)
                    {
                        hours = hours - 12;
                    }
                    disp_seconds = (5 * hours);
                    disp_seconds = (disp_seconds == 0) ? 0 : (disp_seconds);
                    disp_minutes = 5 * hours;
                    disp_minutes = (disp_minutes == 0) ? 0 : (disp_minutes);
                }

                if (selectedRow == SECONDS_ROW)
                {
                    i = i + 1;
                    if (i >= 3)
                    {
                        i = 0;
                    }
                }
                if (selectedRow == MINUTES_ROW)
                {
                    i = i + 1;
                    if (i >= 3)
                    {
                        i = 1;
                    }
                }

                switch (selectedRow)
                {
                case SECONDS_ROW:
                    LED_SetCurrentLED(disp_seconds, selectedRow);
                    break;

                case MINUTES_ROW:
                    LED_SetCurrentLED(disp_minutes, selectedRow);
                    break;

                case HOURS_ROW:
                    /*
                    if (disp_hours >= 12)
                    {
                        disp_hours -= 12;
                    }
                    */
                    LED_SetCurrentLED(disp_hours, selectedRow);
                    break;
                default:
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
                /*
                if ( secs_i > disp_seconds)
                {
                    secs_i = 0;
                }
                if ( mins_i > disp_minutes)
                {
                    mins_i = 0;
                }
                if ( hours_i > standardHours)
                {
                    hours_i = 0;
                }
                */
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
                        LED_SetCurrentLED(hours_i, selectedRow);
                        hours_i ++;
                    }
                    break;
                default:
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
                    break;
                }
            }
            else
            {
                reset_leds();
            }

            nextSleepTime = (unsigned int)0xFFFFFFF;
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
                    LED_SetCurrentLED(0, selectedRow);
                    break;
                }

                case PERIODIC_NOON:
                {
                    LED_SetCurrentLED(12, selectedRow);
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
                nextSleepTime = (unsigned int)100000;
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
                nextSleepTime = determineNextSleepTime(rtc_seconds, rtc_minutes, rtc_hours, sleepTimeInterval, sleepEnabled_b);
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
                    else if (sleepTimeInterval < 0)
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

                nextSleepTime = determineNextSleepTime(rtc_seconds, rtc_minutes, rtc_hours, sleepTimeInterval, sleepEnabled_b);
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

        //gb_button1_hold_seconds = button1_hold_seconds;
        //gb_button2_hold_seconds = button2_hold_seconds;

        gbl_disp_seconds = disp_seconds;
        gbl_disp_minutes = disp_minutes;
        gbl_disp_hours = disp_hours;

        //gbl_blink_b = blink_b;
        //gbl_selectedRow = selectedRow;

        gbl_setNewTime_b = setNewTime_b;

        gbl_nextState = nextState;

        __enable_interrupt();

        // Determine if we should sleep
        unsigned long currentTime = ((rtc_hours * 60) + rtc_minutes) * 60 + rtc_seconds;
        if ((currentTime > nextSleepTime) && (currentTime + nextSleepTime < 86400ul) && (sleepEnabled_b == 1))
        {
            reset_leds();
            nextSleepTime = 0xFFFFFFFul;                 // A value that's impossible to reach to prevent going right back to sleep before recalculating new sleep time
            __bis_SR_register(LPM4_bits + GIE);
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
	//RTCCTL01 |= RTCHOLD + RTCRDYIE; // Hold RTC, enable RTC ready interrupt (1 sec interval)
	RTCCTL01 |= RTCHOLD;
	RTCSEC = 0x0;                  // Set seconds to 0
	RTCMIN = 0;                  // Set minutes to 0
	RTCHOUR = 0;                 // Set hours to 0
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
    TA1CCR0 = 10;                    // TASSEL_2 / ID (250 kHz / 4 == 62500) / 62500 = 1 Hz
    //TA1CCR0 = 50;                                  // Used for blinking LEDs

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
        /*
        case RTCIV_RTCRDYIFG:
        {
            if (gbl_setNewTime_b == 1)
            {
                // Change RTC time to requested new time
                RTCSEC = gbl_disp_seconds;
                RTCMIN = gbl_disp_minutes;
                RTCHOUR = gbl_disp_hours;
                gbl_setNewTime_b = 0;
                gbl_blink_b = 1;
                gbl_nextState = ShowTime;
            }



            rtc_seconds = RTCSEC;
            rtc_minutes = RTCMIN;
            rtc_hours = RTCHOUR;
            gbl_measureLight_b = 1;

            break;
        }
        */
        case RTCIV_RTCTEVIFG:
        {
            wakeTriggered = 1;
            __bic_SR_register_on_exit(LPM4_bits);

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
    global_shift_reg_1 = (global_shift_reg_1 << 1) | ((P1IN & BIT6) >> 6);
    global_shift_reg_2 = (global_shift_reg_2 << 1) | ((P2IN & BIT2) >> 2);
}

/*
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    if (global_shift_reg_1 == 0xFF) // The button has been held for 3 seconds
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

    if (gbl_nextState != SetTime)
    {
        if (displayMode == DISPLAY_MODE_0 || displayMode == DISPLAY_MODE_1 )
        {
            gbl_selectedRow ++;
            if (gbl_selectedRow >= NO_ROW)
            {
                gbl_selectedRow = HOURS_ROW;
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
                    gbl_selectedRow = 0;
                    count = 0;
                }
            }
            if (gbl_selectedRow == MINUTES_ROW)
            {
                if (count < 2)
                {
                    count ++;
                }
                else
                {
                    gbl_selectedRow ++;
                    count = 0;
                }
            }
            else
            {
                gbl_selectedRow ++;
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
    button1_pushed = 1;
    __bic_SR_register_on_exit(LPM4_bits);
}

// Port 2 ISR
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{

    int interruptSource = P2IV;

    button2_pushed = 1;
    __bic_SR_register_on_exit(LPM4_bits);
    //displayMode = DISPLAY_MODE_0;
}
