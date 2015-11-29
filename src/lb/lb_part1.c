#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	
void lbfun1()
{
	printf("I'm fun1() from liblb.so\n");
}

#ifdef __cplusplus
}
#endif

