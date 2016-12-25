#include "stdio.h"
#include "math.h"

#include <autoconfig.h>
#include "proginfo.h"
#include "la/liba.h"
#include "lb/libb.h"

#ifdef __cplusplus
extern "C" {
#endif

int main()
{
	printf("Macro:\n"
		"\tPRJ_NAME      %s\n"
		"\tPRJ_VERSION    %s\n"
		"\tPRJ_PATCHLEVEL %s\n"
		"\tPRJ_SUBLEVEL   %s\n"
		"\tBUILD_DATE    %s\n",
		PRJ_NAME,
		PRJ_VERSION,
		PRJ_PATCHLEVEL,
		PRJ_SUBLEVEL,
		BUILD_DATE);

	printf("asin(1) = %f\n", asin(1));

#ifdef CONFIG_USE_LB_FUN1
	printf("test lafun1():  ");
	lafun1();
#endif

#ifdef CONFIG_USE_LA_PART2
	printf("test lafun2():  ");
	lafun2();
#ifdef CONFIG_USE_LA_FUN3
	printf("test lafun3():  ");
	lafun3();
#endif
#endif




#ifdef CONFIG_USE_LB_FUN1
	printf("test lbfun1():  ");
	lbfun1();
#endif

#ifdef CONFIG_USE_LB_PART2
	printf("test lbfun2():  ");
	lbfun2();
#ifdef CONFIG_USE_LB_FUN3
	printf("test lbfun3():  ");
	lbfun3();
#endif
#endif
	
	return 0;
}



PROG_INFO(project, PRJ_NAME);
PROG_VERSION( PRJ_VERSION "." PRJ_PATCHLEVEL "." PRJ_SUBLEVEL);
PROG_BUILD(BUILD_DATE);
PROG_GITSHA1(__GIT_SHA1__);

PROG_AUTHOR("MenglongWu");
PROG_DEPEND( "liba.so libb.so");
PROG_DESCRIPTION( "MakeDoxygen demo");

#ifdef __cplusplus
}
#endif