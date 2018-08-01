/*
 * light_detect.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Sean H
 */

#include "Headers/head.h"
#include "Headers/led_controller.h"
#include <msp430.h>

volatile unsigned int ADC_Result = 0;

void measureLightInit()
{
    ADC10CTL0 |= ADC10SHT_0 + ADC10ON;
    ADC10CTL1 |= ADC10SHP;
    ADC10CTL2 |= ADC10RES;
    ADC10MCTL0 |= ADC10INCH_1;
    ADC10IE |= ADC10IE0;
}

unsigned int measureLightIntensity(unsigned char hour)
{
    unsigned int startV = 0;
    unsigned int endV = 0;
    reset_leds();

    LED_SetCurrentLED(hour, 0);        // Turn on 12th hour LED
    __delay_cycles(20);               // Just to ensure LED gets a tiny bit of time to turn on

    reset_leds();                   // Turn off 12th hour LED

    P1DIR = 0x3D;

    // Change P1.1 to be ADC input
    P1SEL0 |= BIT1;
    P1SEL1 |= BIT1;

    // Trigger ADC sample start
    ADC10CTL0 |= ADC10ENC + ADC10SC;
    //unsigned int temp = ADC10MEM0;
    // Sleep until ADC done sampling and result is stored
    //__bis_SR_register(CPUOFF + GIE);
    while (ADC10CTL1 & ADC10BUSY);
    __no_operation();

    // Store current voltage before discharge
    startV = ADC_Result;

    __delay_cycles(5000);

    // Measure voltage after discharge time
    // Trigger ADC sample start
    ADC10CTL0 |= ADC10ENC + ADC10SC;
    //unsigned int temp2 = ADC10MEM0;
    // Sleep until ADC done sampling and result is stored
    //__bis_SR_register(CPUOFF + GIE);
    while (ADC10CTL1 & ADC10BUSY);
    __no_operation();

    endV = ADC_Result;

    unsigned int diff = 0;

    if (startV > endV)
    {
        diff = startV - endV;
    }

    if (diff < 25)
    {
       diff = 25;
    }

    diff -= 25;

    if (diff > 50)
    {
        diff = 50;
    }

    P1DIR = 0x3F;
    P1SEL0 &= ~BIT1;                // Change P1.1 to be digital output again
    P1SEL1 &= ~BIT1;

    return (50 - diff);
}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    switch(__even_in_range(ADC10IV,12))
    {
    case 12:
    {
        ADC_Result = ADC10MEM0;
        __bic_SR_register_on_exit(CPUOFF);
        break;
    }
    default:
        break;
    }
}
