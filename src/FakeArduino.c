/*
 * =====================================================================================
 *
 *       Filename:  FakeArduino.c
 *
 *    Description:  Fake arduino implementation
 *
 *        Version:  1.0
 *        Created:  2014.10.28 18:29:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karolis Kalantojus (kkarolis), karolis.kalantojus@gmail.com
 *   Organization:  Vilnius University
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "FakeArduino.h"
#include <stdint.h>
#include <assert.h>


static uint64_t pin_modes = 0x00000000;
static uint64_t pin_states = 0x00000000;

static void set_bit(uint64_t *number, int bit_num)
{
        *number |= 1 << bit_num;
}

static void clear_bit(uint64_t *number, int bit_num)
{
        *number &= ~(1 << bit_num);
}

static uint64_t check_bit(uint64_t* number, int bit_num)
{
        uint64_t bit = *number & (1 << bit_num);
        return bit;
}

void pinMode(int pin, int mode)
{
        (mode == IN)? clear_bit(&pin_modes, pin) : set_bit(&pin_modes, pin);
}

void digitalWrite(int pin, int value)
{
        assert (get_pinMode(pin) == OUT);
        (value == LOW)? clear_bit(&pin_states, pin) :
                set_bit(&pin_states, pin);
}

int get_pinMode(int pin)
{
        uint64_t bit = check_bit(&pin_modes, pin);
        return ((bit == 0)? IN : OUT);
}

int get_pinState(int pin)
{
        uint64_t bit = check_bit(&pin_states, pin);
        return ((bit == 0)? LOW : HIGH);
}

uint64_t modes(void)
{
        return pin_modes;
}

uint64_t states(void)
{
        return pin_states;
}
