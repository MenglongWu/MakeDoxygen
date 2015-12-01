#include <autoconfig.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	
void lbfun2()
{
	printf("%s", CONFIG_LB_FUN2_STR);
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
