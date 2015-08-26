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

void(*led_hours[12])();

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
	led_seconds[40] = fourty_seconds;
	led_seconds[41] = fourtyone_seconds;
	led_seconds[42] = fourtytwo_seconds;
	led_seconds[43] = fourtythree_seconds;
	led_seconds[44] = fourtyfour_seconds;
	led_seconds[45] = fourtyfive_seconds;
	led_seconds[46] = fourtysix_seconds;
	led_seconds[47] = fourtyseven_seconds;
	led_seconds[48] = fourtyeight_seconds;
	led_seconds[49] = fourtynine_seconds;
	led_seconds[50] = fifty_seconds;
	led_seconds[51] = fiftyone_seconds;
	led_seconds[52] = fiftytwo_seconds;
	led_seconds[53] = fiftythree_seconds;
	led_seconds[54] = fiftyfour_seconds;
	led_seconds[55] = fiftyfive_seconds;
	led_seconds[56] = fiftysix_seconds;
	led_seconds[57] = fiftyseven_seconds;
	led_seconds[58] = fiftyeight_seconds;

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
	led_minutes[40] = fourty_minutes;
	led_minutes[41] = fourtyone_minutes;
	led_minutes[42] = fourtytwo_minutes;
	led_minutes[43] = fourtythree_minutes;
	led_minutes[44] = fourtyfour_minutes;
	led_minutes[45] = fourtyfive_minutes;
	led_minutes[46] = fourtysix_minutes;
	led_minutes[47] = fourtyseven_minutes;
	led_minutes[48] = fourtyeight_minutes;
	led_minutes[49] = fourtynine_minutes;
	led_minutes[50] = fifty_minutes;
	led_minutes[51] = fiftyone_minutes;
	led_minutes[52] = fiftytwo_minutes;
	led_minutes[53] = fiftythree_minutes;
	led_minutes[54] = fiftyfour_minutes;
	led_minutes[55] = fiftyfive_minutes;
	led_minutes[56] = fiftysix_minutes;
	led_minutes[57] = fiftyseven_minutes;
	led_minutes[58] = fiftyeight_minutes;

	led_hours[0] = one_hours;
	led_hours[1] = two_hours;
	led_hours[2] = three_hours;
	led_hours[3] = four_hours;
	led_hours[4] = five_hours;
	led_hours[5] = six_hours;
	led_hours[6] = seven_hours;
	led_hours[7] = eight_hours;
	led_hours[8] = nine_hours;
	led_hours[9] = ten_hours;
	led_hours[10] = eleven_hours;
	led_hours[11] = twelve_hours;
}

void reset_leds()
{
	P1OUT = 0x08; // P1.3 high, all else low
	P2OUT = 0xB4; // P2.2, P2.4, P2.5, P2.7 high, all else low
	P3OUT = 0x9B; // P3.1, P3.2, P3.3, P3.4, P3.7 high, all else low
	P4OUT = BIT1; // P4.1 high
}

// LED pin "high" functions

