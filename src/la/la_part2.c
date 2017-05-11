/**
 * Copyright 2015-2017 MenglongWoo@aliyun.com
 * @file	src/la/la_part2.c
 * @brief	example for MakeDoxygen
 * 
*/
#include <stdio.h>
#include <autoconfig.h>


#ifdef __cplusplus
extern "C" {
#endif


void lafun2()
{
	printf("%s\n", CONFIG_LA_FUN2_STR);
}

#ifdef CONFIG_USE_LA_PART2
void lafun3()
{
	printf("I'm fun3() from libla.so new\n");
}
#endif


#ifdef __cplusplus
}
#endif
