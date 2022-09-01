#pragma once

#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H

#include<stdint.h>/*int8_t,...*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>/*Sleep(millisec)*/

#define DEF_PROJ(funcEntrName) int funcEntrName(const int argc, const char* argv[], const char* env[])
#define DEF_EXTERN_PROJ(funcEntrName)	extern DEF_PROJ(funcEntrName)
#define CALL_EXTERN_PROJ(funcEntrName)	funcEntrName(argc, argv, env)
#define EXTERN_PROJ(funcEntrName) \
					DEF_EXTERN_PROJ(funcEntrName); \
					return CALL_EXTERN_PROJ(funcEntrName);\
					system("pause");\
					system("cls")

#define BYTE_PTR(ptr) ((uint8_t*)(ptr))
#define WORD_PTR(ptr) ((uint16_t*)(ptr))
#define BYTE_SHIFT 0x08

#define TOSTR(str) #str/*convert param 'str' in string*/
#define TOFLAG(str) TOSTR(-str)/*convert param 'str' in string*/

typedef const char* str_t;

#endif/*!COMMON_INCLUDES_H*/