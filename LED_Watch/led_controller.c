/*
 * led_controller.c
 *
 *  Created on: Aug 21, 2015
 *      Author: Sean
 */

#include <msp430.h>
#include "Headers\led_controller.h"


// LED Lookup Tables
//
// Stores function pointers
//
// LED Seconds Lookup
// 		Index 0-59 		-> Seconds
// LED Minutes Lookup
// 		Index 0-59 		-> Minutes
// LED Hours Lookup
// 		Index 120-131	-> Hours


void(*led_seconds[60])();

void(*led_minutes[60])();

void(*led_hours[24])();

void initialize_leds()
{
	// Intialize LED lookup tables

	led_seconds[0] = zero_seconds;
	led_seconds[1] = one_seconds;
	led_seconds[2] = two_seconds;
	led_seconds[3] = three_seconds;
	led_seconds[4] = four_seconds;
	led_seconds[5] = five_seconds;
	led_seconds[6] = six_seconds;
	led_seconds[7] = seven_seconds;
	led_seconds[8] = eight_seconds;
	led_seconds[9] = nine_seconds;
	led_seconds[10] = ten_seconds;
	led_seconds[11] = eleven_seconds;
	led_seconds[12] = twelve_seconds;
	led_seconds[13] = thirteen_seconds;
	led_seconds[14] = fourteen_seconds;
	led_seconds[15] = fifteen_seconds;
	led_seconds[16] = sixteen_seconds;
	led_seconds[17] = seventeen_seconds;
	led_seconds[18] = eighteen_seconds;
	led_seconds[19] = nineteen_seconds;
	led_seconds[20] = twenty_seconds;
	led_seconds[21] = twentyone_seconds;
	led_seconds[22] = twentytwo_seconds;
	led_seconds[23] = twentythree_seconds;
	led_seconds[24] = twentyfour_seconds;
	led_seconds[25] = twentyfive_seconds;
	led_seconds[26] = twentysix_seconds;
	led_seconds[27] = twentyseven_seconds;
	led_seconds[28] = twentyeight_seconds;
	led_seconds[29] = twentynine_seconds;
	led_seconds[30] = thirty_seconds;
	led_seconds[31] = thirtyone_seconds;
	led_seconds[32] = thirtytwo_seconds;
	led_seconds[33] = thirtythree_seconds;
	led_seconds[34] = thirtyfour_seconds;
	led_seconds[35] = thirtyfive_seconds;
	led_seconds[36] = thirtysix_seconds;
	led_seconds[37] = thirtyseven_seconds;
	led_seconds[38] = thirtyeight_seconds;
	led_seconds[39] = thirtynine_seconds;
	led_seconds[40] = forty_seconds;
	led_seconds[41] = fortyone_seconds;
	led_seconds[42] = fortytwo_seconds;
	led_seconds[43] = fortythree_seconds;
	led_seconds[44] = fortyfour_seconds;
	led_seconds[45] = fortyfive_seconds;
	led_seconds[46] = fortysix_seconds;
	led_seconds[47] = fortyseven_seconds;
	led_seconds[48] = fortyeight_seconds;
	led_seconds[49] = fortynine_seconds;
	led_seconds[50] = fifty_seconds;
	led_seconds[51] = fiftyone_seconds;
	led_seconds[52] = fiftytwo_seconds;
	led_seconds[53] = fiftythree_seconds;
	led_seconds[54] = fiftyfour_seconds;
	led_seconds[55] = fiftyfive_seconds;
	led_seconds[56] = fiftysix_seconds;
	led_seconds[57] = fiftyseven_seconds;
	led_seconds[58] = fiftyeight_seconds;
	led_seconds[59] = fiftynine_seconds;


	led_minutes[0] = zero_minutes;
	led_minutes[1] = one_minutes;
	led_minutes[2] = two_minutes;
	led_minutes[3] = three_minutes;
	led_minutes[4] = four_minutes;
	led_minutes[5] = five_minutes;
	led_minutes[6] = six_minutes;
	led_minutes[7] = seven_minutes;
	led_minutes[8] = eight_minutes;
	led_minutes[9] = nine_minutes;
	led_minutes[10] = ten_minutes;
	led_minutes[11] = eleven_minutes;
	led_minutes[12] = twelve_minutes;
	led_minutes[13] = thirteen_minutes;
	led_minutes[14] = fourteen_minutes;
	led_minutes[15] = fifteen_minutes;
	led_minutes[16] = sixteen_minutes;
	led_minutes[17] = seventeen_minutes;
	led_minutes[18] = eighteen_minutes;
	led_minutes[19] = nineteen_minutes;
	led_minutes[20] = twenty_minutes;
	led_minutes[21] = twentyone_minutes;
	led_minutes[22] = twentytwo_minutes;
	led_minutes[23] = twentythree_minutes;
	led_minutes[24] = twentyfour_minutes;
	led_minutes[25] = twentyfive_minutes;
	led_minutes[26] = twentysix_minutes;
	led_minutes[27] = twentyseven_minutes;
	led_minutes[28] = twentyeight_minutes;
	led_minutes[29] = twentynine_minutes;
	led_minutes[30] = thirty_minutes;
	led_minutes[31] = thirtyone_minutes;
	led_minutes[32] = thirtytwo_minutes;
	led_minutes[33] = thirtythree_minutes;
	led_minutes[34] = thirtyfour_minutes;
	led_minutes[35] = thirtyfive_minutes;
	led_minutes[36] = thirtysix_minutes;
	led_minutes[37] = thirtyseven_minutes;
	led_minutes[38] = thirtyeight_minutes;
	led_minutes[39] = thirtynine_minutes;
	led_minutes[40] = forty_minutes;
	led_minutes[41] = fortyone_minutes;
	led_minutes[42] = fortytwo_minutes;
	led_minutes[43] = fortythree_minutes;
	led_minutes[44] = fortyfour_minutes;
	led_minutes[45] = fortyfive_minutes;
	led_minutes[46] = fortysix_minutes;
	led_minutes[47] = fortyseven_minutes;
	led_minutes[48] = fortyeight_minutes;
	led_minutes[49] = fortynine_minutes;
	led_minutes[50] = fifty_minutes;
	led_minutes[51] = fiftyone_minutes;
	led_minutes[52] = fiftytwo_minutes;
	led_minutes[53] = fiftythree_minutes;
	led_minutes[54] = fiftyfour_minutes;
	led_minutes[55] = fiftyfive_minutes;
	led_minutes[56] = fiftysix_minutes;
	led_minutes[57] = fiftyseven_minutes;
	led_minutes[58] = fiftyeight_minutes;

	led_hours[0] = zero_hours;
	led_hours[1] = one_hours;
	led_hours[2] = two_hours;
	led_hours[3] = three_hours;
	led_hours[4] = four_hours;
	led_hours[5] = five_hours;
	led_hours[6] = six_hours;
	led_hours[7] = seven_hours;
	led_hours[8] = eight_hours;
	led_hours[9] = nine_hours;
	led_hours[10] = ten_hours;
	led_hours[11] = eleven_hours;
	led_hours[12] = zero_hours;
	led_hours[13] = one_hours;
	led_hours[14] = two_hours;
	led_hours[15] = three_hours;
	led_hours[16] = four_hours;
	led_hours[17] = five_hours;
	led_hours[18] = six_hours;
	led_hours[19] = seven_hours;
	led_hours[20] = eight_hours;
	led_hours[21] = nine_hours;
	led_hours[22] = ten_hours;
	led_hours[23] = eleven_hours;

}

