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
#include <printl.h>
#include <printl_common.h>

#include "dev1-private.h"



void dev1_mod1()
{
	PRINTD("%s() %d    debug dev1 module1", __FUNCTION__, __LINE__);
	PRINTW("%s() %d    warning dev1 module1", __FUNCTION__, __LINE__);
	PRINTE("%s() %d    error dev1 module1", __FUNCTION__, __LINE__);
	print_m1("%s() %d   print_m1()\n", __FUNCTION__, __LINE__);
}

void dev1_mod2()
{
	PRINTD("%s() %d    debug dev1 module2", __FUNCTION__, __LINE__);
	PRINTW("%s() %d    warning dev1 module2", __FUNCTION__, __LINE__);
	PRINTE("%s() %d    error dev1 module2", __FUNCTION__, __LINE__);
	print_m2("%s() %d   print_m2()\n", __FUNCTION__, __LINE__);
}