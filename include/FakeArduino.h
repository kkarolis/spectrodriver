/*
 * =====================================================================================
 *
 *       Filename:  FakeArduino.h
 *
 *    Description:  Fake arduino header for testing purposes
 *
 *        Version:  1.0
 *        Created:  2014.10.28 16:07:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karolis Kalantojus (kkarolis), karolis.kalantojus@gmail.com
 *   Organization:  Vilnius University
 *
 * =====================================================================================
 */
#ifndef  FAKEARDUINO_INC
#define  FAKEARDUINO_INC

#include <stdint.h>

#define OUT 1
#define IN 0
#define HIGH 1 
#define LOW 0

void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int get_pinMode(int pin);
int get_pinState(int pin);
uint64_t modes(void);
uint64_t states(void);

#endif   /* ----- #ifndef FAKEARDUINO_INC  ----- */
