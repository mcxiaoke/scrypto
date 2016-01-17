#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t* hex2bin(const char* in);

char* bin2hex(const uint8_t* data, size_t len);

#endif
