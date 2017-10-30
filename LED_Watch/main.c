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

int nextState = 1;
int HMS_selection = 0; 				// 0 = Hours, 1 = Minutes, 2 = Seconds
int blink = 1;						// Blink off = 0, blink on = 1

typedef enum {
    HOURS_ROW = 0,
    MINUTES_ROW = 1,
    SECONDS_ROW = 2,
    NO_ROW = 3
} selectedRow_t;



selectedRow_t selectedRow = SECONDS_ROW;
int rtc_seconds = 0;
int rtc_minutes = 0;
int rtc_hours = 0;
int rtc_ready = 0;

char set_seconds = 0;
char set_minutes = 0;
char set_hours = 0;
char set_new_time = 0;

char displayMode = DISPLAY_MODE_0;
char disp_seconds = 0;
char disp_minutes = 0;
char disp_hours = 0;

unsigned char button_shift_reg_1 = 0;
unsigned char button_shift_reg_2 = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer

    initialize();

    int index = 0;
    while(1)
    {
    	switch(nextState)
    	{

    	case SetTime:
    	case ShowTime:

    	    reset_leds();
    	    // This is going to be annoying to read... not enough memory for a jump table
    	    switch (selectedRow)
    	    {
    	        case SECONDS_ROW:
    	            if (blink == 1)
    	            {
                        switch (disp_seconds)
                        {
                            case 0:
                                zero_seconds();
                                break;
                            case 1:
                                one_seconds();
                                break;

                            case 2:
                                two_seconds();
                                break;

                            case 3:
                                three_seconds();
                                break;

                            case 4:
                                four_seconds();
                                break;

                            case 5:
                                five_seconds();
                                break;

                            case 6:
                                six_seconds();
                                break;

                            case 7:
                                seven_seconds();
                                break;

                            case 8:
                                eight_seconds();
                                break;

                            case 9:
                                nine_seconds();
                                break;

                            case 10:
                                ten_seconds();
                                break;

                            case 11:
                                eleven_seconds();
                                break;

                            case 12:
                                twelve_seconds();
                                break;

                            case 13:
                                thirteen_seconds();
                                break;

                            case 14:
                                fourteen_seconds();
                                break;

                            case 15:
                                fifteen_seconds();
                                break;

                            case 16:
                                sixteen_seconds();
                                break;

                            case 17:
                                seventeen_seconds();
                                break;

                            case 18:
                                eighteen_seconds();
                                break;

                            case 19:
                                nineteen_seconds();
                                break;

                            case 20:
                                twenty_seconds();
                                break;

                            case 21:
                                twentyone_seconds();
                                break;

                            case 22:
                                twentytwo_seconds();
                                break;

                            case 23:
                                twentythree_seconds();
                                break;

                            case 24:
                                twentyfour_seconds();
                                break;

                            case 25:
                                twentyfive_seconds();
                                break;

                            case 26:
                                twentysix_seconds();
                                break;

                            case 27:
                                twentyseven_seconds();
                                break;

                            case 28:
                                twentyeight_seconds();
                                break;

                            case 29:
                                twentynine_seconds();
                                break;

                            case 30:
                                thirty_seconds();
                                break;

                            case 31:

                                thirtyone_seconds();
                                break;

                            case 32:
                                thirtytwo_seconds();
                                break;

                            case 33:
                                thirtythree_seconds();
                                break;

                            case 34:
                                thirtyfour_seconds();
                                break;

                            case 35:
                                thirtyfive_seconds();
                                break;

                            case 36:
                                thirtysix_seconds();
                                break;

                            case 37:
                                thirtyseven_seconds();
                                break;

                            case 38:
                                thirtyeight_seconds();
                                break;

                            case 39:
                                thirtynine_seconds();
                                break;

                            case 40:
                                forty_seconds();
                                break;

                            case 41:
                                fortyone_seconds();
                                break;

                            case 42:
                                fortytwo_seconds();
                                break;

                            case 43:
                                fortythree_seconds();
                                break;

                            case 44:
                                fortyfour_seconds();
                                break;

                            case 45:
                                fortyfive_seconds();
                                break;

                            case 46:
                                fortysix_seconds();
                                break;

                            case 47:
                                fortyseven_seconds();
                                break;

                            case 48:
                                fortyeight_seconds();
                                break;

                            case 49:
                                fortynine_seconds();
                                break;

                            case 50:
                                fifty_seconds();
                                break;

                            case 51:
                                fiftyone_seconds();
                                break;

                            case 52:
                                fiftytwo_seconds();
                                break;

                            case 53:
                                fiftythree_seconds();
                                break;

                            case 54:
                                fiftyfour_seconds();
                                break;

                            case 55:
                                fiftyfive_seconds();
                                break;

                            case 56:
                                fiftysix_seconds();
                                break;

                            case 57:
                                fiftyseven_seconds();
                                break;

                            case 58:
                                fiftyeight_seconds();
                                break;

                            case 59:
                                fiftynine_seconds();
                                break;
                        }
    	            }
                    break;

    	        case MINUTES_ROW:
    	            if (blink == 1)
    	            {
                        switch (disp_minutes)
                        {
                            case 0:
                                zero_minutes();
                                break;
                            case 1:
                                one_minutes();
                                break;

                            case 2:
                                two_minutes();
                                break;

                            case 3:
                                three_minutes();
                                break;

                            case 4:
                                four_minutes();
                                break;

                            case 5:
                                five_minutes();
                                break;

                            case 6:
                                six_minutes();
                                break;

                            case 7:
                                seven_minutes();
                                break;

                            case 8:
                                eight_minutes();
                                break;

                            case 9:
                                nine_minutes();
                                break;

                            case 10:
                                ten_minutes();
                                break;

                            case 11:
                                eleven_minutes();
                                break;

                            case 12:
                                twelve_minutes();
                                break;

                            case 13:
                                thirteen_minutes();
                                break;

                            case 14:
                                fourteen_minutes();
                                break;

                            case 15:
                                fifteen_minutes();
                                break;

                            case 16:
                                sixteen_minutes();
                                break;

                            case 17:
                                seventeen_minutes();
                                break;

                            case 18:
                                eighteen_minutes();
                                break;

                            case 19:
                                nineteen_minutes();
                                break;

                            case 20:
                                twenty_minutes();
                                break;

                            case 21:
                                twentyone_minutes();
                                break;

                            case 22:
                                twentytwo_minutes();
                                break;

                            case 23:
                                twentythree_minutes();
                                break;

                            case 24:
                                twentyfour_minutes();
                                break;

                            case 25:
                                twentyfive_minutes();
                                break;

                            case 26:
                                twentysix_minutes();
                                break;

                            case 27:
                                twentyseven_minutes();
                                break;

                            case 28:
                                twentyeight_minutes();
                                break;

                            case 29:
                                twentynine_minutes();
                                break;

                            case 30:
                                thirty_minutes();
                                break;

                            case 31:

                                thirtyone_minutes();
                                break;

                            case 32:
                                thirtytwo_minutes();
                                break;

                            case 33:
                                thirtythree_minutes();
                                break;

                            case 34:
                                thirtyfour_minutes();
                                break;

                            case 35:
                                thirtyfive_minutes();
                                break;

                            case 36:
                                thirtysix_minutes();
                                break;

                            case 37:
                                thirtyseven_minutes();
                                break;

                            case 38:
                                thirtyeight_minutes();
                                break;

                            case 39:
                                thirtynine_minutes();
                                break;

                            case 40:
                                forty_minutes();
                                break;

                            case 41:
                                fortyone_minutes();
                                break;

                            case 42:
                                fortytwo_minutes();
                                break;

                            case 43:
                                fortythree_minutes();
                                break;

                            case 44:
                                fortyfour_minutes();
                                break;

                            case 45:
                                fortyfive_minutes();
                                break;

                            case 46:
                                fortysix_minutes();
                                break;

                            case 47:
                                fortyseven_minutes();
                                break;

                            case 48:
                                fortyeight_minutes();
                                break;

                            case 49:
                                fortynine_minutes();
                                break;

                            case 50:
                                fifty_minutes();
                                break;

                            case 51:
                                fiftyone_minutes();
                                break;

                            case 52:
                                fiftytwo_minutes();
                                break;

                            case 53:
                                fiftythree_minutes();
                                break;

                            case 54:
                                fiftyfour_minutes();
                                break;

                            case 55:
                                fiftyfive_minutes();
                                break;

                            case 56:
                                fiftysix_minutes();
                                break;

                            case 57:
                                fiftyseven_minutes();
                                break;

                            case 58:
                                fiftyeight_minutes();
                                break;

                            case 59:
                                fiftynine_minutes();
                                break;
                        }
    	            }
    	            break;
    	        case HOURS_ROW:
    	            if (blink == 1)
    	            {
                        switch (disp_hours)
                        {
                            case 0:
                                zero_hours();
                                break;

                            case 1:
                                one_hours();
                                break;

                            case 2:
                                two_hours();
                                break;

                            case 3:
                                three_hours();
                                break;

                            case 4:
                                four_hours();
                                break;

                            case 5:
                                five_hours();
                                break;

                            case 6:
                                six_hours();
                                break;

                            case 7:
                                seven_hours();
                                break;

                            case 8:
                                eight_hours();
                                break;

                            case 9:
                                nine_hours();
                                break;

                            case 10:
                                ten_hours();
                                break;

                            case 11:
                                eleven_hours();
                                break;

                            case 12:
                                zero_hours();
                                break;

                            case 13:
                                one_hours();
                                break;

                            case 14:
                                two_hours();
                                break;

                            case 15:
                                three_hours();
                                break;

                            case 16:
                                four_hours();
                                break;

                            case 17:
                                five_hours();
                                break;

                            case 18:
                                six_hours();
                                break;

                            case 19:
                                seven_hours();
                                break;

                            case 20:
                                eight_hours();
                                break;

                            case 21:
                                nine_hours();
                                break;

                            case 22:
                                ten_hours();
                                break;

                            case 23:
                                eleven_hours();
                                break;
                        }
    	            }
    	            break;

    	    }
            if (index == 60)
            {
                index = 0;
            }
            //__bis_SR_register(LPM3_bits+GIE);

    		break;

    	/*
    	case SetTime:
    		switch(HMS_selection)
    		{
    		case HOURS:
    			// Blink current hour
    			if (blink == 1)
    			{
    			    switch (set_hours)
    			    {
                    case 0:
                        zero_hours();
                        break;

                    case 1:
                        one_hours();
                        break;

                    case 2:
                        two_hours();
                        break;

                    case 3:
                        three_hours();
                        break;

                    case 4:
                        four_hours();
                        break;

                    case 5:
                        five_hours();
                        break;

                    case 6:
                        six_hours();
                        break;

                    case 7:
                        seven_hours();
                        break;

                    case 8:
                        eight_hours();
                        break;

                    case 9:
                        nine_hours();
                        break;

                    case 10:
                        ten_hours();
                        break;

                    case 11:
                        eleven_hours();
                        break;

                    case 12:
                        zero_hours();
                        break;

                    case 13:
                        one_hours();
                        break;

                    case 14:
                        two_hours();
                        break;

                    case 15:
                        three_hours();
                        break;

                    case 16:
                        four_hours();
                        break;

                    case 17:
                        five_hours();
                        break;

                    case 18:
                        six_hours();
                        break;

                    case 19:
                        seven_hours();
                        break;

                    case 20:
                        eight_hours();
                        break;

                    case 21:
                        nine_hours();
                        break;

                    case 22:
                        ten_hours();
                        break;

                    case 23:
                        eleven_hours();
                        break;
    			    }
    			}
    			else
    			{
    			    reset_leds();
    			}

    			break;
    		case MINUTES:
    			// Blink current minute
                if (blink == 1)
                {
                    switch (set_minutes)
                    {
                        case 0:
                            zero_minutes();
                            break;
                        case 1:
                            one_minutes();
                            break;

                        case 2:
                            two_minutes();
                            break;

                        case 3:
                            three_minutes();
                            break;

                        case 4:
                            four_minutes();
                            break;

                        case 5:
                            five_minutes();
                            break;

                        case 6:
                            six_minutes();
                            break;

                        case 7:
                            seven_minutes();
                            break;

                        case 8:
                            eight_minutes();
                            break;

                        case 9:
                            nine_minutes();
                            break;

                        case 10:
                            ten_minutes();
                            break;

                        case 11:
                            eleven_minutes();
                            break;

                        case 12:
                            twelve_minutes();
                            break;

                        case 13:
                            thirteen_minutes();
                            break;

                        case 14:
                            fourteen_minutes();
                            break;

                        case 15:
                            fifteen_minutes();
                            break;

                        case 16:
                            sixteen_minutes();
                            break;

                        case 17:
                            seventeen_minutes();
                            break;

                        case 18:
                            eighteen_minutes();
                            break;

                        case 19:
                            nineteen_minutes();
                            break;

                        case 20:
                            twenty_minutes();
                            break;

                        case 21:
                            twentyone_minutes();
                            break;

                        case 22:
                            twentytwo_minutes();
                            break;

                        case 23:
                            twentythree_minutes();
                            break;

                        case 24:
                            twentyfour_minutes();
                            break;

                        case 25:
                            twentyfive_minutes();
                            break;

                        case 26:
                            twentysix_minutes();
                            break;

                        case 27:
                            twentyseven_minutes();
                            break;

                        case 28:
                            twentyeight_minutes();
                            break;

                        case 29:
                            twentynine_minutes();
                            break;

                        case 30:
                            thirty_minutes();
                            break;

                        case 31:

                            thirtyone_minutes();
                            break;

                        case 32:
                            thirtytwo_minutes();
                            break;

                        case 33:
                            thirtythree_minutes();
                            break;

                        case 34:
                            thirtyfour_minutes();
                            break;

                        case 35:
                            thirtyfive_minutes();
                            break;

                        case 36:
                            thirtysix_minutes();
                            break;

                        case 37:
                            thirtyseven_minutes();
                            break;

                        case 38:
                            thirtyeight_minutes();
                            break;

                        case 39:
                            thirtynine_minutes();
                            break;

                        case 40:
                            forty_minutes();
                            break;

                        case 41:
                            fortyone_minutes();
                            break;

                        case 42:
                            fortytwo_minutes();
                            break;

                        case 43:
                            fortythree_minutes();
                            break;

                        case 44:
                            fortyfour_minutes();
                            break;

                        case 45:
                            fortyfive_minutes();
                            break;

                        case 46:
                            fortysix_minutes();
                            break;

                        case 47:
                            fortyseven_minutes();
                            break;

                        case 48:
                            fortyeight_minutes();
                            break;

                        case 49:
                            fortynine_minutes();
                            break;

                        case 50:
                            fifty_minutes();
                            break;

                        case 51:
                            fiftyone_minutes();
                            break;

                        case 52:
                            fiftytwo_minutes();
                            break;

                        case 53:
                            fiftythree_minutes();
                            break;

                        case 54:
                            fiftyfour_minutes();
                            break;

                        case 55:
                            fiftyfive_minutes();
                            break;

                        case 56:
                            fiftysix_minutes();
                            break;

                        case 57:
                            fiftyseven_minutes();
                            break;

                        case 58:
                            fiftyeight_minutes();
                            break;

                        case 59:
                            fiftynine_minutes();
                            break;
                    }
                }
                else
                {
                    reset_leds();
                }

    			break;
    		case SECONDS:
    			// Blink current second
                if (blink == 1)
                {
                    switch (set_seconds)
                    {
                        case 0:
                            zero_seconds();
                            break;
                        case 1:
                            one_seconds();
                            break;

                        case 2:
                            two_seconds();
                            break;

                        case 3:
                            three_seconds();
                            break;

                        case 4:
                            four_seconds();
                            break;

                        case 5:
                            five_seconds();
                            break;

                        case 6:
                            six_seconds();
                            break;

                        case 7:
                            seven_seconds();
                            break;

                        case 8:
                            eight_seconds();
                            break;

                        case 9:
                            nine_seconds();
                            break;

                        case 10:
                            ten_seconds();
                            break;

                        case 11:
                            eleven_seconds();
                            break;

                        case 12:
                            twelve_seconds();
                            break;

                        case 13:
                            thirteen_seconds();
                            break;

                        case 14:
                            fourteen_seconds();
                            break;

                        case 15:
                            fifteen_seconds();
                            break;

                        case 16:
                            sixteen_seconds();
                            break;

                        case 17:
                            seventeen_seconds();
                            break;

                        case 18:
                            eighteen_seconds();
                            break;

                        case 19:
                            nineteen_seconds();
                            break;

                        case 20:
                            twenty_seconds();
                            break;

                        case 21:
                            twentyone_seconds();
                            break;

                        case 22:
                            twentytwo_seconds();
                            break;

                        case 23:
                            twentythree_seconds();
                            break;

                        case 24:
                            twentyfour_seconds();
                            break;

                        case 25:
                            twentyfive_seconds();
                            break;

                        case 26:
                            twentysix_seconds();
                            break;

                        case 27:
                            twentyseven_seconds();
                            break;

                        case 28:
                            twentyeight_seconds();
                            break;

                        case 29:
                            twentynine_seconds();
                            break;

                        case 30:
                            thirty_seconds();
                            break;

                        case 31:

                            thirtyone_seconds();
                            break;

                        case 32:
                            thirtytwo_seconds();
                            break;

                        case 33:
                            thirtythree_seconds();
                            break;

                        case 34:
                            thirtyfour_seconds();
                            break;

                        case 35:
                            thirtyfive_seconds();
                            break;

                        case 36:
                            thirtysix_seconds();
                            break;

                        case 37:
                            thirtyseven_seconds();
                            break;

                        case 38:
                            thirtyeight_seconds();
                            break;

                        case 39:
                            thirtynine_seconds();
                            break;

                        case 40:
                            forty_seconds();
                            break;

                        case 41:
                            fortyone_seconds();
                            break;

                        case 42:
                            fortytwo_seconds();
                            break;

                        case 43:
                            fortythree_seconds();
                            break;

                        case 44:
                            fortyfour_seconds();
                            break;

                        case 45:
                            fortyfive_seconds();
                            break;

                        case 46:
                            fortysix_seconds();
                            break;

                        case 47:
                            fortyseven_seconds();
                            break;

                        case 48:
                            fortyeight_seconds();
                            break;

                        case 49:
                            fortynine_seconds();
                            break;

                        case 50:
                            fifty_seconds();
                            break;

                        case 51:
                            fiftyone_seconds();
                            break;

                        case 52:
                            fiftytwo_seconds();
                            break;

                        case 53:
                            fiftythree_seconds();
                            break;

                        case 54:
                            fiftyfour_seconds();
                            break;

                        case 55:
                            fiftyfive_seconds();
                            break;

                        case 56:
                            fiftysix_seconds();
                            break;

                        case 57:
                            fiftyseven_seconds();
                            break;

                        case 58:
                            fiftyeight_seconds();
                            break;

                        case 59:
                            fiftynine_seconds();
                            break;
                    }
                }
                else
                {
                    reset_leds();
                }
    			break;
    		}
    		break;
    	 */
    	case Sleep:
    	    /*
    		ctpl_enterLpm35(CTPL_DISABLE_RESTORE_ON_RESET);
    		// On wakeup from 3.5, all registers have been cleared so reinitialize
    		initialize();
    		*/
    		break;
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


	// Timer setup (used for button qualification)
	TB0CCTL0 = CCIE;
    TB0CCR0 = 31250;    // 0.5 seconds
	TB0CTL = TASSEL_2 + MC_1 + ID_0; // Timer = ACLK, count up


	// Timer for sleeping between LED updating
	// @TODO Consider running this timer off SMCLK. That way, it is disabled when in sleep mode 3.0
    TA1CCTL0 = CCIE;
    TA1CCR0 = 126;                    // TASSEL_2 / ID (250 kHz / 4 == 62500) / 62500 = 1 Hz
                                        // Used for blinking LEDs

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
                RTCSEC = (int)set_seconds;
                RTCMIN = (int)set_minutes;
                RTCHOUR = (int)set_hours;
                set_new_time = 0;
                blink = 1;
                nextState = ShowTime;
            }

            rtc_seconds = RTCSEC;
            rtc_minutes = RTCMIN;
            rtc_hours = RTCHOUR;
            rtc_ready = 1;

            break;
        }
    }
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    // Shift value of each button

    button_shift_reg_1 = (button_shift_reg_1 << 1) + ((P1IN & BIT6) >> 6);
    button_shift_reg_2 = (button_shift_reg_2 << 1) + ((P2IN & BIT2) >> 2);

    if (button_shift_reg_1 & 0x01)
    {
        if (nextState == SetTime)
        {
            if (selectedRow == 2)
            {
                // Change RTC values
                set_new_time = 1;
            }
            else
            {
                selectedRow = selectedRow + 1;
            }
        }
    }
    if (button_shift_reg_1 == 0x3F) // The button has been held for 3 seconds
    {
        // Mode should be SetTime now
        if (nextState != SetTime)
        {
            nextState = SetTime;
            selectedRow = HOURS_ROW;
        }
    }

    if (button_shift_reg_2 & 0x01) // The button has been held for 3 seconds
    {
        if (nextState == SetTime)
        {
            switch (selectedRow)
            {
                case HOURS_ROW:
                {
                    if (set_hours == 11)
                    {
                        set_hours = 0;
                        disp_hours = 0;
                    }
                    else
                    {
                        set_hours ++;
                        disp_hours = set_hours;
                    }
                    break;
                }
                case MINUTES_ROW:
                {
                    if (set_minutes == 59)
                    {
                        set_minutes = 0;
                        disp_minutes = 0;
                    }
                    else
                    {
                        set_minutes ++;
                        disp_minutes = set_minutes;
                    }
                    break;
                }
                case SECONDS_ROW:
                {
                    if (set_seconds == 59)
                    {
                        set_seconds = 0;
                        disp_seconds = 0;
                    }
                    else
                    {
                        set_seconds ++;
                        disp_seconds = set_seconds;
                    }
                    break;
                }
            }
        }
    }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
    // Toggle blink
    //blink = blink ^ 1;
    //TA1CCR0 += 62500;


    //int interruptSource = TA1IV;

    if (nextState != SetTime)
    {
        selectedRow = selectedRow + 1;
        if (selectedRow == NO_ROW)
        {
            selectedRow = HOURS_ROW;
        }

        if (displayMode == DISPLAY_MODE_0)
        {
            disp_seconds = rtc_seconds;
            disp_minutes = rtc_minutes;
            disp_hours = rtc_hours;
        }

        else if (displayMode == DISPLAY_MODE_1)
        {
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

            if (selectedRow == HOURS_ROW)
            {
                i = i + 1;
                if (i >= 3)
                {
                    i = 0;
                }
            }
        }
    }

    TA1CCR0 += 63;
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
        break;
    }



    /*
    int interruptSource = TA1IV;

    selectedRow = selectedRow + 1;
    if (selectedRow == NO_ROW)
    {
        selectedRow = SECONDS_ROW;
    }

    if (displayMode == DISPLAY_MODE_0)
    {
        disp_seconds = rtc_seconds;
        disp_minutes = rtc_minutes;
        disp_hours = rtc_hours;
    }

    else if (displayMode == DISPLAY_MODE_1)
    {
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

        if (selectedRow == HOURS_ROW)
        {
            i = i + 1;
            if (i >= 3)
            {
                i = 0;
            }
        }
    }
    */

}


// Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    /*
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
		switch(HMS_selection)
		{
		case HOURS:
		{
			HMS_selection = MINUTES;
			break;
		}
		case MINUTES:
		{
			HMS_selection = SECONDS;
			break;
		}
		case SECONDS:
			// Exit out of SetTime, go into ShowTime
			nextState = ShowTime;
			// Reset HMS for next entry
			HMS_selection = HOURS;
			break;
		}
		break;
	}
	}
	P2IFG &= ~BIT6;
	P2IE = 0; 			// Disable interrupt from P2 and P3 and wait for standby clock to elapse before enabling again
	P3IE = 0;
	TA0CTL |= MC_1; 	// Enable debounce timer
	*/

    int interruptSource = P1IV;
    //displayMode = DISPLAY_MODE_1;

    // Change mode to set time

}

// Port 2 ISR
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    /*
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
		switch(HMS_selection)
		{
		case HOURS:
		{
			// Wait until RTC can be modified safely
			while(!RTCRDY);
			// Increment hour
			if(RTCHOUR < 23)
			{
				RTCHOUR = RTCHOUR + 1;
			}
			else
			{
				RTCHOUR = 0;
			}
			break;
		}

		case MINUTES:
		{
			// Wait until RTC can be modified safely
			while(!RTCRDY);
			// Increment minute
			if(RTCMIN < 59)
			{
				RTCMIN = RTCMIN + 1;
			}
			else
			{
				RTCMIN = 0;
			}
			break;
		}
		case SECONDS:
		{
			// Wait until RTC can be modified safely
			while(!RTCRDY);
			// Reset seconds
			RTCSEC = 0;
			break;
		}
	}
	}
	P3IFG &= ~BIT6;
	P2IE = 0;	// Disable interrupt from P2 and P3 and wait for standby clock to elapse before enabling again
	P3IE = 0;
	TA0CTL |= MC_1;		// Enable debounce timer

    }*/
    int interruptSource = P2IV;



    //displayMode = DISPLAY_MODE_0;
}
