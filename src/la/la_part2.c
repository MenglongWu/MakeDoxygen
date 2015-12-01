#include <autoconfig.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


void lafun2()
{
	printf("%s", CONFIG_LB_FUN2_STR);
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
