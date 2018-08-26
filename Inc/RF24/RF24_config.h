
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__

#include "stm32f1xx_hal.h"
#include <util.h>
#include "tim.h"
#include "spi.h"

#include <stddef.h>
//#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define _BV(x) (1<<(x))


#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
#else
	#define IF_SERIAL_DEBUG(x)
#endif


typedef uint16_t prog_uint16_t;
#define PSTR(x) (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p)) 
#define PRIPSTR "%s"

#define LOW GPIO_PIN_RESET
#define HIGH GPIO_PIN_SET

#endif // __RF24_CONFIG_H__
// vim:ai:cin:sts=2 sw=2 ft=cpp
