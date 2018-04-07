/*
 * head.h
 *
 *  Created on: Aug 21, 2015
 *      Author: Sean
 */

#ifndef HEADERS_HEAD_H_
#define HEADERS_HEAD_H_

// States
#define ShowTime 1
#define SetTime 2
#define Sleep 3
#define SetPeriodicAlarm 4
#define SetAlarm 5
#define SetSleepTime    6

#define PERIODIC_NONE       4
#define PERIODIC_MINUTE     0
#define PERIODIC_HOUR       1
#define PERIODIC_MIDNIGHT   2
#define PERIODIC_NOON       3

// Constants
#define HOURS 0
#define MINUTES 1
#define SECONDS 2

void initialize(char rtcPeriodicMode);

#endif /* HEADERS_HEAD_H_ */
