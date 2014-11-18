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
#ifndef  SPECTROMETER_INC
#define  SPECTROMETER_INC

#include <stdint.h>

#include "Pinout.h"
#include "Stepper.h"
#include "Shutter.h"

void Spectrometer_init(void);
uint32_t Spectrometer_parse(uint32_t);
void Spectrometer_execute(uint32_t);
void Spectrometer_busy_set(void);
void Spectrometer_busy_clear(void);

#endif   /* ----- #ifndef SPECTROMETER_INC  ----- */
