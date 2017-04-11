/**
 ******************************************************************************
 * @file	example/dev2.c
 * @brief	模拟开发者2写的代码 

 *
 @section Platform
	-# printl_common.c
- 2016-12-07,MenglongWu

*/
#include <stdio.h>
#include <printl.h>
#include <printl_common.h>

#include "dev2-private.h"



void dev2_mod1()
{
	print_m1("%s() %d   print_m1()\n", __FUNCTION__, __LINE__);
}

void dev2_mod2()
{
	print_m2("%s() %d   print_m2()\n", __FUNCTION__, __LINE__);
}