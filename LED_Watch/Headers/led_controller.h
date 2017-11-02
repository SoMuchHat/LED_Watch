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

typedef enum {
    HOURS_ROW = 0,
    MINUTES_ROW = 1,
    SECONDS_ROW = 2,
    NO_ROW = 3
} selectedRow_t;

void reset_leds();

void LED_SetCurrentLED(unsigned char index, selectedRow_t row);

#endif /* HEADERS_LED_CONTROLLER_H_ */
