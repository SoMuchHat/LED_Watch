/*
 * led_controller.c
 *
 *  Created on: Aug 21, 2015
 *      Author: Sean
 */

#include <msp430.h>
#include "Headers\led_controller.h"


typedef struct {
    char P1;
    char P2;
    char P3;
    char P4;
    char PJ;
} ledCommand_t;

static char test = 0;

static const ledCommand_t led_seconds[60] = {{ (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },    // 0 seconds
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT3) | BIT7),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },             // 1 second
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },             // 2 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT3) | BIT6),     (char)P4_OFF,           (char)PJ_OFF },                   // 3 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT3) | BIT4),     (char)P4_OFF,           (char)PJ_OFF },                   // 4 seconds
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT6),              (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)PJ_OFF },                   // 5 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT3),              (char)(P4_OFF | BIT0),  (char)PJ_OFF },                   // 6 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)(PJ_OFF | BIT1) },    // 7 seconds
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT1),              (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)PJ_OFF },                   // 8 seconds
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT0),              (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)PJ_OFF },                   // 9 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)(PJ_OFF | BIT3) },    // 10 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)(PJ_OFF | BIT2) },    // 11 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)(PJ_OFF | BIT0) },    // 12 seconds
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT7),              (char)(P3_OFF ^ BIT3),              (char)P4_OFF,           (char)PJ_OFF },                   // 13 seconds
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT3) | BIT7),     (char)P4_OFF,           (char)PJ_OFF },                   // 14 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },                   // 15 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },              // 16 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)(P2_OFF | BIT6),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },              // 17 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },              // 18 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },              // 19 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)(P2_OFF | BIT1),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },              // 20 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)(P2_OFF | BIT0),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },              // 21 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },              // 22 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) },              // 23 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },              // 24 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)(P2_OFF | BIT7),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },              // 25 seconds
                                             { (char)(P1_OFF ^ BIT4),           (char)P2_OFF,                       (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },              // 26 seconds
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },              // 27 seconds
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },              // 28 seconds
                                             { (char)(P1_OFF ^ BIT2),           (char)(P2_OFF | BIT6),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },              // 29 seconds
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)(P1_OFF ^ BIT2),           (char)(P2_OFF | BIT1),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT2),           (char)(P2_OFF | BIT0),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)(P1_OFF ^ BIT2),           (char)(P2_OFF | BIT7),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT2),           (char)P2_OFF,                       (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT2) | BIT6),       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT2) | BIT4),       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT6),              (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT2),              (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT1),              (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT0),              (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT7),              (char)(P3_OFF ^ BIT2),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT2) | BIT7),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT3) | BIT6),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT3) | BIT1),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT3) | BIT0),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT3),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) }
};

static const ledCommand_t led_minutes[60] = {{ (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT4) | BIT7),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT0) | BIT6),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT0) | BIT4),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT6),              (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT0),              (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT1),              (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT0),              (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT7),              (char)(P3_OFF ^ BIT0),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT0) | BIT7),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)(P2_OFF | BIT6),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)(P1_OFF ^ BIT5),           (char)(P2_OFF | BIT1),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)(P2_OFF | BIT0),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)(P1_OFF ^ BIT5),           (char)(P2_OFF | BIT7),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT5),           (char)P2_OFF,                       (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)(P2_OFF | BIT6),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)(P1_OFF ^ BIT3),           (char)(P2_OFF | BIT1),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)(P2_OFF | BIT0),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)(P1_OFF ^ BIT3),           (char)(P2_OFF | BIT7),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)(P1_OFF ^ BIT3),           (char)P2_OFF,                       (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT1) | BIT6),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT1) | BIT4),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT6),              (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT1),              (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT1),              (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT0),              (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                             { (char)P1_OFF,                    (char)(P2_OFF | BIT7),              (char)(P3_OFF ^ BIT1),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)P2_OFF,                       (char)((P3_OFF ^ BIT1) | BIT7),     (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT4) | BIT6),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT4) | BIT1),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)((P2_OFF ^ BIT4) | BIT0),     (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                             { (char)P1_OFF,                    (char)(P2_OFF ^ BIT4),              (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) }

};

static const ledCommand_t led_hours[24] = {{ (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                           { (char)(P1_OFF ^ BIT1),             (char)(P2_OFF | BIT7),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)(P2_OFF | BIT6),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                           { (char)(P1_OFF ^ BIT1),             (char)(P2_OFF | BIT1),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)(P2_OFF | BIT0),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                           { (char)(P1_OFF ^ BIT1),             (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT0) },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)(P2_OFF | BIT7),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)(P3_OFF | BIT7),              (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)(P3_OFF | BIT6),              (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)(P3_OFF | BIT4),              (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)(P2_OFF | BIT6),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)P3_OFF,                       (char)(P4_OFF | BIT0),  (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT1) },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)(P2_OFF | BIT1),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)(P2_OFF | BIT0),              (char)P3_OFF,                       (char)P4_OFF,           (char)PJ_OFF },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT3) },
                                           { (char)((P1_OFF ^ BIT1) | BIT0),    (char)P2_OFF,                       (char)P3_OFF,                       (char)P4_OFF,           (char)(PJ_OFF | BIT2) }
                                           //{ (char)(P1_OFF ^ BIT1),     (char)P2_OFF,           (char)P3_OFF,           (char)P4_OFF,           (char)(PJ_OFF | BIT0) }
};

void reset_leds()
{
    P1OUT = (char)P1_OFF;
    P2OUT = (char)P2_OFF;
    P3OUT = (char)P3_OFF;
    P4OUT = (char)P4_OFF;
    PJOUT = (short)PJ_OFF;
}


#pragma FUNC_ALWAYS_INLINE(LED_SetCurrentLED)
inline void LED_SetCurrentLED(unsigned char index, unsigned int row)
{
    reset_leds();
    switch(row)
    {
    case HOURS_ROW:
    {
            P1OUT = led_hours[index].P1;
            P2OUT = led_hours[index].P2;
            P3OUT = led_hours[index].P3;
            P4OUT = led_hours[index].P4;
            PJOUT = (PJOUT & 0xFF) | (short) led_hours[index].PJ;

        break;
    }
    case MINUTES_ROW:
    {
            P1OUT = led_minutes[index].P1;
            P2OUT = led_minutes[index].P2;
            P3OUT = led_minutes[index].P3;
            P4OUT = led_minutes[index].P4;
            PJOUT = (PJOUT & 0xFF00) | (short) led_minutes[index].PJ;

        break;
    }
    case SECONDS_ROW:
    {
            P1OUT = led_seconds[index].P1;
            P2OUT = led_seconds[index].P2;
            P3OUT = led_seconds[index].P3;
            P4OUT = led_seconds[index].P4;
            PJOUT = (PJOUT & 0xFF00) | (short) led_seconds[index].PJ;
       break;
    }
    default:

        break;
    }
}




