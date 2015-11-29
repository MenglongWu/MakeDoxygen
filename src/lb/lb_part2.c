#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	
void lbfun2()
{
	printf("I'm fun2() from liblb.so\n");
}

#ifdef __cplusplus
}
#endif
