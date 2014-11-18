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

#ifndef  SHUTTER_INC
#define  SHUTTER_INC

#include "Pinout.h"

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */
#include <stdint.h>

void Shutter_init(void);
void Shutter_open(void);
void Shutter_close(void);
void Shutter_toggle(void);
void Shutter_bound_left(void);
void Shutter_bound_right(void);
void Shutter_bound_reset(void);

#endif   /* ----- #ifndef SHUTTER_INC  ----- */
