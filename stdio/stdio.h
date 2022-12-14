#pragma once
#include "typedefs.h"
#include "string.h"
#include "syscalls.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 2

const char ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
    'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
    'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
    'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '
};
void set_args(char type, char arg1,char arg2, char arg3);
void clear(void);
void print_char(char b);
void printf(const char *fmt, ...);
char readChar(void);
void readLine(char* data);
void exit(int exit_code);
void deleteOneCharacter(void);
void Sleep(uint32_t mill);
void* memcpy(void* dest, void* src, uint32_t size);
void* memset(void* dest,uint8_t val, uint32_t size);