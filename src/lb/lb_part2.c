/**
 * Copyright 2015-2017 MenglongWoo@aliyun.com
 * @file	src/lb/lb_part2.c
 * @brief	example for MakeDoxygen
 * 
*/
#include <stdio.h>
#include <autoconfig.h>


#ifdef __cplusplus
extern "C" {
#endif

void lbfun2()
{
	printf("%s\n", CONFIG_LB_FUN2_STR);
}

#ifdef CONFIG_USE_LB_PART2
void lbfun3()
{
	printf("I'm fun3() from liblb.so new\n");
}
#endif

#ifdef __cplusplus
}
#endif
