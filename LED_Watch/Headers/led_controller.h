/*
 * led_controller.h
 *
 *  Created on: Aug 25, 2015
 *      Author: Sean
 */

#ifndef HEADERS_LED_CONTROLLER_H_
#define HEADERS_LED_CONTROLLER_H_

#define P1_OFF 0x3E
#define P2_OFF 0x18
#define P3_OFF 0x0F
#define P4_OFF 0x00
#define PJ_OFF 0x00

#define HOURS_ROW       0
#define MINUTES_ROW     1
#define SECONDS_ROW     2
#define NO_ROW          3

void reset_leds();

void LED_SetCurrentLED(unsigned char index, unsigned int row);

#endif /* HEADERS_LED_CONTROLLER_H_ */
