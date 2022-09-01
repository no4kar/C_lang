#pragma once
#include<stdio.h>
#include<string.h>
#include<assert.h>/*assert(FALSE) -> abort()*/

#define DEF_PROJ(funcEntrName)	int _##funcEntrName(const int argc, const char* argv[])

DEF_PROJ(ParseFormat);
