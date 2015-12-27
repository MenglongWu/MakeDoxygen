#include <autoconfig.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	
void lbfun1()
{
	printf("%s", CONFIG_LA_FUN1_STR);
}

#ifdef __cplusplus
}
#endif

