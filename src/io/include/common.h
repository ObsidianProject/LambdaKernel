#ifndef COMMON_H
#define COMMON_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef char* string;
uint64 strlen(const char *str);

uint32 digit_count(int num);

void itoa(int num, char *number);

#endif