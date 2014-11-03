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
static uint64_t hits[PIN_COUNT] = {0};

static void set_bit(uint64_t *number, uint32_t bit_num)
{
        *number |= 1 << bit_num;
}

static void clear_bit(uint64_t *number, uint32_t bit_num)
{
        *number &= ~(1 << bit_num);
}

static uint64_t check_bit(uint64_t* number, uint32_t bit_num)
{
        uint64_t bit = *number & (1 << bit_num);
        return bit;
}

static void increment_pin_hit(uint32_t pin)
{
        assert(pin < PIN_COUNT);
        hits[pin] += 1;
}

void pinMode(uint32_t pin, uint32_t mode)
{
        (mode == IN)? clear_bit(&pin_modes, pin) : set_bit(&pin_modes, pin);
}

void digitalWrite(uint32_t pin, uint32_t value)
{
        assert(get_pinMode(pin) == OUT);
        if (value == HIGH) {
                set_bit(&pin_states, pin);
                increment_pin_hit(pin);
        } else {
                clear_bit(&pin_states, pin);
        }
}

uint32_t get_pinMode(uint32_t pin)
{
        uint64_t bit = check_bit(&pin_modes, pin);
        return ((bit == 0)? IN : OUT);
}

uint32_t get_pinState(uint32_t pin)
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

void delayMicroseconds(uint32_t seconds)
{
        /* Since its not an adress - does nothing */
        seconds += 1;
}

uint32_t pin_hits(uint32_t pin)
{
        assert(pin < PIN_COUNT);
        return hits[pin];
}

void reset_pin_hits()
{
        for(int i = 0; i < PIN_COUNT - 1; i++) hits[i] = 0; 
}