void reset_leds()
{
	P1OUT = P1_OFF;
	P2OUT = P2_OFF;
	P3OUT = P3_OFF;
	P4OUT = P4_OFF;
	PJOUT = PJ_OFF;
}

// LED pin "high" functions

// SECONDS
void zero_seconds()
{
	//Row 1, Column 1
	P1OUT = P1_OFF;
	P2OUT = P2_OFF ^ BIT3;
	P3OUT = P3_OFF;
	P4OUT = P4_OFF;
	PJOUT = PJ_OFF | BIT0;
	return;
}
void one_seconds()
{
	//Row 9, Column 12
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT3) | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void two_seconds()
{
	//Row 9, Column 11
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void three_seconds()
{
	//Row 9, Column 10
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT3) | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void four_seconds()
{
	//Row 9, Column 9
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT3) | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void five_seconds()
{
	//Row 9, Column 8
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void six_seconds()
{
	//Row 9, Column 7
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void seven_seconds()
{
	//Row 9, Column 6
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void eight_seconds()
{
	//Row 9, Column 5
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void nine_seconds()
{
	//Row 9, Column 4
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void ten_seconds()
{
	//Row 9, Column 3
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void eleven_seconds()
{
	//Row 9, Column 2
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void twelve_seconds()
{
	//Row 9, Column 1
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void thirteen_seconds()
{
	//Row 7, Column 12
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF ^ BIT3;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fourteen_seconds()
{
	//Row 7, Column 11
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT3) | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fifteen_seconds()
{
	//Row 7, Column 10
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void sixteen_seconds()
{
	//Row 7, Column 9
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void seventeen_seconds()
{
	//Row 7, Column 8
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void eighteen_seconds()
{
	//Row 7, Column 7
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void nineteen_seconds()
{
	//Row 7, Column 6
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void twenty_seconds()
{
	//Row 7, Column 5
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentyone_seconds()
{
	//Row 7, Column 4
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
    return;
}
void twentytwo_seconds()
{
	//Row 7, Column 3
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void twentythree_seconds()
{
	//Row 7, Column 2
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void twentyfour_seconds()
{
	//Row 7, Column 1
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void twentyfive_seconds()
{
	//Row 5, Column 12
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentysix_seconds()
{
	//Row 5, Column 11
    P1OUT = P1_OFF ^ BIT4;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentyseven_seconds()
{
	//Row 5, Column 10
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentyeight_seconds()
{
	//Row 5, Column 9
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentynine_seconds()
{
	//Row 5, Column 8
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirty_seconds()
{
	//Row 5, Column 7
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
    return;
}
void thirtyone_seconds()
{
	//Row 5, Column 6
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void thirtytwo_seconds()
{
	//Row 5, Column 5
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtythree_seconds()
{
	//Row 5, Column 4
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtyfour_seconds()
{
	//Row 5, Column 3
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void thirtyfive_seconds()
{
	//Row 5, Column 2
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void thirtysix_seconds()
{
	//Row 5, Column 1
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void thirtyseven_seconds()
{
	//Row 3, Column 12
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtyeight_seconds()
{
	//Row 3, Column 11
    P1OUT = P1_OFF ^ BIT2;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtynine_seconds()
{
	//Row 3, Column 10
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT2) | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void forty_seconds()
{
	//Row 3, Column 9
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT2) | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortyone_seconds()
{
	//Row 3, Column 8
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortytwo_seconds()
{
	//Row 3, Column 7
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void fortythree_seconds()
{
	//Row 3, Column 6
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void fortyfour_seconds()
{
	//Row 3, Column 5
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortyfive_seconds()
{
	//Row 3, Column 4
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortysix_seconds()
{
	//Row 3, Column 3
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void fortyseven_seconds()
{
	//Row 3, Column 2
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void fortyeight_seconds()
{
	//Row 3, Column 1
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void fortynine_seconds()
{
	//Row 1, Column 12
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF ^ BIT2;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fifty_seconds()
{
	//Row 1, Column 11
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT2) | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyone_seconds()
{
	//Row 1, Column 10
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftytwo_seconds()
{
	//Row 1, Column 9
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;	return;
}
void fiftythree_seconds()
{
	//Row 1, Column 8
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT3) | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyfour_seconds()
{
	//Row 1, Column 7
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void fiftyfive_seconds()
{
	//Row 1, Column 6
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void fiftysix_seconds()
{
	//Row 1, Column 5
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT3) | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyseven_seconds()
{
	//Row 1, Column 4
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT3) | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyeight_seconds()
{
	//Row 1, Column 3
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
    return;
}
void fiftynine_seconds()
{
	//Row 1, Column 2
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT3;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}


// MINUTES
void zero_minutes()
{
	//Row 2, Column 1
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}
void one_minutes()
{
	//Row 10, Column 12
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT4) | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void two_minutes()
{
	//Row 10, Column 11
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void three_minutes()
{
	//Row 10, Column 10
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT0) | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
    return;
}
void four_minutes()
{
	//Row 10, Column 9
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT0) | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void five_minutes()
{
	//Row 10, Column 8
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void six_minutes()
{
	//Row 10, Column 7
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
    return;
}
void seven_minutes()
{
	//Row 10, Column 6
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void eight_minutes()
{
	//Row 10, Column 5
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void nine_minutes()
{
	//Row 10, Column 4
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void ten_minutes()
{
	//Row 10, Column 3
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void eleven_minutes()
{
	//Row 10, Column 2
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void twelve_minutes()
{
	//Row 10, Column 1
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void thirteen_minutes()
{
	//Row 8, Column 12
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF ^ BIT0;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fourteen_minutes()
{
	//Row 8, Column 11
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT0) | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fifteen_minutes()
{
	//Row 8, Column 10
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void sixteen_minutes()
{
	//Row 8, Column 9
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void seventeen_minutes()
{
	//Row 8, Column 8
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void eighteen_minutes()
{
	//Row 8, Column 7
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void nineteen_minutes()
{
	//Row 8, Column 6
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void twenty_minutes()
{
	//Row 8, Column 5
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentyone_minutes()
{
	//Row 8, Column 4
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentytwo_minutes()
{
	//Row 8, Column 3
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void twentythree_minutes()
{
	//Row 8, Column 2
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void twentyfour_minutes()
{
	//Row 8, Column 1
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void twentyfive_minutes()
{
	//Row 6, Column 12
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentysix_minutes()
{
	//Row 6, Column 11
    P1OUT = P1_OFF ^ BIT5;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentyseven_minutes()
{
	//Row 6, Column 10
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentyeight_minutes()
{
	//Row 6, Column 9
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void twentynine_minutes()
{
	//Row 6, Column 8
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirty_minutes()
{
	//Row 6, Column 7
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void thirtyone_minutes()
{
	//Row 6, Column 6
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void thirtytwo_minutes()
{
	//Row 6, Column 5
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtythree_minutes()
{
	//Row 6, Column 4
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtyfour_minutes()
{
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void thirtyfive_minutes()
{
	//Row 6, Column 2
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void thirtysix_minutes()
{
	//Row 6, Column 1
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void thirtyseven_minutes()
{
	//Row 4, Column 12
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtyeight_minutes()
{
	//Row 4, Column 11
    P1OUT = P1_OFF ^ BIT3;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void thirtynine_minutes()
{
	//Row 4, Column 10
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT1) | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void forty_minutes()
{
	//Row 4, Column 9
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT1) | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortyone_minutes()
{
	//Row 4, Column 8
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortytwo_minutes()
{
	//Row 4, Column 7
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void fortythree_minutes()
{
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void fortyfour_minutes()
{
	//Row 4, Column 5
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortyfive_minutes()
{
	//Row 4, Column 4
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fortysix_minutes()
{
	//Row 4, Column 3
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void fortyseven_minutes()
{
	//Row 4, Column 2
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void fortyeight_minutes()
{
	//Row 4, Column 1
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}

void fortynine_minutes()
{
	//Row 2, Column 12
    P1OUT = P1_OFF;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF ^ BIT1;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fifty_minutes()
{
	//Row 2, Column 11
    P1OUT = P1_OFF;
    P2OUT = P2_OFF;
    P3OUT = (P3_OFF ^ BIT1) | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyone_minutes()
{
	//Row 2, Column 10
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;	return;
}
void fiftytwo_minutes()
{
	//Row 2, Column 9
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF | BIT4;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftythree_minutes()
{
	//Row 2, Column 8
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT4) | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyfour_minutes()
{
	//Row 2, Column 7
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void fiftyfive_minutes()
{
	//Row 2, Column 6
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void fiftysix_minutes()
{
	//Row 2, Column 5
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT4) | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void fiftyseven_minutes()
{
	//Row 2, Column 4
    P1OUT = P1_OFF;
    P2OUT = (P2_OFF ^ BIT4) | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
    return;
}
void fiftyeight_minutes()
{
	//Row 2, Column 3
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void fiftynine_minutes()
{
	//Row 2, Column 2
    P1OUT = P1_OFF;
    P2OUT = P2_OFF ^ BIT4;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}

void zero_hours()
{
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
    return;
}

void one_hours()
{
	//Row 11, Column 12
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF | BIT7;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void two_hours()
{
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT7;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void three_hours()
{
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF | BIT6;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void four_hours()
{
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF | BIT6;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void five_hours()
{
	//Row 11, Column 8
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF | BIT0;
    PJOUT = PJ_OFF;
	return;
}
void six_hours()
{
	//Row 11, Column 7
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT1;
	return;
}
void seven_hours()
{
	//Row 11, Column 6
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF | BIT1;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void eight_hours()
{
	//Row 11, Column 5
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF | BIT0;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF;
	return;
}
void nine_hours()
{
	//Row 11, Column 4
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT3;
	return;
}
void ten_hours()
{
	//Row 11, Column 3
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT2;
	return;
}
void eleven_hours()
{
	//Row 11, Column 2
    P1OUT = P1_OFF ^ BIT1;
    P2OUT = P2_OFF;
    P3OUT = P3_OFF;
    P4OUT = P4_OFF;
    PJOUT = PJ_OFF | BIT0;
	return;
}
