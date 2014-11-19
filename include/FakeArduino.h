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

#define OUTPUT 0x1
#define IN 0x0
#define HIGH 0x1 
#define LOW 0x0
#define PIN_COUNT 64

void pinMode(uint32_t pin, uint32_t mode);
void digitalWrite(uint32_t pin, uint32_t value);
uint32_t get_pinMode(uint32_t pin);
uint32_t get_pinState(uint32_t pin);
uint64_t modes(void);
uint64_t states(void);
void delayMicroseconds(uint32_t);
void reset_pin_hits(void);
uint32_t pin_hits(uint32_t pin);
void reset_pin_toggles(void);
uint32_t pin_toggles(uint32_t pin);

#endif   /* ----- #ifndef FAKEARDUINO_INC  ----- */
