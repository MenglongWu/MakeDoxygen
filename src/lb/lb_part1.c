/**
 * Copyright 2015-2017 MenglongWoo@aliyun.com
 * @file	src/lb/lb_part1.c
 * @brief	example for MakeDoxygen
 * 
*/
#include <stdio.h>

#include <autoconfig.h>
#include "proginfo.h"


#ifdef __cplusplus
extern "C" {
#endif


void lbfun1()
{
	printf("%s\n", CONFIG_LA_FUN1_STR);
}


PROG_INFO(project, PRJ_NAME);
PROG_VERSION(PRJ_VERSION "." PRJ_PATCHLEVEL "." PRJ_SUBLEVEL);
PROG_BUILD(__DATE__ " " __TIME__);
PROG_AUTHOR("MenglongWu");
PROG_DESCRIPTION("MakeDoxygen demo dynamic library libb.so part1");
#ifdef __cplusplus
}
#endif

