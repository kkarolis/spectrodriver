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
#include "Stepper.h"
#include <stdint.h>

// Command width in bits should be less than 32
#define CMD_WIDTH 8

void Spectrometer_init(void);
uint32_t Spectrometer_parse(uint32_t cmd);

#endif   /* ----- #ifndef SPECTROMETER_INC  ----- */
