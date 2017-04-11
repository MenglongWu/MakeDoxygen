/**
 ******************************************************************************
 * @file	example/dev1.c
 * @brief	模拟开发者1写的代码

 *
 @section Platform
	-# printl_common.c
- 2016-12-07,MenglongWu

*/

#include <stdio.h>
#include <stdbool.h>
#include <printl.h>
#include <printl_common.h>

#include "dev1-private.h"


bool dev1_is_digit(char *str)
{
	char *pstr = str;
	while(*pstr) {
		if (*pstr < '0' || *pstr > '9') {
			PRINTW("string \"%s\" is not digit", str);
			return false;
		}
		pstr++;
	}
	return true;
}
double dev1_div(double a, double b)
{
	if (b == 0) {
		PRINTE("dividend b = 0");
	}
	return a / b;
}
void dev1_mod1()
{
	print_m1("%s() %d:   print_m1()\n", __FUNCTION__, __LINE__);
}

void dev1_mod2()
{
	print_m2("%s() %d:   print_m2()\n", __FUNCTION__, __LINE__);
}