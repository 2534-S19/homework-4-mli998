/*
 * homework4.h
 *
 *  Created on:4/7/2020
 *      Author:Meijin Li
 */

#ifndef HOMEWORK4_H_
#define HOMEWORK4_H_

// This function initializes the board by turning off the Watchdog Timer.
void initBoard();
bool charFSM(char rChar);

// TODO: Define any constants that are local to homework.c using #define
   #define LAUNCHPAD_ONLY
   #define P2_RED_LED_H GPIO_PIN0
   #define P2_BLUE_LED_H GPIO_PIN2
   #define P2_GREEN_LED_H GPIO_PIN1
   #define P2_ALL_LEDS_H (P2_RED_LED_H|P2_BLUE_LED_H|P2_GREEN_LED_H)
   #define A0_BRDIV 1
   #define A0_UCxBRF 10
   #define A0_UCxBRS 0
#endif /* HOMEWORK4_H_ */