// SECONDS
void zero_seconds()
{
	//Row 1, Column 1
	P1OUT = (P1_OFF ^ BIT3);
	P4OUT = (P4_OFF | BIT0);

	return;
}
void one_seconds()
{
	//Row 9, Column 12
	//P2OUT ^= BIT2;
	//P2OUT |= BIT0;
	P2OUT = (P2_OFF ^ BIT2) | BIT0;
	return;
}
void two_seconds()
{
	//Row 9, Column 11
	//P2OUT ^= BIT2;
	//P2OUT |= BIT1;
	P2OUT = (P2_OFF ^ BIT2) | BIT1;
	return;
}
void three_seconds()
{
	//Row 9, Column 10
	//P2OUT ^= BIT2;
	//P3OUT |= BIT5;
	P2OUT = (P2_OFF ^ BIT2);
	P3OUT = (P3_OFF | BIT5);
	return;
}
void four_seconds()
{
	//Row 9, Column 9
	P2OUT = (P2_OFF ^ BIT2);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void five_seconds()
{
	//Row 9, Column 8
	P2OUT = (P2_OFF ^ BIT2);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void six_seconds()
{
	//Row 9, Column 7
	P2OUT = (P2_OFF ^ BIT2) | BIT3;
	return;
}
void seven_seconds()
{
	//Row 9, Column 6
	P2OUT = (P2_OFF ^ BIT2);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void eight_seconds()
{
	//Row 9, Column 5
	P2OUT = (P2_OFF ^ BIT2);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void nine_seconds()
{
	//Row 9, Column 4
	P2OUT = (P2_OFF ^ BIT2);
	P3OUT = (P3_OFF | BIT2);
	return;
}
void ten_seconds()
{
	//Row 9, Column 3
	P2OUT = (P2_OFF ^ BIT2);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void eleven_seconds()
{
	//Row 9, Column 2
	P2OUT = (P2_OFF ^ BIT2);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void twelve_seconds()
{
	//Row 9, Column 1
	P2OUT = (P2_OFF ^ BIT2);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void thirteen_seconds()
{
	//Row 7, Column 12
	P3OUT = (P3_OFF ^ BIT7);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void fourteen_seconds()
{
	//Row 7, Column 11
	P3OUT = (P3_OFF ^ BIT7);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void fifteen_seconds()
{
	//Row 7, Column 10
	P3OUT = (P3_OFF ^ BIT7) | BIT5;
	return;
}
void sixteen_seconds()
{
	//Row 7, Column 9
	P3OUT = (P3_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void seventeen_seconds()
{
	//Row 7, Column 8
	P3OUT = (P3_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void eighteen_seconds()
{
	//Row 7, Column 7
	P3OUT = (P3_OFF ^ BIT7);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void nineteen_seconds()
{
	//Row 7, Column 6
	P3OUT = (P3_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void twenty_seconds()
{
	//Row 7, Column 5
	P3OUT = (P3_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void twentyone_seconds()
{
	//Row 7, Column 4
	P3OUT = (P3_OFF ^ BIT7) | BIT2;
	return;
}
void twentytwo_seconds()
{
	//Row 7, Column 3
	P3OUT = (P3_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void twentythree_seconds()
{
	//Row 7, Column 2
	P3OUT = (P3_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void twentyfour_seconds()
{
	//Row 7, Column 1
	P3OUT = (P3_OFF ^ BIT7);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void twentyfive_seconds()
{
	//Row 5, Column 12
	P2OUT = (P2_OFF ^ BIT7) | BIT0;
	return;
}
void twentysix_seconds()
{
	//Row 5, Column 11
	P2OUT = (P2_OFF ^ BIT7) | BIT1;
	return;
}
void twentyseven_seconds()
{
	//Row 5, Column 10
	P2OUT = (P2_OFF ^ BIT7);
	P3OUT = (P3_OFF | BIT5);
	return;
}
void twentyeight_seconds()
{
	//Row 5, Column 9
	P2OUT = (P2_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void twentynine_seconds()
{
	//Row 5, Column 8
	P2OUT = (P2_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void thirty_seconds()
{
	//Row 5, Column 7
	P2OUT = (P2_OFF ^ BIT7) | BIT3;
	return;
}
void thirtyone_seconds()
{
	//Row 5, Column 6
	P2OUT = (P2_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void thirtytwo_seconds()
{
	//Row 5, Column 5
	P2OUT = (P2_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void thirtythree_seconds()
{
	//Row 5, Column 4
	P2OUT = (P2_OFF ^ BIT7);
	P3OUT = (P3_OFF | BIT2);
	return;
}
void thirtyfour_seconds()
{
	//Row 5, Column 3
	P2OUT = (P2_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void thirtyfive_seconds()
{
	//Row 5, Column 2
	P2OUT = (P2_OFF ^ BIT7);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void thirtysix_seconds()
{
	//Row 5, Column 1
	P2OUT = (P2_OFF ^ BIT7);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void thirtyseven_seconds()
{
	//Row 3, Column 12
	P3OUT = (P3_OFF ^ BIT0);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void thirtyeight_seconds()
{
	//Row 3, Column 11
	P3OUT = (P3_OFF ^ BIT0);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void thirtynine_seconds()
{
	//Row 3, Column 10
	P3OUT = (P3_OFF ^ BIT0) | BIT5;
	return;
}
void fourty_seconds()
{
	//Row 3, Column 9
	P3OUT = (P3_OFF ^ BIT0);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void fourtyone_seconds()
{
	//Row 3, Column 8
	P3OUT = (P3_OFF ^ BIT0);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void fourtytwo_seconds()
{
	//Row 3, Column 7
	P3OUT = (P3_OFF ^ BIT0);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void fourtythree_seconds()
{
	//Row 3, Column 6
	P3OUT = (P3_OFF ^ BIT0);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void fourtyfour_seconds()
{
	//Row 3, Column 5
	P3OUT = (P3_OFF ^ BIT0);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void fourtyfive_seconds()
{
	//Row 3, Column 4
	P3OUT = (P3_OFF ^ BIT0) | BIT2;
	return;
}
void fourtysix_seconds()
{
	//Row 3, Column 3
	P3OUT = (P3_OFF ^ BIT0);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void fourtyseven_seconds()
{
	//Row 3, Column 2
	P3OUT = (P3_OFF ^ BIT0);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void fourtyeight_seconds()
{
	//Row 3, Column 1
	P3OUT = (P3_OFF ^ BIT0);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void fourtynine_seconds()
{
	//Row 1, Column 12
	P1OUT = (P1_OFF ^ BIT3);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void fifty_seconds()
{
	//Row 1, Column 11
	P1OUT = (P1_OFF ^ BIT3);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void fiftyone_seconds()
{
	//Row 1, Column 10
	P1OUT = (P1_OFF ^ BIT3);
	P3OUT = (P3_OFF | BIT5);
	return;
}
void fiftytwo_seconds()
{
	//Row 1, Column 9
	P1OUT = (P1_OFF ^ BIT3) | BIT7;
	return;
}
void fiftythree_seconds()
{
	//Row 1, Column 8
	P1OUT = (P1_OFF ^ BIT3) | BIT6;
	return;
}
void fiftyfour_seconds()
{
	//Row 1, Column 7
	P1OUT = (P1_OFF ^ BIT3);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void fiftyfive_seconds()
{
	//Row 1, Column 6
	P1OUT = (P1_OFF ^ BIT3) | BIT2;
	return;
}
void fiftysix_seconds()
{
	//Row 1, Column 5
	P1OUT = (P1_OFF ^ BIT3) | BIT1;
	return;
}
void fiftyseven_seconds()
{
	//Row 1, Column 4
	P1OUT = (P1_OFF ^ BIT3);
	P3OUT = (P3_OFF | BIT2);
	return;
}
void fiftyeight_seconds()
{
	//Row 1, Column 3
	P1OUT = (P1_OFF ^ BIT3) | BIT4;
	return;
}
void fiftynine_seconds()
{
	//Row 1, Column 2
	P1OUT = (P1_OFF ^ BIT3) | BIT5;
	return;
}


// MINUTES
void zero_minutes()
{
	//Row 2, Column 1
	P3OUT = (P3_OFF ^ BIT1);
	P4OUT = (P4_OFF | BIT0);
	return;
}
void one_minutes()
{
	//Row 10, Column 12
	P2OUT = (P2_OFF ^ BIT5) | BIT0;
	return;
}
void two_minutes()
{
	//Row 10, Column 11
	P2OUT = (P2_OFF ^ BIT5) | BIT1;
	return;
}
void three_minutes()
{
	//Row 10, Column 10
	P2OUT = (P2_OFF ^ BIT5) | BIT5;
	return;
}
void four_minutes()
{
	//Row 10, Column 9
	P2OUT = (P2_OFF ^ BIT5);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void five_minutes()
{
	//Row 10, Column 8
	P2OUT = (P2_OFF ^ BIT5);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void six_minutes()
{
	//Row 10, Column 7
	P2OUT = (P2_OFF ^ BIT5) | BIT3;
	return;
}
void seven_minutes()
{
	//Row 10, Column 6
	P2OUT = (P2_OFF ^ BIT5);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void eight_minutes()
{
	//Row 10, Column 5
	P2OUT = (P2_OFF ^ BIT5);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void nine_minutes()
{
	//Row 10, Column 4
	P2OUT = (P2_OFF ^ BIT5);
	P3OUT = (P3_OFF | BIT2);
	return;
}
void ten_minutes()
{
	//Row 10, Column 3
	P2OUT = (P2_OFF ^ BIT5);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void eleven_minutes()
{
	//Row 10, Column 2
	P2OUT = (P2_OFF ^ BIT5);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void twelve_minutes()
{
	//Row 10, Column 1
	P2OUT = (P2_OFF ^ BIT5);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void thirteen_minutes()
{
	//Row 8, Column 12
	P3OUT = (P3_OFF ^ BIT4);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void fourteen_minutes()
{
	//Row 8, Column 11
	P3OUT = (P3_OFF ^ BIT4);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void fifteen_minutes()
{
	//Row 8, Column 10
	P3OUT = (P3_OFF ^ BIT4) | BIT5;
	return;
}
void sixteen_minutes()
{
	//Row 8, Column 9
	P3OUT = (P3_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void seventeen_minutes()
{
	//Row 8, Column 8
	P3OUT = (P3_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void eighteen_minutes()
{
	//Row 8, Column 7
	P3OUT = (P3_OFF ^ BIT4);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void nineteen_minutes()
{
	//Row 8, Column 6
	P3OUT = (P3_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void twenty_minutes()
{
	//Row 8, Column 5
	P3OUT = (P3_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void twentyone_minutes()
{
	//Row 8, Column 4
	P3OUT = (P3_OFF ^ BIT4) | BIT2;
	return;
}
void twentytwo_minutes()
{
	//Row 8, Column 3
	P3OUT = (P3_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void twentythree_minutes()
{
	//Row 8, Column 2
	P3OUT = (P3_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void twentyfour_minutes()
{
	//Row 8, Column 1
	P3OUT = (P3_OFF ^ BIT4);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void twentyfive_minutes()
{
	//Row 6, Column 12
	P2OUT = (P2_OFF ^ BIT4) | BIT0;
	return;
}
void twentysix_minutes()
{
	//Row 6, Column 11
	P2OUT = (P2_OFF ^ BIT4) | BIT1;
	return;
}
void twentyseven_minutes()
{
	//Row 6, Column 10
	P2OUT = (P2_OFF ^ BIT4);
	P3OUT = (P3_OFF | BIT5);
	return;
}
void twentyeight_minutes()
{
	//Row 6, Column 9
	P2OUT = (P2_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void twentynine_minutes()
{
	//Row 6, Column 8
	P2OUT = (P2_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void thirty_minutes()
{
	//Row 6, Column 7
	P2OUT = (P2_OFF ^ BIT4) | BIT3;
	return;
}
void thirtyone_minutes()
{
	//Row 6, Column 6
	P2OUT = (P2_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void thirtytwo_minutes()
{
	//Row 6, Column 5
	P2OUT = (P2_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void thirtythree_minutes()
{
	//Row 6, Column 4
	P2OUT = (P2_OFF ^ BIT4);
	P3OUT = (P3_OFF | BIT2);
	return;
}
void thirtyfour_minutes()
{
	//Row 6, Column 3
	P2OUT = (P2_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void thirtyfive_minutes()
{
	//Row 6, Column 2
	P2OUT = (P2_OFF ^ BIT4);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void thirtysix_minutes()
{
	//Row 6, Column 1
	P2OUT = (P2_OFF ^ BIT4);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void thirtyseven_minutes()
{
	//Row 4, Column 12
	P3OUT = (P3_OFF ^ BIT3);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void thirtyeight_minutes()
{
	//Row 4, Column 11
	P3OUT = (P3_OFF ^ BIT3);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void thirtynine_minutes()
{
	//Row 4, Column 10
	P3OUT = (P3_OFF ^ BIT3) | BIT5;
	return;
}
void fourty_minutes()
{
	//Row 4, Column 9
	P3OUT = (P3_OFF ^ BIT3);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void fourtyone_minutes()
{
	//Row 4, Column 8
	P3OUT = (P3_OFF ^ BIT3);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void fourtytwo_minutes()
{
	//Row 4, Column 7
	P3OUT = (P3_OFF ^ BIT3);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void fourtythree_minutes()
{
	//Row 4, Column 6
	P3OUT = (P3_OFF ^ BIT3);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void fourtyfour_minutes()
{
	//Row 4, Column 5
	P3OUT = (P3_OFF ^ BIT3);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void fourtyfive_minutes()
{
	//Row 4, Column 4
	P3OUT = (P3_OFF ^ BIT3) | BIT2;
	return;
}
void fourtysix_minutes()
{
	//Row 4, Column 3
	P3OUT = (P3_OFF ^ BIT3);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void fourtyseven_minutes()
{
	//Row 4, Column 2
	P3OUT = (P3_OFF ^ BIT3);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void fourtyeight_minutes()
{
	//Row 4, Column 1
	P3OUT = (P3_OFF ^ BIT3);
	P4OUT = (P4_OFF | BIT0);
	return;
}

void fourtynine_minutes()
{
	//Row 2, Column 12
	P3OUT = (P3_OFF ^ BIT1);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void fifty_minutes()
{
	//Row 2, Column 11
	P3OUT = (P3_OFF ^ BIT1);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void fiftyone_minutes()
{
	//Row 2, Column 10
	P3OUT = (P3_OFF ^ BIT1) | BIT5;
	return;
}
void fiftytwo_minutes()
{
	//Row 2, Column 9
	P3OUT = (P3_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void fiftythree_minutes()
{
	//Row 2, Column 8
	P3OUT = (P3_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void fiftyfour_minutes()
{
	//Row 2, Column 7
	P3OUT = (P3_OFF ^ BIT1);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void fiftyfive_minutes()
{
	//Row 2, Column 6
	P3OUT = (P3_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void fiftysix_minutes()
{
	//Row 2, Column 5
	P3OUT = (P3_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void fiftyseven_minutes()
{
	//Row 2, Column 4
	P3OUT = (P3_OFF ^ BIT1) | BIT2;
	return;
}
void fiftyeight_minutes()
{
	//Row 2, Column 3
	P3OUT = (P3_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void fiftynine_minutes()
{
	//Row 2, Column 2
	P3OUT = (P3_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT5);
	return;
}

void one_hours()
{
	//Row 11, Column 12
	P4OUT = (P4_OFF ^ BIT1);
	P2OUT = (P2_OFF | BIT0);
	return;
}
void two_hours()
{
	//Row 11, Column 11
	P4OUT = (P4_OFF ^ BIT1);
	P2OUT = (P2_OFF | BIT1);
	return;
}
void three_hours()
{
	//Row 11, Column 10
	P4OUT = (P4_OFF ^ BIT1);
	P3OUT = (P3_OFF | BIT5);
	return;
}
void four_hours()
{
	//Row 11, Column 9
	P4OUT = (P4_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT7);
	return;
}
void five_hours()
{
	//Row 11, Column 8
	P4OUT = (P4_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT6);
	return;
}
void six_hours()
{
	//Row 11, Column 7
	P4OUT = (P4_OFF ^ BIT1);
	P2OUT = (P2_OFF | BIT3);
	return;
}
void seven_hours()
{
	//Row 11, Column 6
	P4OUT = (P4_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT2);
	return;
}
void eight_hours()
{
	//Row 11, Column 5
	P4OUT = (P4_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT1);
	return;
}
void nine_hours()
{
	//Row 11, Column 4
	P4OUT = (P4_OFF ^ BIT1);
	P3OUT = (P3_OFF | BIT2);
	return;
}
void ten_hours()
{
	//Row 11, Column 3
	P4OUT = (P4_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT4);
	return;
}
void eleven_hours()
{
	//Row 11, Column 2
	P4OUT = (P4_OFF ^ BIT1);
	P1OUT = (P1_OFF | BIT5);
	return;
}
void twelve_hours()
{
	//Row 11, Column 1
	P4OUT = BIT0;
	return;
}
