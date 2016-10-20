#include "stdio.h"
#include "math.h"

#include <autoconfig.h>
#include "proginfo.h"
#include "la/liba.h"
#include "lb/libb.h"

// #ifdef __cplusplus
// extern "C" {

// #endif

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
// #ifdef __cplusplus
// }
// #endif



#ifdef PRJ_NAME
PROG_INFO(project, PRJ_NAME);
#endif

#if  defined(PRJ_VERSION) && defined(PRJ_PATCHLEVEL) && defined(PRJ_SUBLEVEL)
PROG_INFO(version, PRJ_VERSION "." PRJ_PATCHLEVEL "." PRJ_SUBLEVEL);
#endif

#ifdef BUILD_DATE
PROG_INFO(build, BUILD_DATE);
#endif

PROG_INFO(Author, "MenglongWu");
PROG_INFO(depend, "liba.so libb.so");
PROG_INFO(description, "MakeDoxygen demo");